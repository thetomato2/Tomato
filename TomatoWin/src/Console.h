#pragma once
#include <cstdio>
#include <iostream>
#include <tchar.h>
#include <windows.h>

namespace TomWin
{
	class Console {
	public:
		Console() = default;
		Console(const Console&) = delete;
		Console& operator=(const Console&) = delete;
		~Console() = default;
		void CreateConsole() {

			m_isActive = AllocConsole();

			if (m_isActive) {
				std::cout << "Console started...\n" << std::endl;
			} else {
				// TOM_LAST_EXCEPT();
			}

			// std::cout, std::clog, std::cerr, std::cin
			FILE* fDummy;
			freopen_s(&fDummy, "CONOUT$", "w", stdout);
			freopen_s(&fDummy, "CONOUT$", "w", stderr);
			freopen_s(&fDummy, "CONIN$", "r", stdin);
			std::cout.clear();
			std::clog.clear();
			std::cerr.clear();
			std::cin.clear();

			// std::wcout, std::wclog, std::wcerr, std::wcin
			HANDLE hConOut = CreateFile(_T("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			HANDLE hConIn = CreateFile(_T("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
			SetStdHandle(STD_ERROR_HANDLE, hConOut);
			SetStdHandle(STD_INPUT_HANDLE, hConIn);
			std::wcout.clear();
			std::wclog.clear();
			std::wcerr.clear();
			m_conOut = hConOut;
		}
		HANDLE GetConOut() const noexcept { return m_conOut; }
	private:
		bool m_isActive = false;
		HANDLE m_conOut = nullptr;
	};
}