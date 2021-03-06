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
		Tomato::Console m_console;
		Tomato::Window m_window;
	};
}
// defines
#define TOM_LOG_INFO(msg) \
Tomato::ServiceLocator::GetFileLogger()->Print<(Tomato::SeverityType::Info)>(msg);\
SetConsoleTextAttribute(m_console.GetConOut(), 11);\
std::cout << msg << std::endl

#define TOM_LOG_DEBUG(msg) \
Tomato::ServiceLocator::GetFileLogger()->Print<(Tomato::SeverityType::Debug)>(msg);\
SetConsoleTextAttribute(m_console.GetConOut(), 10);\
std::cout << msg << std::endl

#define TOM_LOG_WARNING(msg) \
Tomato::ServiceLocator::GetFileLogger()->Print<(Tomato::SeverityType::Warning)>(msg);\
SetConsoleTextAttribute(m_console.GetConOut(), 14);\
std::cout << msg << std::endl

#define TOM_LOG_ERROR(msg) \
Tomato::ServiceLocator::GetFileLogger()->Print<(Tomato::SeverityType::Error)>(msg);\
SetConsoleTextAttribute(m_console.GetConOut(), 12); \
std::cout << msg << std::endl
