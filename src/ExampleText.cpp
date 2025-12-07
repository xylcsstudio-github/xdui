#include <windows.h>
#include "xdui/Text.h"
#include <string>

// Global text elements with different fonts
Text titleText("Welcome to XDUI!", 20, 20, L"Microsoft YaHei", 24);
Text infoText("This is a simple text element example.", 20, 60);
Text customFontText("Custom Font Text", 20, 100, L"Arial", 18);
Text footerText("Powered by XDUI Framework", 20, 140);

// Window procedure for our example window
LRESULT CALLBACK ExampleWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        // Simply draw the text elements - much easier now!
        titleText.Draw(hdc);
        infoText.Draw(hdc);
        customFontText.Draw(hdc);
        footerText.Draw(hdc);
        
        EndPaint(hwnd, &ps);
        break;
    }
    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
        
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register window class
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = ExampleWndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"SimpleTextWindowClass";
    
    RegisterClassEx(&wc);
    
    // Create window
    HWND hwnd = CreateWindowEx(
        0,
        L"SimpleTextWindowClass",
        L"Simple XDUI Text Example",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
        NULL, NULL, hInstance, NULL
    );
    
    if (!hwnd) {
        return 1;
    }
    
    // Show window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}