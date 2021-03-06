#pragma once

#define TOM_EXCEPT(hr) Window::HrException(__LINE__, __FILE__, hr) 
#define TOM_LAST_EXCEPT() Window::HrException(__LINE__, __FILE__, GetLastError())
#define TOM_NOGFX_EXCEPT() Window::NoGfxException(__LINE__, __FILE__)

