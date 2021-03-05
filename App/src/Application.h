#pragma once
#include "TomatoDX/TomatoDX.h"
#include "TomatoUtils/TomatoUtils.h"

namespace App
{
	class Application {
	public:
		Application();
		~Application() = default;
		int Go();
	private:
		Tomato::Console m_console;
	};
}