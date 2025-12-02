# UIEle Base Class Documentation

## Overview

The `UIEle` class is the fundamental base class for all UI elements in the XDUI library. Every UI component, whether it's a button, text field, window, or custom control, inherits from this base class. This design ensures consistency across all UI elements and provides a unified interface for handling user interactions and managing UI properties.

## Key Concepts

### Universal Base Class

All XDUI UI elements inherit from the `UIEle` base class. This inheritance hierarchy provides:

1. **Consistent Interface**: All UI elements share the same core methods and properties
2. **Unified Event Handling**: A standardized approach to handling user input
3. **Common Property Management**: Shared mechanisms for managing position, visibility, and state

### Core Properties

The `UIEle` class defines essential properties that every UI element possesses:

- **Position and Size**: x, y coordinates and width, height dimensions
- **Element Type**: Classification as Control, Window, or Display element
- **Visibility State**: Visible, Hidden, or Collapsed
- **Enabled State**: Whether the element can receive user input
- **Focus State**: Whether the element currently has keyboard focus

## Class Definition

```cpp
class UIEle
{
protected:
    // Basic position and size properties
    int m_x, m_y, m_width, m_height;
  
    // UI element type
    UIElementType m_elementType;
  
    // Visibility property
    UIVisibility m_visibility;
  
    // Enabled state
    bool m_enabled;
  
    // Focus state
    bool m_focused;

public:
    UIEle();
    virtual ~UIEle();

    // Drawing method
    virtual void Draw(HDC hdc) = 0;
  
    // Mouse event handlers
    virtual void OnMouseMove(int x, int y) = 0;
    virtual void OnMouseDown(int x, int y) = 0;
    virtual void OnMouseUp(int x, int y) = 0;
    virtual void OnMouseLeave() = 0;
    virtual void OnMouseEnter() = 0;
    virtual void OnMouseWheel(int x, int y, int delta) = 0;
    virtual void OnLButtonDblClk(int x, int y) = 0;
    virtual void OnRButtonDown(int x, int y) = 0;
    virtual void OnRButtonUp(int x, int y) = 0;
    virtual void OnMButtonDown(int x, int y) = 0;
    virtual void OnMButtonUp(int x, int y) = 0;
    virtual void OnMButtonDblClk(int x, int y) = 0;
    virtual void OnXButtonDown(int x, int y, int button) = 0;
    virtual void OnXButtonUp(int x, int y, int button) = 0;
    virtual void OnXButtonDblClk(int x, int y, int button) = 0;
    virtual void OnMouseHWheel(int x, int y, int delta) = 0;
  
    // Keyboard event handlers
    virtual void OnKeyDown(int key) = 0;
    virtual void OnKeyUp(int key) = 0;
    virtual void OnChar(char ch) = 0;
  
    // Focus event handlers
    virtual void OnFocus() = 0;
    virtual void OnKillFocus() = 0;
    virtual void OnSetFocus() = 0;
  
    // Other event handlers
    virtual void OnCaptureChanged() = 0;
    virtual void OnTimer(int id) = 0;
    virtual void OnSize(int w, int h) = 0;

    // Position and size management
    void SetPos(int x, int y, int w, int h);
  
    // Property getters
    int GetX() const { return m_x; }
    int GetY() const { return m_y; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    UIElementType GetElementType() const { return m_elementType; }
    UIVisibility GetVisibility() const { return m_visibility; }
    bool IsEnabled() const { return m_enabled; }
    bool IsFocused() const { return m_focused; }
  
    // Property setters
    void SetElementType(UIElementType type) { m_elementType = type; }
    void SetVisibility(UIVisibility visibility) { m_visibility = visibility; }
    void SetEnabled(bool enabled) { m_enabled = enabled; }
    void SetFocused(bool focused) { m_focused = focused; }
};
```

## Enumerations

### UIElementType

Defines the type classification for UI elements:

```cpp
enum class UIElementType {
    Unknown,      // Unknown type
    Control,      // Interactive control (button, textbox, etc.)
    Window,       // Window element
    Display       // Display-only element (label, image, etc.)
};
```

### UIVisibility

Defines the visibility states for UI elements:

```cpp
enum class UIVisibility {
    Visible,      // Element is visible
    Hidden,       // Element is hidden but occupies space
    Collapsed     // Element is hidden and doesn't occupy space
};
```

## Pure Virtual Methods

The `UIEle` class defines several pure virtual methods that must be implemented by all derived classes:

### Drawing Method

```cpp
virtual void Draw(HDC hdc) = 0;
```

