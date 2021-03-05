#include "ServiceLocator.h"

namespace Tomato 
{
	// file logger
	std::shared_ptr<Logger<FileLogPolicy> > ServiceLocator::m_fileLogger = NULL;
	void ServiceLocator::ProvideFileLoggingService(std::shared_ptr<Logger<FileLogPolicy> > providedFileLogger) {
		m_fileLogger = providedFileLogger;
	}
}