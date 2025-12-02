# Window Class Usage Guide

## Overview

The `Window` class is a foundational component of the XDUI library that provides an object-oriented wrapper around the Windows API for creating and managing windows. This document explains how to use the `Window` class to create custom windows in your applications.

## Prerequisites

Before using the `Window` class, ensure you have:

1. A Windows development environment with Visual Studio 2026
2. Basic knowledge of Windows API programming
3. The XDUI library files included in your project

## Creating a Custom Window Class

To create a custom window, you need to inherit from the `Window` class and override necessary methods.

### Inherit from Window Class

```cpp
#include "include/Window.h"

class MyCustomWindow : public Window
{
public:
    MyCustomWindow() {}
  
    // Override the message handling method
    LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) override
    {
        switch (msg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
          
        case WM_PAINT:
            OnPaint();
            return 0;
        }
      
        // Call base class for default handling
        return Window::HandleMessage(msg, wParam, lParam);
    }
  
private:
    void OnPaint()
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
      
        // Perform custom drawing here
      
        EndPaint(m_hwnd, &ps);
    }
};
```

## Creating and Displaying a Window

### Step 1: Register Window Class

In your application's entry point, register your custom window class:

```cpp
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Create an instance of your custom window
    MyCustomWindow myWindow;
  
    // Register window class
    WNDCLASS wc = { };
    wc.lpfnWndProc = MyCustomWindow::StaticWindowProc;  // Use static window procedure
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyCustomWindowClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  
    RegisterClass(&wc);
```

### Step 2: Create Window Instance

```cpp
    // Create the window
    if (!myWindow.Create(
        L"MyCustomWindowClass",     // Class name
        L"My Custom Window",        // Window title
        WS_OVERLAPPEDWINDOW,        // Window style
        0,                          // Extended style
        CW_USEDEFAULT,              // X position
        CW_USEDEFAULT,              // Y position
        800,                        // Width
        600,                        // Height
        nullptr,                    // Parent window
        nullptr,                    // Menu
        hInstance                   // Instance handle
    ))
    {
        return 1; // Failed to create window
    }
```

### Step 3: Show and Update Window

```cpp
    // Show window
    myWindow.Show(nCmdShow);
  
    // Message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
  
    return (int)msg.wParam;
}
```

## Key Methods and Properties

### Window Creation Methods

#### `Create` Method

```cpp
bool Create(
    LPCTSTR className, 
    LPCTSTR windowName, 
    DWORD style, 
    DWORD exStyle,
    int x, 
    int y, 
    int width, 
    int height, 
    HWND parent, 
    HMENU menu, 
    HINSTANCE hInstance
);
```

Creates a window with specified parameters.

Parameters:

- `className`: Registered window class name
- `windowName`: Window title
- `style`: Window style
- `exStyle`: Extended window style
- `x`, `y`: Window position
- `width`, `height`: Window dimensions
- `parent`: Parent window handle
- `menu`: Menu handle
- `hInstance`: Application instance handle

Returns: `true` if successful, `false` otherwise

### Window Management Methods

#### `Show` Method

```cpp
void Show(int cmdShow = SW_SHOW);
```

Displays the window.

Parameter:

- `cmdShow`: Show command, defaults to `SW_SHOW`

#### `Hide` Method

```cpp
void Hide();
```

Hides the window.

#### `Update` Method

```cpp
void Update();
```

Updates the window.

#### `Close` Method

```cpp
void Close();
```

Closes the window.

### Property Access Methods

#### Getters

```cpp
HWND GetHwnd() const;                    // Get window handle
const std::wstring& GetTitle() const;    // Get window title
DWORD GetStyle() const;                  // Get window style
DWORD GetExStyle() const;                // Get extended style
bool IsWindowVisible() const;            // Check visibility
bool IsWindowEnabled() const;            // Check enabled state
HINSTANCE GetHInstance() const;          // Get instance handle
```

#### Setters

```cpp
void SetTitle(const std::wstring& title);  // Set window title
void SetStyle(DWORD style);                // Set window style
void SetExStyle(DWORD exStyle);            // Set extended style
```

