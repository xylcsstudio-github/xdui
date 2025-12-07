# Text Class

The Text class is a UI element that allows you to display text in your application window. It inherits from the UIEle base class and provides easy-to-use methods for rendering text with customizable fonts and positions.

## Overview

The Text class simplifies the process of adding text to your UI. You can create text elements with just one line of code, and customize fonts, sizes, and positions as needed. By default, it uses the "Microsoft YaHei" font which matches typical Windows title bar styling.

## Constructor

```cpp
Text()
Text(const std::string& text)
Text(const std::string& text, int x, int y)
Text(const std::string& text, int x, int y, const std::wstring& fontName, int fontSize)
```

### Parameters

- `text` - The text content to display
- `x`, `y` - The position coordinates for the text
- `fontName` - The name of the font to use (wide string)
- `fontSize` - The size of the font in points

## Methods

### SetText

```cpp
void SetText(const std::string& text)
```

Sets the text content to display.

### SetFont

```cpp
void SetFont(const std::wstring& fontName, int fontSize)
```

Changes the font and font size for the text element.

### Draw

```cpp
void Draw(HDC hdc)
```

Draws the text at its configured position using the specified font.

### DrawAt

```cpp
void DrawAt(HDC hdc, int x, int y)
```

Draws the text at the specified position, updating the stored position.

## Example Usage

```cpp
#include "Text.h"

// Create text with default font (Microsoft YaHei, 14pt)
Text infoText("Welcome to XDUI!", 20, 20);

// Create text with custom font
Text titleText("Title Text", 20, 60, L"Arial", 24);
```

## Remarks

- The Text class automatically manages font resources and cleans them up when the object is destroyed
- By default, the class uses "Microsoft YaHei" font with 14pt size, which matches standard Windows UI appearance
- Position is specified in pixels from the top-left corner of the parent window
- Font names must be specified as wide strings (std::wstring)

---

# Text 类

Text类是一个UI元素，允许您在应用程序窗口中显示文本。它继承自UIEle基类，并提供了简单易用的方法来渲染具有自定义字体和位置的文本。

## 概述

Text类简化了向UI添加文本的过程。您只需一行代码就可以创建文本元素，并可根据需要自定义字体、大小和位置。默认情况下，它使用"Microsoft YaHei"字体，这与典型的Windows标题栏样式相匹配。

## 构造函数

```cpp
Text()
Text(const std::string& text)
Text(const std::string& text, int x, int y)
Text(const std::string& text, int x, int y, const std::wstring& fontName, int fontSize)
```

### 参数

- `text` - 要显示的文本内容
- `x`, `y` - 文本的位置坐标
- `fontName` - 要使用的字体名称（宽字符串）
- `fontSize` - 字体大小（磅值）

## 方法

### SetText

```cpp
void SetText(const std::string& text)
```

设置要显示的文本内容。

### SetFont

```cpp
void SetFont(const std::wstring& fontName, int fontSize)
```

更改文本元素的字体和字体大小。

### Draw

```cpp
void Draw(HDC hdc)
```

使用指定的字体在其配置的位置绘制文本。

### DrawAt

```cpp
void DrawAt(HDC hdc, int x, int y)
```

在指定位置绘制文本，并更新存储的位置。

## 使用示例

```cpp
#include "Text.h"

// 使用默认字体创建文本（Microsoft YaHei，14pt）
Text infoText("欢迎使用XDUI！", 20, 20);

// 使用自定义字体创建文本
Text titleText("标题文本", 20, 60, L"Arial", 24);
```

## 备注

- Text类会自动管理字体资源，并在对象销毁时清理它们
- 默认情况下，该类使用"Microsoft YaHei"字体，大小为14磅，这与标准Windows UI外观相匹配
- 位置以父窗口左上角为原点的像素为单位指定
- 字体名称必须指定为宽字符串（std::wstring）
