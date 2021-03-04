#pragma once
#include "TomatoDX/TomatoDX.h"

namespace App
{
	class Application {
	public:
		Application();
		~Application() = default;
		void Go();
	private:
		TDX::Console m_console;
	};
}