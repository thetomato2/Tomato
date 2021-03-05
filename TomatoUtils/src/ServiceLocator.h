#pragma once
#include "Log.h"							// logging

namespace Tomato
{
	class ServiceLocator {
	private:
		static std::shared_ptr<Logger<FileLogPolicy> > m_fileLogger;		

	public:

		// file logging services
		static Logger<FileLogPolicy>* GetFileLogger() { return m_fileLogger.get(); };
		static void ProvideFileLoggingService(std::shared_ptr<Logger<FileLogPolicy> > providedFileLogger);
	};
}