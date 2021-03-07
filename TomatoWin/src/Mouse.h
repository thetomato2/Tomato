#pragma once
#include <queue>

namespace TomWin
{
	class Mouse {
		friend class Window;
	public:
		class Event {
		public:
			enum class Type {
				LPress,
				LRealease,
				RPress,
				RRelease,
				WheelUp,
				WheelDown,
				Move,
				Enter,
				Leave,
				Invalid
			};
		private:
			Type m_type;
			bool m_isLeftPressed;
			bool m_isRightPressed;
			int m_x;
			int m_y;
		public:
			Event() noexcept
				: m_type(Type::Invalid), m_isLeftPressed(false), m_isRightPressed(false), m_x(0), m_y(0) {
			}
			Event(Type type, const Mouse& parent) noexcept
				: m_type(type), m_isLeftPressed(parent.m_isLeftPressed), m_isRightPressed(parent.m_isRightPressed),
				m_x(parent.m_x), m_y(parent.m_y) {
			}
			bool IsValid() const noexcept {
				return m_type != Type::Invalid;
			}
			Type GetType() const noexcept {
				return m_type;
			}
			std::pair<int, int> GetPos() const noexcept {
				return { m_x, m_y };
			}
			int GetPosX() const noexcept {
				return m_x;
			}
			int GetPosY() const noexcept {
				return m_y;
			}
			bool IsLeftPressed() const noexcept {
				return m_isLeftPressed;
			}
			bool IsRightPressed() const noexcept {
				return m_isRightPressed;
			}
		};
	public:
		Mouse() = default;
		Mouse(const Mouse&) = delete;
		Mouse& operator=(const Mouse&) = delete;
		std::pair<int, int> GetPos() const noexcept;
		int GetPosX() const noexcept;
		int GetPosY() const noexcept;
		bool IsLeftPressed() const noexcept;
		bool IsRighPressed() const noexcept;
		bool IsInWindow() const noexcept;
		Mouse::Event Read() noexcept;
		inline bool IsEmpty() const noexcept { return m_buffer.empty(); }
		void Flush() noexcept;
	private:
		void OnMouseMove(int x, int y) noexcept;
		void OnMouseLeave() noexcept;
		void OnMouseEnter() noexcept;
		void OnLeftPressed(int x, int y) noexcept;
		void OnLeftReleased(int x, int y) noexcept;
		void OnRightPressed(int x, int y) noexcept;
		void OnRightReleased(int x, int y) noexcept;
		void OnWheelUp(int x, int y) noexcept;
		void OnWheelDown(int x, int y) noexcept;
		void TrimBuffer() noexcept;
		void OnWheelDelta(int x, int y, int delta) noexcept;
	private:
		static constexpr unsigned int m_bufferSize = 16u;
		int m_x;
		int m_y;
		bool m_isLeftPressed = false;
		bool m_isRightPressed = false;
		bool m_isInWindow = false;
		int m_wheelDeltaCarry = 0;
		std::queue<Event> m_buffer;
	};
}