#pragma once
#include "Application.h"
#include "TomatoDX/TomatoDX.h"

namespace App
{
	Application::Application() {
		m_console.CreateConsole();
	}
	int Application::Application::Go() {
		int counter = 0;
		while (true) {
			std::cout << counter++ << std::endl;
		}
		return 0;
	}
}
