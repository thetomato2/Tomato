#pragma once
#include "TomatoWin/TomatoWin.h"
#include "TomatoDX/TomatoDX.h"
#include "TomatoUtils/TomatoUtils.h"

namespace App
{
	class Application {
	public:
		Application();
		~Application() = default;
		int Go();
		void DoFrame();
		void StartLoggingService();
		bool IsLogger();
		bool GetMyDocumentsPath();
		bool CheckConfigFile();
		void ReadResolution();
	private:
		bool m_activeLogger;
		bool m_validConfigFile;
		int m_clientWidth;
		int m_clientHeight;
		std::wstring m_myDocumentsPath;
		std::wstring m_logFilePath;
		std::wstring m_configFilePath;
		TomWin::Console m_console;
		TomWin::Window m_window;
	};
}
// defines
#define TOM_LOG_INFO(msg) \
TomUtils::ServiceLocator::GetFileLogger()->Print<(TomUtils::SeverityType::Info)>(msg);\
SetConsoleTextAttribute(m_console.GetConOut(), 11);\
std::cout << msg << std::endl

#define TOM_LOG_DEBUG(msg) \
TomUtils::ServiceLocator::GetFileLogger()->Print<(TomUtils::SeverityType::Debug)>(msg);\
SetConsoleTextAttribute(m_console.GetConOut(), 10);\
std::cout << msg << std::endl

#define TOM_LOG_WARNING(msg) \
TomUtils::ServiceLocator::GetFileLogger()->Print<(TomUtils::SeverityType::Warning)>(msg);\
SetConsoleTextAttribute(m_console.GetConOut(), 14);\
std::cout << msg << std::endl

#define TOM_LOG_ERROR(msg) \
TomUtils::ServiceLocator::GetFileLogger()->Print<(TomUtils::SeverityType::Error)>(msg);\
SetConsoleTextAttribute(m_console.GetConOut(), 12); \
std::cout << msg << std::endl
