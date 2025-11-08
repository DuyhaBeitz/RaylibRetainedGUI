#include "UIStyle.hpp"
#include "UIElement.hpp"

void UIStyle::DrawBase(UIElement &e) {
    DrawRectanglePro(e.GetRect(), Vector2{0, 0}, 0.f, m_background_color);
}

void UIStyle::DrawBorders(UIElement &e)  {
    DrawRectangleLinesEx(e.GetRect(), m_line_thickness, m_line_color);
    if (e.MouseOn()) {
        DrawRectangleLinesEx(e.GetInnerRect(m_line_thickness), m_line_thickness, m_line_color);
    }
}