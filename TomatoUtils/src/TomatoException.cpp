#include "TomatoException.h"
#include <sstream>

namespace TomUtils

{
	TomatoException::TomatoException(int line, const char* file) noexcept
		: m_line(line), m_file(file) {
	}

	const char* TomatoException::what() const noexcept {
		std::ostringstream oss;
		oss << GetType() << std::endl << GetOriginString();
		m_whatBuffer = oss.str();
		return m_whatBuffer.c_str();
	}

	const char* TomatoException::GetType() const noexcept {
		return "Tomato Exception";
	}

	int TomatoException::GetLine() const noexcept {
		return m_line;
	}

	const std::string& TomatoException::GetFile() const noexcept {
		return m_file;
	}

	std::string TomatoException::GetOriginString() const noexcept {
		std::ostringstream oss;
		oss << "[File] " << m_file << std::endl << "[Line] " << m_line;
		return oss.str();
	}
}