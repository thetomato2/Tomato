#pragma  once
#include <windows.h>
#include <atomic>
#include <thread>
#include <mutex>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

namespace Tomato
{
// Log Policies
	// Virtual abstract class - interface to open and close streams (and to write them)
	class LogPolicyInterface {
	public:
		virtual ~LogPolicyInterface() noexcept = default;
		virtual bool OpenOutputStream(const std::wstring& name) = 0;
		virtual void CloseOutputStream() = 0;
		virtual void Write(const std::string& msg) = 0;
	};

	// implementation of a policy  to write a file on the hard drive
	class FileLogPolicy : public LogPolicyInterface {
	public:
		FileLogPolicy() : m_outputStream() {};
		~FileLogPolicy() {};
		bool OpenOutputStream(const std::wstring& fileName) override;
		void CloseOutputStream() override;
		void Write(const std::string& msg) override;
	private:
		std::ofstream m_outputStream;
	};

	// Message types
	enum SeverityType {
		Info = 0,
		Debug,
		Warning,
		Error,
		Config
	};

	// Logger
	template<typename LogPolicy>
	class Logger;

	template<typename LogPolicy>
	void LoggingDaemon(Logger<LogPolicy>* logger) {
		// dump log data if present
		std::unique_lock<std::timed_mutex> lock(logger->m_writeMutex, std::defer_lock);
		do {
			std::this_thread::sleep_for(std::chrono::milliseconds{ 50 });
			if (logger->m_logBuffer.size()) {
				if (!lock.try_lock_for(std::chrono::milliseconds{ 50 }))
					continue;
				for (auto& x : logger->m_logBuffer)
					logger->m_policy.Write(x);
				logger->m_logBuffer.clear();
				lock.unlock();
			}
		} while (logger->m_isStillRunning.test_and_set() || logger->m_logBuffer.size());
	}

	// the actual logger class to be instantiated with a specific log policy
	template<typename LogPolicy>
	class Logger {
	private:
		unsigned int m_logLineNumber;								// used to save the current line number
		std::map<std::thread::id, std::string> m_threadName;		// defines a human-readable name for each thread
		LogPolicy m_policy;										// the log policy (i.e. write to file, ...)
		std::timed_mutex m_writeMutex;							// mutual exclusive writer
		std::vector<std::string> m_logBuffer;						// the content to log
		std::thread m_daemon;										// the actual logging daemon
		std::atomic_flag m_isStillRunning{ ATOMIC_FLAG_INIT };	// lock-free boolean to check whether our daemon is still running or not

	public:
		// constructor and destructor
		Logger(const std::wstring& name);
		~Logger();

		void SetThreadName(const std::string& name);			// sets human-readable name for current thread

		template<SeverityType severity>
		void Print(std::stringstream stream);					// print message (varies based on severity level)
		template<SeverityType severity>
		void Print(std::string msg);

		template<typename Policy>
		friend void LoggingDaemon(Logger<Policy>* logger);		// the actual logger daemon
	};

	template<typename LogPolicy>
	Logger<LogPolicy>::Logger(const std::wstring& name) : m_logLineNumber(0), m_threadName(), m_policy(), m_writeMutex(), m_logBuffer() {
		if (m_policy.OpenOutputStream(name)) {
			m_isStillRunning.test_and_set();						// mark the logging daemon as running
			m_daemon = std::move(std::thread{ LoggingDaemon<LogPolicy>, this });
		} else
			throw std::runtime_error("Unable to open the log file!");
	}

	template<typename LogPolicy>
	Logger<LogPolicy>::~Logger() {
#ifndef NDEBUG
		// print closing message
		Tomato::ServiceLocator::GetFileLogger()->Print<Tomato::SeverityType::Info>("The file logger was shut down.");
#endif
		// terminate the daemon by clearing the still running flag and letting it join to the main thread
		m_isStillRunning.clear();
		m_daemon.join();

		// clear the thread name map
		m_threadName.clear();
		std::map<std::thread::id, std::string>().swap(m_threadName);

		// clear the log vector
		m_logBuffer.clear();
		m_logBuffer.shrink_to_fit();

		// close the output stream
		m_policy.CloseOutputStream();
	}

	template<typename LogPolicy>
	void Logger<LogPolicy>::SetThreadName(const std::string& name) {
		m_threadName[std::this_thread::get_id()] = name;
	}

	template<typename LogPolicy>
	template<SeverityType severity>
	void Logger<LogPolicy>::Print(std::stringstream stream) {
		std::stringstream logStream;

		if (!(severity == SeverityType::Config)) {
		// get time
			SYSTEMTIME localTime;
			GetLocalTime(&localTime);

			// header: line number and date (x: xx/xx/xxxx xx:xx:xx)
			if (m_logLineNumber != 0)
				logStream << "\r\n";
			logStream << m_logLineNumber++ << ": " << localTime.wMonth << "/" << localTime.wDay << "/" << localTime.wYear << " " << localTime.wHour << ":" << localTime.wMinute << ":" << localTime.wSecond << "\t";

			// write down warning level
			switch (severity) {
			case SeverityType::Info:
				logStream << "INFO:    ";
				break;
			case SeverityType::Debug:
				logStream << "DEBUG:   ";
				break;
			case SeverityType::Warning:
				logStream << "WARNING: ";
				break;
			case SeverityType::Error:
				logStream << "ERROR:   ";
				break;
			};

			// write thread name
			logStream << m_threadName[std::this_thread::get_id()] << ":\t";
		}
		// write the actual message
		logStream << stream.str();
		std::lock_guard<std::timed_mutex> lock(m_writeMutex);
		m_logBuffer.push_back(logStream.str());
	}

	template<typename LogPolicy>
	template<SeverityType severity>
	void Logger<LogPolicy>::Print(std::string msg) {
		std::stringstream stream;
		stream << msg.c_str();
		this->Print<severity>(std::stringstream(stream.str()));
	}
}