This method is responsible for rendering the UI element. Derived classes must implement this method to define how their element appears on screen.

### Event Handling Methods

The class provides a comprehensive set of pure virtual methods for handling various user interactions:

- **Mouse Events**: Movement, clicks, wheel movements, etc.
- **Keyboard Events**: Key presses, character input, etc.
- **Focus Events**: Gaining or losing focus
- **System Events**: Timer events, sizing, capture changes, etc.

## Property Management

The base class provides standard getter and setter methods for all core properties, ensuring consistent access patterns across all UI elements.

### Position and Size

```cpp
void SetPos(int x, int y, int w, int h);
int GetX() const;
int GetY() const;
int GetWidth() const;
int GetHeight() const;
```

### Element Type

```cpp
void SetElementType(UIElementType type);
UIElementType GetElementType() const;
```

### Visibility

```cpp
void SetVisibility(UIVisibility visibility);
UIVisibility GetVisibility() const;
```

### Enabled State

```cpp
void SetEnabled(bool enabled);
bool IsEnabled() const;
```

### Focus State

```cpp
void SetFocused(bool focused);
bool IsFocused() const;
```

## Creating Custom UI Elements

To create a custom UI element, derive from `UIEle` and implement all pure virtual methods:

```cpp
#include "include/UIEle.h"

class CustomButton : public UIEle
{
public:
    CustomButton(int x, int y, int width, int height) 
    {
        SetPos(x, y, width, height);
        SetElementType(UIElementType::Control);
    }
  
    // Implement required methods
    void Draw(HDC hdc) override
    {
        // Draw button appearance
        Rectangle(hdc, m_x, m_y, m_x + m_width, m_y + m_height);
      
        // Add button text
        std::wstring text = L"Button";
        RECT rect = { m_x, m_y, m_x + m_width, m_y + m_height };
        DrawText(hdc, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
  
    // Implement event handlers
    void OnMouseDown(int x, int y) override
    {
        // Handle mouse click
        // Change button appearance to show pressed state
    }
  
    void OnMouseUp(int x, int y) override
    {
        // Handle mouse release
        // Trigger button action
    }
  
    // Implement other required methods...
    // (All pure virtual methods must be implemented)
};
```



# UIEle基类文档

## 概述

UIEle类是XDUI库中所有UI元素的基础类。每一个UI组件，无论是按钮、文本框、窗口还是自定义控件，都继承自这个基类。这种设计确保了所有UI元素之间的一致性，并为处理用户交互和管理UI属性提供了统一的接口。

## 核心概念

### 通用基类

所有XDUI UI元素都继承自UIEle基类。这种继承层次结构提供了：

1. **一致的接口**：所有UI元素共享相同的核心方法和属性
2. **统一的事件处理**：标准化的用户输入处理方法
3. **通用属性管理**：共享的位置、可见性和状态管理机制

### 核心属性

UIEle类定义了每个UI元素都拥有的基本属性：

- **位置和尺寸**：x、y坐标以及宽度、高度尺寸
- **元素类型**：分类为控件、窗口或显示元素
- **可见性状态**：可见、隐藏或折叠
- **启用状态**：元素是否可以接收用户输入
- **焦点状态**：元素当前是否拥有键盘焦点

## 类定义

