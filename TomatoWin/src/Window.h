#pragma once
#include <memory>
#include <optional>
#include "Keyboard.h"
#include "Mouse.h"
#include <TomatoUtils/TomatoUtils.h>

#pragma once

#define TOM_EXCEPT(hr) TomWin::Window::HrException(__LINE__, __FILE__, hr) 
#define TOM_LAST_EXCEPT() TomWin::Window::HrException(__LINE__, __FILE__, GetLastError())
#define TOM_NOGFX_EXCEPT() TomWin::Window::NoGfxException(__LINE__, __FILE__)


namespace TomWin
{
	class Window {
	public:
		class Exception : public TomUtils::TomatoException{
			using TomUtils::TomatoException::TomatoException;
		public:
			static std::string TranslateErrorCode(HRESULT hr) noexcept;
		};
		class HrException : public Exception {
		public:
			HrException(int line, const char* file, HRESULT hr) noexcept;
			const char* what() const noexcept override;
			const char* GetType() const noexcept override;
			HRESULT GetErrorCode() const noexcept;
			std::string GetErrorDescription() const noexcept;
		private:
			HRESULT m_hr;
		};
		class NoGfxException : public Exception {
		public:
			using Exception::Exception;
			const char* GetType() const noexcept override;
		};
	private: // singleton manages registration/cleanup of window class
		class WindowClass {
		public:
			static const char* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;
		private:
			WindowClass() noexcept;
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
			static constexpr const char* m_wndClassName = "Tomato Direct3D Engine Window";
			static WindowClass wndClass_;
			HINSTANCE m_hInstance;
		};
	public:
		Window(int width, int height, const char* name);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		void SetTitle(const std::string& title);
		void SetForeground() const noexcept;
		void SetResolution(int width, int hieght);
		static std::optional<int> ProcessMessage() noexcept;
		//Graphics& Gfx();
	private:
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	public:
		Keyboard m_keyboard;
		Mouse m_mouse;
	private:
		int m_width;
		int m_height;
		HWND m_hWnd;
		//std::unique_ptr<Graphics> m_graphics;
	};
}

