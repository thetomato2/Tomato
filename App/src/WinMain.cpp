#include <Application.h>
#include "lua.hpp"

void StartLoggingService();

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	// main entry points, app will eventually be replaced by specific programs/games/etc...
	lua_State* state = luaL_newstate();
	lua_close(state);

	try { StartLoggingService(); } catch (std::runtime_error) {
		// show error message on on message box
		MessageBox(NULL, "Unable to start logging service!", "Critical Error!", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	try {

		return App::Application{}.Go();

	} catch (const Tomato::TomatoException& e) {
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	} catch (const std::exception& e) {
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	} catch (...) {
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}

void StartLoggingService() {
	//create file logger
	std::shared_ptr<Tomato::Logger<Tomato::FileLogPolicy>> engineLogger(new Tomato::Logger<Tomato::FileLogPolicy>(L"TomatoDX.log"));

	// set name of current thread
	engineLogger->SetThreadName("mainThread");

	//register the logging service
	Tomato::ServiceLocator::ProvideFileLoggingService(engineLogger);

#ifndef NDEBUG
	// print starting message
	Tomato::ServiceLocator::GetFileLogger()->Print<(Tomato::SeverityType::Info)>("The file logger was created successfully.");
#endif
}

