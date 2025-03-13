#ifndef RENDER_WINDOW_H_INCLUDED
#define RENDER_WINDOW_H_INCLUDED
#include <windows.h>
#include "define.h"
#include "Timer.h"
class Graphics;


class Window
{
public:
    explicit Window( HINSTANCE hInstance, uint16 width = 1920, uint16 height = 1080, char const* title = "TestWindow" );
    ~Window();

    bool Update();

    [[nodiscard]] bool IsOpen() const;

    [[nodiscard]] uint16 GetWidth() const;
    [[nodiscard]] uint16 GetHeight() const;
    [[nodiscard]] HINSTANCE GetHInstance() const;
    [[nodiscard]] HWND GetHWND() const;

    Graphics* GetGraphics();

private:
    inline static Window* s_pInstance = nullptr;

    LRESULT CALLBACK MessageProcessing( HWND hwnd, uint32 message, WPARAM wParam, LPARAM lParam );

    void Resize();

    uint16 m_width = 1920;
    uint16 m_height = 1080;
    char const* m_title = "TestWindow";

    HINSTANCE m_hInstance = nullptr;
    HWND m_HWND = nullptr;

    bool m_open = true;
    bool m_shouldResize = false;

    Graphics* m_pGraphics = nullptr;

    friend LRESULT CALLBACK MsgProc( HWND, uint32, WPARAM, LPARAM );
    friend class Graphics;
};


#include "Window.inl"

#endif