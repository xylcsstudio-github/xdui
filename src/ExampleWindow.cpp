#include "xdui/Window.h"
#include <windows.h>

// Simple test application to demonstrate Window class usage

class TestWindow : public Window
{
public:
    TestWindow() {}
    LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) override
    {
        switch (msg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
        return Window::HandleMessage(msg, wParam, lParam);
    }
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    TestWindow testWindow;
    
    WNDCLASS wc = { };
    wc.lpfnWndProc = TestWindow::StaticWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"TestWindowClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    RegisterClass(&wc);
    
    if (!testWindow.Create(L"TestWindowClass", L"XDUI Test Window", 
                          WS_OVERLAPPEDWINDOW, 0,
                          CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
                          nullptr, nullptr, hInstance))
    {
        return 1;
    }
    
    testWindow.Show(nCmdShow);
    
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}