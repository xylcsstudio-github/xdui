#include "../include/Window.h"
Window::Window() :
    m_hwnd(nullptr),
    m_style(WS_OVERLAPPEDWINDOW),
    m_exStyle(0),
    m_isVisible(false),
    m_isEnabled(true),
    m_hInstance(nullptr)
{
    // Initialize position and size with default values
    m_x = CW_USEDEFAULT;
    m_y = CW_USEDEFAULT;
    m_width = CW_USEDEFAULT;
    m_height = CW_USEDEFAULT;
    m_elementType = UIElementType::Window;
}
Window::~Window()
{
    if (m_hwnd && IsWindow(m_hwnd)) {
        DestroyWindow(m_hwnd);
    }
}

// Create window
bool Window::Create(LPCTSTR className, LPCTSTR windowName, DWORD style, DWORD exStyle,
                   int x, int y, int width, int height, HWND parent, HMENU menu, HINSTANCE hInstance)
{
    m_style = style;
    m_exStyle = exStyle;
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_hInstance = hInstance;
    m_title = windowName ? windowName : L"";

    // Create window
    m_hwnd = CreateWindowEx(
        m_exStyle,
        className,
        windowName,
        m_style,
        m_x, m_y,
        m_width, m_height,
        parent,
        menu,
        m_hInstance,
        nullptr
    );

    if (!m_hwnd) {
        return false;
    }

    // Associate this object with the window
    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    
    return true;
}

// Show window
void Window::Show(int cmdShow)
{
    if (m_hwnd) {
        ShowWindow(m_hwnd, cmdShow);
        UpdateWindow(m_hwnd);
        m_isVisible = true;
    }
}

// Hide window
void Window::Hide()
{
    if (m_hwnd) {
        ShowWindow(m_hwnd, SW_HIDE);
        m_isVisible = false;
    }
}

// Update window
void Window::Update()
{
    if (m_hwnd) {
        UpdateWindow(m_hwnd);
    }
}

// Close window
void Window::Close()
{
    if (m_hwnd) {
        SendMessage(m_hwnd, WM_CLOSE, 0, 0);
    }
}

// Check if window is valid
bool Window::IsValid() const
{
    return (m_hwnd != nullptr) && IsWindow(m_hwnd);
}

// Static window procedure
LRESULT CALLBACK Window::StaticWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* pWindow = nullptr;
    
    if (msg == WM_NCCREATE) {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        pWindow = static_cast<Window*>(lpcs->lpCreateParams);
        if (pWindow) {
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
            pWindow->m_hwnd = hwnd;
        }
    } else {
        pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }
    
    if (pWindow) {
        return pWindow->HandleMessage(msg, wParam, lParam);
    }
    
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// Handle window messages
LRESULT Window::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_PAINT:
        OnPaint();
        return 0;

    case WM_SIZE:
        OnSize((UINT)wParam, LOWORD(lParam), HIWORD(lParam));
        return 0;

    case WM_DESTROY:
        OnDestroy();
        return 0;

    case WM_ACTIVATE:
        OnActivate(LOWORD(wParam), (HWND)lParam, HIWORD(wParam));
        return 0;

    case WM_COMMAND:
        OnCommand(LOWORD(wParam), HIWORD(wParam), (HWND)lParam);
        return 0;
    }

    return DefWindowProc(m_hwnd, msg, wParam, lParam);
}

// Paint handler
void Window::OnPaint()
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(m_hwnd, &ps);
    
    // Derived classes should override this method to perform custom drawing
    
    EndPaint(m_hwnd, &ps);
}

// Size handler
void Window::OnSize(UINT flag, int width, int height)
{
    // Derived classes should override this method to handle resizing
    // Store new dimensions
    m_width = width;
    m_height = height;
}

// Destroy handler
void Window::OnDestroy()
{
    // Derived classes should override this method to handle cleanup
    m_hwnd = nullptr;
    PostQuitMessage(0);
}

// Activate handler
void Window::OnActivate(UINT state, HWND hwndActDeact, BOOL minimized)
{
    // Derived classes should override this method to handle activation changes
}

// Command handler
void Window::OnCommand(UINT controlId, UINT notificationCode, HWND controlHwnd)
{
    // Derived classes should override this method to handle command messages
}

// Set title
void Window::SetTitle(const std::wstring& title)
{
    m_title = title;
    if (m_hwnd) {
        SetWindowText(m_hwnd, m_title.c_str());
    }
}

// Set style
void Window::SetStyle(DWORD style)
{
    m_style = style;
    if (m_hwnd) {
        SetWindowLong(m_hwnd, GWL_STYLE, m_style);
        SetWindowPos(m_hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
}

// Set extended style
void Window::SetExStyle(DWORD exStyle)
{
    m_exStyle = exStyle;
    if (m_hwnd) {
        SetWindowLong(m_hwnd, GWL_EXSTYLE, m_exStyle);
        SetWindowPos(m_hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
}