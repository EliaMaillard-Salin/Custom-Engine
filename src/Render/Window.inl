#ifndef RENDER_WINDOW_INL_INCLUDED
#define RENDER_WINDOW_INL_INCLUDED
#include "Graphics.h"


inline bool Window::IsOpen() const { return m_open; }

inline uint16 Window::GetWidth() const { return m_width; }
inline uint16 Window::GetHeight() const { return m_height; }
inline HINSTANCE Window::GetHInstance() const { return m_hInstance; }
inline HWND Window::GetHWND() const { return m_HWND; }
inline Graphics* Window::GetGraphics() { return m_pGraphics; }

inline void Window::Resize() { return; }



#endif