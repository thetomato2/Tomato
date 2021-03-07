#include <Shlobj.h>
#include <Shlwapi.h>
#include <Pathcch.h>

#include "Log.h"

// DLLs /////////////////////////////////////////////////////////////////////////////////
//#pragma comment(lib, "Shlwapi.lib")
//#pragma comment(lib, "Pathcch.lib")

namespace TomUtils
{
	// The openOutputStream function opens a file on the hard drive and sets the output precision
	bool FileLogPolicy::OpenOutputStream(const std::wstring& filename) {
		// try to open file
		m_outputStream.open(filename.c_str(), std::ios_base::binary | std::ios_base::out);

		// debug mode only: make sure the operation succeeded
#ifndef NDEBUG
		if (!m_outputStream.is_open())
			return false;
#endif
		m_outputStream.precision(20);

		return true;
	}

	// the closeOutputStream function closes the file on the hard drive
	void FileLogPolicy::CloseOutputStream() {
		m_outputStream.close();
	}

	// the write functions writes a message :)
	void FileLogPolicy::Write(const std::string& msg) {
		// add the message to the stream
		m_outputStream << msg << std::endl;
	}
}