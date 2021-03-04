#pragma once
#include "TomatoDX/TomatoDX.h"

namespace App
{
	class Application {
	public:
		Application();
		~Application() = default;
		int Go();
	private:
		TDX::Console m_console;
	};
}