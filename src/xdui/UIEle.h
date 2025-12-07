#pragma once
// UIEle.h
/*

 *  UI element base class
 *  It is a base class for all UI elements.

*/

#include <windows.h>

// Enumeration for UI element types
enum class UIElementType {
    Unknown,      // Unknown type
    Control,      // Control element
    Window,       // Window element
    Display       // Display element (non-window)
};

// Enumeration for UI element visibility states
enum class UIVisibility {
    Visible,      // Element is visible
    Hidden,       // Element is hidden but occupies space
    Collapsed     // Element is hidden and doesn't occupy space
};

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
	 ~UIEle();

	 void Draw(HDC hdc);
	 void OnMouseMove(int x, int y);
	 void OnMouseDown(int x, int y);
	 void OnMouseUp(int x, int y);
     void OnMouseLeave();
     void OnMouseEnter();
     void OnMouseWheel(int x, int y, int delta);
     void OnKeyDown(int key);
     void OnKeyUp(int key);
     void OnChar(char ch);
     void OnFocus();
     void OnKillFocus();
     void OnSetFocus();
     void OnLButtonDblClk(int x, int y);
     void OnRButtonDown(int x, int y);
     void OnRButtonUp(int x, int y);
     void OnMButtonDown(int x, int y);
     void OnMButtonUp(int x, int y);
     void OnMButtonDblClk(int x, int y);
     void OnXButtonDown(int x, int y, int button);
     void OnXButtonUp(int x, int y, int button);
     void OnXButtonDblClk(int x, int y, int button);
     void OnMouseHWheel(int x, int y, int delta);
     void OnCaptureChanged();
     void OnTimer(int id);
     void OnSize(int w, int h);

	// Set position and size
	void SetPos(int x, int y, int w, int h);
    
    // Get position and size
    int GetX() const { return m_x; }
    int GetY() const { return m_y; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    
    // Set and get element type
    void SetElementType(UIElementType type) { m_elementType = type; }
    UIElementType GetElementType() const { return m_elementType; }
    
    // Set and get visibility
    void SetVisibility(UIVisibility visibility) { m_visibility = visibility; }
    UIVisibility GetVisibility() const { return m_visibility; }
    
    // Set and get enabled state
    void SetEnabled(bool enabled) { m_enabled = enabled; }
    bool IsEnabled() const { return m_enabled; }
    
    // Set and get focus state
    void SetFocused(bool focused) { m_focused = focused; }
    bool IsFocused() const { return m_focused; }
};