## Message Handling

The `Window` class uses a virtual message handling system that allows derived classes to customize behavior for specific messages.

### `HandleMessage` Method

```cpp
virtual LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
```

Override this method to handle specific Windows messages in your derived class.

Example:

```cpp
LRESULT MyCustomWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) override
{
    switch (msg)
    {
    case WM_LBUTTONDOWN:
        // Handle left mouse button down
        return 0;
      
    case WM_KEYDOWN:
        // Handle key down
        return 0;
    }
  
    // Call base class for unhandled messages
    return Window::HandleMessage(msg, wParam, lParam);
}
```

## Complete Example

Here's a complete example demonstrating how to create a simple window using the `Window` class:

```cpp
#include "include/Window.h"
#include <windows.h>

// Custom window class
class SimpleWindow : public Window
{
public:
    SimpleWindow() {}
  
    LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) override
    {
        switch (msg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
          
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(m_hwnd, &ps);
              
                // Draw a simple text
                TextOut(hdc, 10, 10, L"Hello, XDUI Window!", 20);
              
                EndPaint(m_hwnd, &ps);
            }
            return 0;
        }
      
        return Window::HandleMessage(msg, wParam, lParam);
    }
};

// Application entry point
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Create window instance
    SimpleWindow window;
  
    // Register window class
    WNDCLASS wc = { };
    wc.lpfnWndProc = SimpleWindow::StaticWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SimpleWindowClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  
    RegisterClass(&wc);
  
    // Create window
    if (!window.Create(
        L"SimpleWindowClass",
        L"Simple XDUI Window",
        WS_OVERLAPPEDWINDOW,
        0,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        nullptr, nullptr, hInstance))
    {
        return 1;
    }
  
    // Show window
    window.Show(nCmdShow);
  
    // Message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
  
    return (int)msg.wParam;
}
```



# 窗口类使用指南

## 概述

Window类是XDUI库的基础组件，它为创建和管理Windows窗口提供了面向对象的封装。本文档将介绍如何使用Window类在应用程序中创建自定义窗口。

## 前提条件

在使用Window类之前，请确保您具备：

1. 配备Visual Studio 2026的Windows开发环境
2. Windows API编程基础知识
3. XDUI库文件已包含在您的项目中

## 创建自定义窗口类

要创建自定义窗口，您需要从Window类继承并重写必要方法。

### 从Window类继承

```cpp
#include "include/Window.h"

class MyCustomWindow : public Window
{
public:
    MyCustomWindow() {}
  
    // 重写消息处理方法
    LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) override
    {
        switch (msg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
          
        case WM_PAINT:
            OnPaint();
            return 0;
        }
      
        // 调用基类进行默认处理
        return Window::HandleMessage(msg, wParam, lParam);
    }
  
private:
    void OnPaint()
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
      
        // 在此处执行自定义绘制
      
        EndPaint(m_hwnd, &ps);
    }
};
```

## 创建并显示窗口

### 步骤1：注册窗口类

在应用程序入口点注册您的自定义窗口类：

```cpp
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // 创建自定义窗口实例
    MyCustomWindow myWindow;
  
    // 注册窗口类
    WNDCLASS wc = { };
    wc.lpfnWndProc = MyCustomWindow::StaticWindowProc;  // 使用静态窗口过程
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyCustomWindowClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  
    RegisterClass(&wc);
```

### 步骤2：创建窗口实例

```cpp
    // 创建窗口
    if (!myWindow.Create(
        L"MyCustomWindowClass",     // 类名
        L"My Custom Window",        // 窗口标题
        WS_OVERLAPPEDWINDOW,        // 窗口样式
        0,                          // 扩展样式
        CW_USEDEFAULT,              // X坐标
        CW_USEDEFAULT,              // Y坐标
        800,                        // 宽度
        600,                        // 高度
        nullptr,                    // 父窗口
        nullptr,                    // 菜单
        hInstance                   // 实例句柄
    ))
    {
        return 1; // 创建窗口失败
    }
```

