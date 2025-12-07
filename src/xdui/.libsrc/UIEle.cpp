#include "../xdui/UIEle.h"
UIEle::UIEle() : 
    m_x(0), 
    m_y(0), 
    m_width(0), 
    m_height(0),
    m_elementType(UIElementType::Unknown),
    m_visibility(UIVisibility::Visible),
    m_enabled(true),
    m_focused(false)
{
}
UIEle::~UIEle()
{
}
void UIEle::SetPos(int x, int y, int w, int h)
{
    m_x = x;
    m_y = y;
    m_width = w;
    m_height = h;
}