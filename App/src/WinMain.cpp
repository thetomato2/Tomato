#include <windows.h>
#include <iostream>
#include <Application.h>

void Report() {
	std::cout << "App started..." << std::endl;
	TDX::TestPrint();
}

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	
	MessageBox(NULL, "Hello, World!", "TomatoDX", MB_ICONEXCLAMATION | MB_OK);

	App::Application app;
	
	Report();

	app.Go();
	
	return 0;
}

