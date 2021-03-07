#pragma once
#include "Application.h"
#include <ShlObj.h>
#include <Shlwapi.h>
#include <PathCch.h>
#include <sol.hpp>
#include <sstream>

namespace App
{
	Application::Application()
		:m_clientHeight(200), m_clientWidth(200), m_window(100, 100, "Tomato") {
		m_console.CreateConsole();
		m_window.SetForeground();
		m_activeLogger = false;
		m_validConfigFile = false;
	}

	// main loop
	void Application::DoFrame() {
		if (m_window.m_keyboard.KeyIsPressed(VK_SPACE)) {
			TOM_LOG_DEBUG("Space is pressed!");
		}

		if (m_window.m_keyboard.KeyIsPressed(0x54)) {
			TOM_LOG_DEBUG("T");
		}
		
		if (m_window.m_keyboard.ReadKey().IsPress()) {
			std::ostringstream oss;
			oss <<  m_window.m_keyboard.ReadChar();
			TOM_LOG_DEBUG(oss.str());
		}

	}

	int Application::Application::Go() {
		// start logging service
		GetMyDocumentsPath();

		try {
			StartLoggingService();
			m_activeLogger = true;
		} catch (std::runtime_error) {
			// show error message on on message box
			MessageBox(NULL, "Unable to start logging service!", "Critical Error!", MB_ICONEXCLAMATION | MB_OK);
			return -1;
		}

		if (!CheckConfigFile()) {
			TOM_LOG_WARNING("Non existant or invalid config file!");
		}
		ReadResolution();
		m_window.SetResolution(m_clientWidth, m_clientHeight);
		
		std::ostringstream oss;
		oss << "Resolution is x: " << m_clientWidth << ", y: " << m_clientHeight << std::endl;

		TOM_LOG_INFO(oss.str());

		TOM_LOG_INFO("App configured. Main loop starting...");

		// start the main loop
		while (true) {
			// process all messages pending but do not block new messages
			if (const auto ecode = TomWin::Window::ProcessMessage()) {
				// if return optional has value it means we are quitting
				// so return exit code
				return *ecode;
			}
			DoFrame();
		}
	}

	void Application::StartLoggingService() {
		HRESULT hr;
		hr = SHCreateDirectory(NULL, m_logFilePath.c_str());

		//debug mode only check to make sure operator succeeds
#ifndef NDEBUG
		if (FAILED(hr))
			TOM_LAST_EXCEPT();
#endif
		// append name of log file to the path
		std::wstring logFile = m_logFilePath + L"\\TomatoEngine.log";

		//create file logger
		std::shared_ptr<TomUtils::Logger<TomUtils::FileLogPolicy>> engineLogger(new TomUtils::Logger<TomUtils::FileLogPolicy>(logFile));

		// set logger to active
		m_activeLogger = true;

		// set name of current thread
		engineLogger->SetThreadName("mainThread");

		//register the logging service
		TomUtils::ServiceLocator::ProvideFileLoggingService(engineLogger);

#ifndef NDEBUG
	// print starting message
		TOM_LOG_INFO("The file logger was created successfully.");
#endif
	}

	bool Application::IsLogger() {
		return m_activeLogger;
	}

	bool Application::GetMyDocumentsPath() {
		PWSTR docPath = NULL;
		HRESULT hr = SHGetKnownFolderPath(FOLDERID_Documents, NULL, NULL, &docPath);

#ifndef NDEBUG
		if (FAILED(hr))
			TOM_LAST_EXCEPT();
#endif

		// store path
		m_myDocumentsPath = docPath;

		// delete the wstring pointer to avoid memory leak
		::CoTaskMemFree(static_cast<void*>(docPath));

		//set up log and configuration paths

		// append custom folder to path
		// TODO: temp custom path
		m_logFilePath = L"C:\\dev\\git\\Tomato\\Files\\Log";
		m_configFilePath = L"C:\\dev\\git\\Tomato\\Files\\Config";

		return true;
	}

	bool Application::CheckConfigFile() {
		HRESULT hr;
		hr = SHCreateDirectory(NULL, m_configFilePath.c_str());
#ifndef NDEBUG
		if (FAILED(hr))
			return false;
#endif 

		// append name of log file to the path
		std::wstring pathToPrefFile = m_configFilePath + L"\\TomatoPrefs.lua";

		// the dir exists, check log file
		std::ifstream prefFile(pathToPrefFile.c_str());
		if (prefFile.good()) {
			if (prefFile.peek() == std::ifstream::traits_type::eof()) {
				// if file is empty, create it
				try {
					TomUtils::Logger<TomUtils::FileLogPolicy> prefFileCreator(pathToPrefFile.c_str());
					std::stringstream printPref;
					printPref << "config =\r\n{ \r\n\tresolution = { width = 800, y = height }\r\n}";
					prefFileCreator.Print<TomUtils::Config>(printPref.str());
				} catch (std::runtime_error) {
					return false;
				}
			}
		} else {
			// the file does not exist, create it		
			try {
				TomUtils::Logger<TomUtils::FileLogPolicy> prefFileCreator(pathToPrefFile.c_str());
				std::stringstream printPref;
				printPref << "config =\r\n{ \r\n\tresolution = { width = 800, height = 600 }\r\n}";
				prefFileCreator.Print<TomUtils::Config>(printPref.str());
			} catch (std::runtime_error) {
				return false;
			}

			m_validConfigFile = true;
			return true;
		}

		return true;
	}

	void Application::ReadResolution() {
		std::wstring pathToPreFile = m_configFilePath + L"\\TomatoPrefs.lua";
		try {
			sol::state lua;
			//lua.script_file(Tomato::StringConverter::ws2s(pathToPreFile));
			std::string path = "C:\\dev\\git\\Tomato\\Files\\Config\\TomatoPrefs.lua";
			lua.script_file(path);
			
			// read from config file, default is 200 x 200
			m_clientWidth = lua["config"]["resolution"]["width"].get_or(200);
			m_clientHeight = lua["config"]["resolution"]["height"].get_or(200);
		} catch (std::exception) {
			TOM_LOG_WARNING("Unable to read config file!");
		}
	}

}
