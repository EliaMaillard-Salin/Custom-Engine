#include "pch.h"
#include "Window.h"
#include <string>
#include "Graphics.h"


LRESULT CALLBACK MsgProc( HWND const hwnd, uint32 const message, WPARAM const wParam, LPARAM const lParam ) { return Window::s_pInstance->MessageProcessing( hwnd, message, wParam, lParam ); }


Window::Window( HINSTANCE const hInstance, uint16 const width, uint16 const height, char const* title ):
    m_width( width ),
    m_height( height ),
    m_title( title ),
    m_hInstance( hInstance )
{
    assert( s_pInstance == nullptr );
    s_pInstance = this;
    
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MsgProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = m_hInstance;
    wc.hIcon = LoadIcon( nullptr, IDI_APPLICATION );
    wc.hCursor = LoadCursor( nullptr, IDC_ARROW );
    wc.hbrBackground = static_cast<HBRUSH>( GetStockObject( NULL_BRUSH ) );
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = L"MainWindow";

    if ( RegisterClass( &wc ) == false )
    {
        MessageBox( nullptr, L"RegisterClass Failed.", nullptr, 0 );
        assert( false );
    }

    RECT rect = RECT( 0, 0, m_width, m_height );

    AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false );

    int32 const rectWidth = rect.right - rect.left;
    int32 const rectHeight = rect.bottom - rect.top;

    m_width = rectWidth;
    m_height = rectHeight;

    m_HWND = CreateWindow(
        L"MainWindow", L"Rendu",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        rectWidth, rectHeight,
        nullptr, nullptr, m_hInstance, nullptr
    );

    if ( m_HWND == nullptr )
    {
        MessageBox( nullptr, L"CreateWindow Failed.", nullptr, 0 );
        assert( false );
    }
    
    m_pGraphics = new Graphics( this );

    ShowWindow( m_HWND, SW_SHOW );
    UpdateWindow( m_HWND );
}

Window::~Window() { delete m_pGraphics; }


bool Window::Update()
{
    MSG msg = { nullptr };

    if ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
    {
        TranslateMessage( &msg );
        if (msg.message == WM_QUIT)
            return false;
        DispatchMessage( &msg );
        return true;
    }

    if ( m_shouldResize )
    {
        m_pGraphics->m_render.Resize();
        m_shouldResize = false;
    }

    return true;
}


LRESULT CALLBACK Window::MessageProcessing( HWND const hwnd, uint32 const message, WPARAM const wParam, LPARAM const lParam )
{
    switch ( message )
    {
        case WM_DESTROY:
            m_open = false;
            PostQuitMessage( 0 );
            break;

        case WM_SIZE:
            m_width = LOWORD( lParam );
            m_height = HIWORD( lParam );
            m_shouldResize = true;
            break;

        default: return DefWindowProc( hwnd, message, wParam, lParam );
    }
    return 0;
}
