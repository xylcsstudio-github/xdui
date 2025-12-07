#pragma once
#include "UIEle.h"
#include <windows.h>
#include <string>
// Text.h
/*

 *  Text class
 *  Let you draw text.
 *  This UI element is simple, only need create object to draw text.

*/

class Text : public UIEle { 
private:
    std::string m_text;
    std::wstring m_fontName;
    int m_fontSize;
    HFONT m_font;

    void CreateFontIfNeeded(HDC hdc) {
        if (m_font == NULL) {
            int height = -MulDiv(m_fontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
            m_font = CreateFontW(
                height, 0, 0, 0,
                FW_NORMAL,
                FALSE, FALSE, FALSE,
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS,
                m_fontName.c_str()
            );
        }
    }

public:
    Text() : m_text(""), m_fontName(L"Microsoft YaHei"), m_fontSize(14), m_font(NULL) {}

    Text(const std::string& text) : m_text(text), m_fontName(L"Microsoft YaHei"), m_fontSize(14), m_font(NULL) {}
    
    Text(const std::string& text, int x, int y) : m_text(text), m_fontName(L"Microsoft YaHei"), m_fontSize(14), m_font(NULL) {
        SetPos(x, y, 0, 0);
    }
    
    Text(const std::string& text, int x, int y, const std::wstring& fontName, int fontSize) 
        : m_text(text), m_fontName(fontName), m_fontSize(fontSize), m_font(NULL) {
        SetPos(x, y, 0, 0);
    }

    ~Text() {
        if (m_font != NULL) {
            DeleteObject(m_font);
        }
    }

    void SetText(const std::string& text) {
        m_text = text;
    }

    const std::string& GetText() const {
        return m_text;
    }
    
    void SetFont(const std::wstring& fontName, int fontSize) {
        m_fontName = fontName;
        m_fontSize = fontSize;
        
        // Delete old font if exists
        if (m_font != NULL) {
            DeleteObject(m_font);
            m_font = NULL;
        }
    }
    
    // Simplified drawing method that can be called easily
    void DrawAt(HDC hdc, int x, int y) {
        SetPos(x, y, 0, 0);
        Draw(hdc);
    }

    void Draw(HDC hdc)
    {
        // Save the current font
        HGDIOBJ oldFont = SelectObject(hdc, GetStockObject(SYSTEM_FONT));
        
        // Create and select our font
        CreateFontIfNeeded(hdc);
        if (m_font != NULL) {
            oldFont = SelectObject(hdc, m_font);
        }
        
        // Convert std::string to std::wstring for Unicode support
        int len = MultiByteToWideChar(CP_UTF8, 0, m_text.c_str(), -1, NULL, 0);
        LPWSTR wideStr = new WCHAR[len];
        MultiByteToWideChar(CP_UTF8, 0, m_text.c_str(), -1, wideStr, len);
        
        // Remove the null terminator for drawing (don't want extra space)
        int drawLen = len - 1;
        if (drawLen > 0) {
            ::TextOutW(hdc, GetX(), GetY(), wideStr, drawLen);
        }
        
        // Clean up allocated memory
        delete[] wideStr;
        
        // Restore the original font
        SelectObject(hdc, oldFont);
    }

};