### 步骤3：显示和更新窗口

```cpp
    // 显示窗口
    myWindow.Show(nCmdShow);
  
    // 消息循环
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
  
    return (int)msg.wParam;
}
```

## 关键方法和属性

### 窗口创建方法

#### Create方法

```cpp
bool Create(
    LPCTSTR className, 
    LPCTSTR windowName, 
    DWORD style, 
    DWORD exStyle,
    int x, 
    int y, 
    int width, 
    int height, 
    HWND parent, 
    HMENU menu, 
    HINSTANCE hInstance
);
```

使用指定参数创建窗口。

参数:

- `className`: 已注册的窗口类名
- `windowName`: 窗口标题
- `style`: 窗口样式
- `exStyle`: 扩展窗口样式
- `x`, `y`: 窗口位置
- `width`, `height`: 窗口尺寸
- `parent`: 父窗口句柄
- `menu`: 菜单句柄
- `hInstance`: 应用程序实例句柄

返回值: 成功返回true，否则返回false

### 窗口管理方法

#### Show方法

```cpp
void Show(int cmdShow = SW_SHOW);
```

显示窗口。

参数:

- `cmdShow`: 显示命令，默认为SW_SHOW

#### Hide方法

```cpp
void Hide();
```

隐藏窗口。

#### Update方法

```cpp
void Update();
```

更新窗口。

#### Close方法

```cpp
void Close();
```

关闭窗口。

### 属性访问方法

#### 获取器

```cpp
HWND GetHwnd() const;                    // 获取窗口句柄
const std::wstring& GetTitle() const;    // 获取窗口标题
DWORD GetStyle() const;                  // 获取窗口样式
DWORD GetExStyle() const;                // 获取扩展样式
bool IsWindowVisible() const;            // 检查可见性
bool IsWindowEnabled() const;            // 检查启用状态
HINSTANCE GetHInstance() const;          // 获取实例句柄
```

#### 设置器

```cpp
void SetTitle(const std::wstring& title);  // 设置窗口标题
void SetStyle(DWORD style);                // 设置窗口样式
void SetExStyle(DWORD exStyle);            // 设置扩展样式
```

## 消息处理

Window类使用虚拟消息处理系统，允许派生类为特定消息自定义行为。

### HandleMessage方法

```cpp
virtual LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
```

在派生类中重写此方法以处理特定的Windows消息。

示例:

```cpp
LRESULT MyCustomWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) override
{
    switch (msg)
    {
    case WM_LBUTTONDOWN:
        // 处理鼠标左键按下
        return 0;
      
    case WM_KEYDOWN:
        // 处理按键按下
        return 0;
    }
  
    // 为未处理的消息调用基类
    return Window::HandleMessage(msg, wParam, lParam);
}
```

## 完整示例

以下是一个完整的示例，演示如何使用Window类创建简单窗口：

```cpp
#include "include/Window.h"
#include <windows.h>

// 自定义窗口类
class SimpleWindow : public Window
{
public:
    SimpleWindow() {}
  
    LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) override
    {
        switch (msg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
          
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(m_hwnd, &ps);
              
                // 绘制简单文本
                TextOut(hdc, 10, 10, L"Hello, XDUI Window!", 20);
              
                EndPaint(m_hwnd, &ps);
            }
            return 0;
        }
      
        return Window::HandleMessage(msg, wParam, lParam);
    }
};

// 应用程序入口点
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // 创建窗口实例
    SimpleWindow window;
  
    // 注册窗口类
    WNDCLASS wc = { };
    wc.lpfnWndProc = SimpleWindow::StaticWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SimpleWindowClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  
    RegisterClass(&wc);
  
    // 创建窗口
    if (!window.Create(
        L"SimpleWindowClass",
        L"Simple XDUI Window",
        WS_OVERLAPPEDWINDOW,
        0,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        nullptr, nullptr, hInstance))
    {
        return 1;
    }
  
    // 显示窗口
    window.Show(nCmdShow);
  
    // 消息循环
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
  
    return (int)msg.wParam;
}
```
