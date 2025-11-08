#pragma once
#include "UIElement.hpp"

class UIText : public UIElement {
public:
    UIText(std::string text, Rectangle rect = UI_FULL_RECT)
    : UIElement(rect), m_text(text), m_font(GetStyle()->m_font), m_font_size(64.f), m_text_tint(GetStyle()->m_text_color)
    {}

    void DrawText(std::string text) {
        Vector2 textSize = MeasureTextEx(m_font, text.c_str(), m_font_size, GetStyle()->m_text_spacing);

        // Calculate scaling factor
        float scaleX = GetRect().width / textSize.x;
        float scaleY = GetRect().height / textSize.y;
        float finalScale = fminf(scaleX, scaleY); // Use the smaller scale to ensure it fits both dimensions

        // Adjust font size based on scaling factor
        float adjustedFontSize = m_font_size * finalScale * 0.7; // 0.8 for some padding
        //float adjustedFontSize = GetScreenWidth() / 50;
        // Recalculate text size with adjusted font size (more accurate for positioning)
        textSize = MeasureTextEx(m_font, text.c_str(), adjustedFontSize, GetStyle()->m_text_spacing);

        Vector2 textPosition;
        textPosition.x = GetRect().x + (GetRect().width - textSize.x) / 2;
        textPosition.y = GetRect().y + (GetRect().height - textSize.y) / 2;

        DrawTextEx(GetStyle()->m_font, text.c_str(), textPosition, adjustedFontSize, GetStyle()->m_text_spacing, m_text_tint);
    }

    virtual void Draw() override {
        GetStyle()->DrawBase(*this);
        DrawText(m_text);
        GetStyle()->DrawBorders(*this);
        DrawChildren();
    }

    void SetTextTint(Color text_tint) { m_text_tint = text_tint;}
    void SetText(std::string text) { m_text = text; };
    std::string GetText() { return m_text; }

protected:
    std::string m_text{};
    Font m_font{};
    float m_font_size{};
    Color m_text_tint{};
};