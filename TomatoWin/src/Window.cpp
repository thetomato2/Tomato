#include "Window.h"
#include <sstream> 
//#include "Tomato/Macros/WindowsThrowMacros.h"
//#include "ImGui/ImGui_impl_win32.h"

namespace Tomato
{
	Window::WindowClass Window::WindowClass::wndClass_;

	Window::WindowClass::WindowClass() noexcept
		: m_hInstance(GetModuleHandle(nullptr)) {
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = HandleMsgSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetInstance();
		wc.hIcon = nullptr;
		wc.hIconSm = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = GetName();
		RegisterClassEx(&wc);
	}

	Window::WindowClass::~WindowClass() {
		UnregisterClass(m_wndClassName, GetInstance());
	}

	const char* Window::WindowClass::GetName() noexcept {
		return m_wndClassName;
	}

	HINSTANCE Window::WindowClass::GetInstance() noexcept {
		return wndClass_.m_hInstance;
	}

	// window stuff
	Window::Window(int width, int height, const char* name)
		:m_width(width), m_height(height) {
		// calculate window size based on desired client region size
		RECT wr;
		wr.left = 100;
		wr.right = width + wr.left;
		wr.top = 100;
		wr.bottom = height + wr.top;
		//if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
		//	throw TOM_LAST_EXCEPT();
		// create window and get hWnd
		m_hWnd = CreateWindow(
			WindowClass::GetName(), name,
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
			nullptr, nullptr, WindowClass::GetInstance(), this
		);
		//check for error
		//	if (m_hWnd == nullptr)
		//	throw TOM_LAST_EXCEPT();

		// newly created windows start off as hidden
		ShowWindow(m_hWnd, SW_SHOWDEFAULT);

		// init ImGui Win32 Impl
		//ImGui_ImplWin32_Init(m_hWnd);

		// create graphics object
		//m_graphics = std::make_unique<Graphics>(m_hWnd);
	}

	Window::~Window() {
	//	ImGui_ImplWin32_Shutdown();
		DestroyWindow(m_hWnd);
	}

	void Window::SetTitle(const std::string& title) {
		//if (SetWindowText(m_hWnd, title.c_str()) == 0) {
		//	throw TOM_LAST_EXCEPT();
		//}
	}

	void Window::SetForeground() const noexcept {
		::SetForegroundWindow(m_hWnd);
	}

	std::optional<int> Window::ProcessMessage() noexcept {
		MSG msg;
		// while queue has messages, remove and dispatch them (but do not block and empty queue)
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			// check for quit because PeekMessage does not signal this via a return val
			if (msg.message == WM_QUIT) {
				// return optional wrapping int (arg to PostQuitMessage is in wparam) signals quit
				return msg.wParam;
			}

			// TranslateMessage will post auxiliary WM_CHAR messages from key msgs
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// return empty optional when not quitting app
		return {};
	}

	//Graphics& Window::Gfx() {
	//	if (!m_graphics)
	//		throw TOM_NOGFX_EXCEPT();
	//	return *m_graphics;
	//}

	LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
		// use create parameter passed in from CreateWindow() to store window class pointer
		if (msg == WM_NCCREATE) {
			//extract ptr to window class from creation data
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
			// set WinAPI-managed user data to store pt to window class
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			// set message pro to normal (non-setup) handler now that setup is finished
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
			// forward message to window class handler
			return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
		}
		// if we get a message before the WM_NCREATE message, handle with default handler
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
		// retrieve ptr to window class
		Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		// forward message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {

		//if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
		//	return true;
		//}
		//const auto& imio = ImGui::GetIO();

