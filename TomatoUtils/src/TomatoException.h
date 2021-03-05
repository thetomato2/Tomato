#pragma once
#include <exception>
#include <string>

namespace Tomato
{
	class TomatoException : public std::exception {
	public:
		TomatoException(int line, const char* file) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		int GetLine() const noexcept;
		const std::string& GetFile() const noexcept;
		std::string GetOriginString() const noexcept;
	protected:
		mutable std::string m_whatBuffer;
	private:
		int m_line;
		std::string m_file;
	};
}