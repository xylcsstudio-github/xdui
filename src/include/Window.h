#pragma once
// Window.h
/*

 *  Window base class
 *  It is a base class for all window elements.

*/

#include "UIEle.h"
#include <windows.h>
#include <string>

class Window : public UIEle
{
protected:
    HWND m_hwnd;                    // Window handle
    std::wstring m_title;           // Window title
    DWORD m_style;                  // Window style
    DWORD m_exStyle;                // Extended window style
    bool m_isVisible;               // Visibility flag
    bool m_isEnabled;               // Enabled flag
    HINSTANCE m_hInstance;          // Application instance handle

public:
    Window();
    virtual ~Window();

    // Initialize the window
    virtual bool Create(LPCTSTR className, LPCTSTR windowName, DWORD style, DWORD exStyle, 
                       int x, int y, int width, int height, HWND parent, HMENU menu, HINSTANCE hInstance);
    
    // Show window
    virtual void Show(int cmdShow = SW_SHOW);
    
    // Hide window
    virtual void Hide();
    
    // Update window
    virtual void Update();
    
    // Close window
    virtual void Close();
    
    // Check if window is valid
    virtual bool IsValid() const;
    
    // Window procedure - this should be overridden by derived classes
    static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    // Getter methods
    HWND GetHwnd() const { return m_hwnd; }
    const std::wstring& GetTitle() const { return m_title; }
    DWORD GetStyle() const { return m_style; }
    DWORD GetExStyle() const { return m_exStyle; }
    bool IsWindowVisible() const { return m_isVisible; }
    bool IsWindowEnabled() const { return m_isEnabled; }
    HINSTANCE GetHInstance() const { return m_hInstance; }

    // Setter methods
    void SetTitle(const std::wstring& title);
    void SetStyle(DWORD style);
    void SetExStyle(DWORD exStyle);

    // Message handlers
    virtual LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
    virtual void OnPaint();
    virtual void OnSize(UINT flag, int width, int height);
    virtual void OnDestroy();
    virtual void OnActivate(UINT state, HWND hwndActDeact, BOOL minimized);
    virtual void OnCommand(UINT controlId, UINT notificationCode, HWND controlHwnd);
};