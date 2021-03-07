#pragma once

#define TOM_EXCEPT(hr) TomWin::Window::HrException(__LINE__, __FILE__, hr) 
#define TOM_LAST_EXCEPT() TomWin::Window::HrException(__LINE__, __FILE__, GetLastError())
#define TOM_NOGFX_EXCEPT() TomWin::Window::NoGfxException(__LINE__, __FILE__)

