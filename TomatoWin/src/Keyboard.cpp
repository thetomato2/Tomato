#include "Keyboard.h"

namespace TomWin
{
	bool Keyboard::KeyIsPressed(unsigned char keycode) const noexcept {
		return keystates[keycode];
	}
	Keyboard::Event Keyboard::ReadKey() noexcept {
		if (keybuffer.size() > 0u) {
			Keyboard::Event e = keybuffer.front();
			keybuffer.pop();
			return e;
		} else {
			return Keyboard::Event();
		}
	}
	bool Keyboard::KeyIsEmpty() const noexcept {
		return keybuffer.empty();
	}
	char Keyboard::ReadChar() noexcept {
		if (charbuffer.size() > 0u) {
			unsigned char charcode = charbuffer.front();
			charbuffer.pop();
			return charcode;
		} else {
			return 0;
		}
	}
	bool Keyboard::CharIsEmpty() noexcept {
		return charbuffer.empty();
	}
	void Keyboard::FlushKey() noexcept {
		keybuffer = std::queue<Event>();
	}
	void Keyboard::FlushChar() noexcept {
		charbuffer = std::queue<char>();
	}
	void Keyboard::Flush() noexcept {
		FlushKey();
		FlushChar();
	}
	void Keyboard::EnableAutorepeat() noexcept {
		m_isAutorepeat = true;
	}
	void Keyboard::DisableAutorepeat() noexcept {
		m_isAutorepeat = false;
	}
	bool Keyboard::AutorepeateIsEnabled() const noexcept {
		return m_isAutorepeat;
	}
	void Keyboard::OnKeyPressed(unsigned char keycode) noexcept {
		keystates[keycode] = true;
		keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Press, keycode));
		TrimBuffer(keybuffer);
	}
	void Keyboard::OnKeyReleased(unsigned char keycode) noexcept {
		keystates[keycode] = false;
		keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Release, keycode));
		TrimBuffer(keybuffer);
	}
	void Keyboard::OnChar(char character) noexcept {
		charbuffer.push(character);
		TrimBuffer(charbuffer);
	}
	void Keyboard::ClearState() noexcept {
		keystates.reset();
	}
	template<typename T>
	void Keyboard::TrimBuffer(std::queue<T>& m_buffer) noexcept {
		while (m_buffer.size() > m_bufferSize) {
			m_buffer.pop();
		}
	}
}