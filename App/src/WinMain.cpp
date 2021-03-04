#include <windows.h>
#include <iostream>
#include <Application.h>
#include <exception>

void Report() {
	std::cout << "App started..." << std::endl;
	TDX::TestPrint();
}

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	// main entry points, app will eventually be replaced by specific programs/games/etc...

	try {

		return App::Application{}.Go();

	} catch (const std::exception& e) {
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	} catch (...) {
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
		return -1;
}

