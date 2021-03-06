#pragma once
#include <chrono>

namespace Tomato {
	class TomatoTimer {
	public:
		TomatoTimer();
		float Mark();
		float Peek() const;
	private:
		std::chrono::steady_clock::time_point m_last;
	};
}