		switch (msg) {
		case  WM_CLOSE:
			PostQuitMessage(0);
			return 0;
			// clear state when windows loses focus to prevent input getting stuck
		case WM_KILLFOCUS:
			m_keyboard.ClearState();
			break;

			//--------Keyboard------------//
		case WM_KEYDOWN:
			// ALT and F10 are not not tracked in keydown, but in syskeydown
		case WM_SYSKEYDOWN:
			// stifle this keyboard message if ImGui wants to capture
		//	if (imio.WantCaptureKeyboard) {
		//		break;
		//	}

			if (!(lParam & 0x40000000) || m_keyboard.AutorepeateIsEnabled()) // check if key was down last message
			{
				m_keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
			}
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			// stifle this keyboard message if ImGui wants to capture
			//if (imio.WantCaptureKeyboard) {
			//	break;
			//}
			m_keyboard.OnKeyReleased(static_cast<unsigned char>(wParam));
			break;
		case WM_CHAR:
			m_keyboard.OnChar(static_cast<unsigned char>(wParam));
			break;
			//------End Keyboard---------//

			//------Mouse----------------//
		case WM_MOUSEMOVE:
		{
			// stifle this keyboard message if ImGui wants to capture
			//if (imio.WantCaptureKeyboard) {
			//	break;
			//}
			const POINTS pt = MAKEPOINTS(lParam);
			// in client region -> log move and log enter + capture mouse ( if not prev in window)
			if (pt.x >= 0 && pt.x < m_width && pt.y >= 0 && pt.y < m_height) {
				m_mouse.OnMouseMove(pt.x, pt.y);
				if (!m_mouse.IsInWindow()) {
					SetCapture(hWnd);
					m_mouse.OnMouseEnter();
				}
			}
			// not in client -> log move / maintain capter if button down
			else {
				if (wParam & (MK_LBUTTON | MK_RBUTTON)) {
					m_mouse.OnMouseMove(pt.x, pt.y);
				}
				// button up -> relase capture / log event for leaving
				else {
					ReleaseCapture();
					m_mouse.OnMouseLeave();
				}
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			// stifle this keyboard message if ImGui wants to capture
			//if (imio.WantCaptureKeyboard) {
			//	break;
			//}
			const POINTS pt = MAKEPOINTS(lParam);
			m_mouse.OnLeftPressed(pt.x, pt.y);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			// stifle this keyboard message if ImGui wants to capture
			//if (imio.WantCaptureKeyboard) {
			//	break;
			//}
			const POINTS pt = MAKEPOINTS(lParam);
			m_mouse.OnRightPressed(pt.x, pt.y);
			break;
		}
		case WM_LBUTTONUP:
		{
			// stifle this keyboard message if ImGui wants to capture
			//if (imio.WantCaptureKeyboard) {
			//	break;
			//}
			const POINTS pt = MAKEPOINTS(lParam);
			m_mouse.OnLeftReleased(pt.x, pt.y);
			// release if mouse outside of window
			if (pt.x < 0 || pt.x >= m_width || pt.y < 0 || pt.y >= m_height) {
				ReleaseCapture();
				m_mouse.OnMouseLeave();
			}
			break;
		}
		case WM_RBUTTONUP:
		{
			// stifle this keyboard message if ImGui wants to capture
		//	if (imio.WantCaptureKeyboard) {
		//		break;
		//	}
			const POINTS pt = MAKEPOINTS(lParam);
			m_mouse.OnRightReleased(pt.x, pt.y);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			// stifle this keyboard message if ImGui wants to capture
			//if (imio.WantCaptureKeyboard) {
			//	break;
			//	}
			const POINTS pt = MAKEPOINTS(lParam);
			const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
			m_mouse.OnWheelDelta(pt.x, pt.y, delta);
			break;
		}
		//--------end mouse messages -------//
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}


	// handle exception stuff
	Window::HrException::HrException(int line, const char* file, HRESULT hr) noexcept
		:
		Exception(line, file),
		m_hr(hr) {
	}
	const char* Window::HrException::what() const noexcept {
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
			<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
			<< "[Description] " << GetErrorDescription() << std::endl
			<< GetOriginString();
		m_whatBuffer = oss.str();
		return m_whatBuffer.c_str();
	}

	const char* Window::HrException::GetType() const noexcept {
		return "Tomato Window Exception";
	}

	std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept {
		char* msgBuf = nullptr;
		const DWORD msgLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPSTR>(&msgBuf), 0, nullptr
		);
		if (msgLen == 0) {
			return "Unidentified error code";
		}
		std::string errorString = msgBuf;
		LocalFree(msgBuf);
		return errorString;
	}

	HRESULT Window::HrException::GetErrorCode() const noexcept {
		return m_hr;
	}

	std::string Window::HrException::GetErrorDescription() const noexcept {
		return Exception::TranslateErrorCode(m_hr);
	}

	const char* Window::NoGfxException::GetType() const noexcept {
		return "Tomato Window Exception [No Graphics]";
	}
}