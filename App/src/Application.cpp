#pragma once
#include "Application.h"
#include "TomatoDX/TomatoDX.h"

namespace App
{
	Application::Application()
	: m_window(1024, 768, "Tomato") {
		m_console.CreateConsole();
		m_window.SetForeground();
	}

	// main loop
	void Application::DoFrame() {
				
	}

	int Application::Application::Go() {	
		// start the main loop

		
		while (true) {
			// process all messages pending but do not block new messages
			if (const auto ecode = Tomato::Window::ProcessMessage()) {
				// if return optional has value it means we are quitting
				// so return exit code
				return *ecode;
			}
			DoFrame();
		}
	}
}
