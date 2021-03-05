#pragma once
#include "TomatoWin/TomatoWin.h"
#include "TomatoDX/TomatoDX.h"
#include "TomatoUtils/TomatoUtils.h"

namespace App
{
	class Application {
	public:
		Application();
		~Application() = default;
		int Go();
		void DoFrame();
	private:
		Tomato::Console m_console;
		Tomato::Window m_window;
	};
}