```cpp
class UIEle
{
protected:
    // 基本位置和尺寸属性
    int m_x, m_y, m_width, m_height;
  
    // UI元素类型
    UIElementType m_elementType;
  
    // 可见性属性
    UIVisibility m_visibility;
  
    // 启用状态
    bool m_enabled;
  
    // 焦点状态
    bool m_focused;

public:
    UIEle();
    virtual ~UIEle();

    // 绘制方法
    virtual void Draw(HDC hdc) = 0;
  
    // 鼠标事件处理程序
    virtual void OnMouseMove(int x, int y) = 0;
    virtual void OnMouseDown(int x, int y) = 0;
    virtual void OnMouseUp(int x, int y) = 0;
    virtual void OnMouseLeave() = 0;
    virtual void OnMouseEnter() = 0;
    virtual void OnMouseWheel(int x, int y, int delta) = 0;
    virtual void OnLButtonDblClk(int x, int y) = 0;
    virtual void OnRButtonDown(int x, int y) = 0;
    virtual void OnRButtonUp(int x, int y) = 0;
    virtual void OnMButtonDown(int x, int y) = 0;
    virtual void OnMButtonUp(int x, int y) = 0;
    virtual void OnMButtonDblClk(int x, int y) = 0;
    virtual void OnXButtonDown(int x, int y, int button) = 0;
    virtual void OnXButtonUp(int x, int y, int button) = 0;
    virtual void OnXButtonDblClk(int x, int y, int button) = 0;
    virtual void OnMouseHWheel(int x, int y, int delta) = 0;
  
    // 键盘事件处理程序
    virtual void OnKeyDown(int key) = 0;
    virtual void OnKeyUp(int key) = 0;
    virtual void OnChar(char ch) = 0;
  
    // 焦点事件处理程序
    virtual void OnFocus() = 0;
    virtual void OnKillFocus() = 0;
    virtual void OnSetFocus() = 0;
  
    // 其他事件处理程序
    virtual void OnCaptureChanged() = 0;
    virtual void OnTimer(int id) = 0;
    virtual void OnSize(int w, int h) = 0;

    // 位置和尺寸管理
    void SetPos(int x, int y, int w, int h);
  
    // 属性获取器
    int GetX() const { return m_x; }
    int GetY() const { return m_y; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    UIElementType GetElementType() const { return m_elementType; }
    UIVisibility GetVisibility() const { return m_visibility; }
    bool IsEnabled() const { return m_enabled; }
    bool IsFocused() const { return m_focused; }
  
    // 属性设置器
    void SetElementType(UIElementType type) { m_elementType = type; }
    void SetVisibility(UIVisibility visibility) { m_visibility = visibility; }
    void SetEnabled(bool enabled) { m_enabled = enabled; }
    void SetFocused(bool focused) { m_focused = focused; }
};
```

## 枚举类型

### UIElementType

定义UI元素的类型分类：

```cpp
enum class UIElementType {
    Unknown,      // 未知类型
    Control,      // 交互控件（按钮、文本框等）
    Window,       // 窗口元素
    Display       // 仅显示元素（标签、图像等）
};
```

### UIVisibility

定义UI元素的可见性状态：

```cpp
enum class UIVisibility {
    Visible,      // 元素可见
    Hidden,       // 元素隐藏但仍占据空间
    Collapsed     // 元素隐藏且不占据空间
};
```

## 纯虚方法

UIEle类定义了几个必须由所有派生类实现的纯虚方法：

### 绘制方法

```cpp
virtual void Draw(HDC hdc) = 0;
```

该方法负责渲染UI元素。派生类必须实现此方法来定义其元素在屏幕上的外观。

### 事件处理方法

该类为处理各种用户交互提供了一套全面的纯虚方法：

- **鼠标事件**：移动、点击、滚轮移动等
- **键盘事件**：按键、字符输入等
- **焦点事件**：获得或失去焦点
- **系统事件**：定时器事件、尺寸调整、捕获变化等

## 属性管理

基类为所有核心属性提供了标准的getter和setter方法，确保跨所有UI元素的一致访问模式。

### 位置和尺寸

```cpp
void SetPos(int x, int y, int w, int h);
int GetX() const;
int GetY() const;
int GetWidth() const;
int GetHeight() const;
```

### 元素类型

```cpp
void SetElementType(UIElementType type);
UIElementType GetElementType() const;
```

### 可见性

```cpp
void SetVisibility(UIVisibility visibility);
UIVisibility GetVisibility() const;
```

### 启用状态

```cpp
void SetEnabled(bool enabled);
bool IsEnabled() const;
```

### 焦点状态

```cpp
void SetFocused(bool focused);
bool IsFocused() const;
```

## 创建自定义UI元素

要创建自定义UI元素，请从UIEle派生并实现所有纯虚方法：

```cpp
#include "include/UIEle.h"

class CustomButton : public UIEle
{
public:
    CustomButton(int x, int y, int width, int height) 
    {
        SetPos(x, y, width, height);
        SetElementType(UIElementType::Control);
    }
  
    // 实现必需的方法
    void Draw(HDC hdc) override
    {
        // 绘制按钮外观
        Rectangle(hdc, m_x, m_y, m_x + m_width, m_y + m_height);
      
        // 添加按钮文本
        std::wstring text = L"按钮";
        RECT rect = { m_x, m_y, m_x + m_width, m_y + m_height };
        DrawText(hdc, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
  
    // 实现事件处理程序
    void OnMouseDown(int x, int y) override
    {
        // 处理鼠标点击
        // 更改按钮外观以显示按下状态
    }
  
    void OnMouseUp(int x, int y) override
    {
        // 处理鼠标释放
        // 触发按钮动作
    }
  
    // 实现其他必需的方法...
    // (所有纯虚方法都必须实现)
};
```
