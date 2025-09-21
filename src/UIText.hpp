#pragma once
#include "UIElement.hpp"

class UIText : public UIElement {
public:
    UIText(std::string text, Rectangle rect = UI_FULL_RECT)
    : UIElement(rect), m_text(text), m_font(GetFontDefault()), m_font_size(64.f), m_spacing(UI_TEXT_SPACING), m_text_tint(UI_TEXT_COLOR)
    {}

    void DrawText(std::string text) {
        Vector2 textSize = MeasureTextEx(m_font, text.c_str(), m_font_size, m_spacing);

        // Calculate scaling factor
        float scaleX = GetRect().width / textSize.x;
        float scaleY = GetRect().height / textSize.y;
        float finalScale = fminf(scaleX, scaleY); // Use the smaller scale to ensure it fits both dimensions

        // Adjust font size based on scaling factor
        float adjustedFontSize = m_font_size * finalScale * 0.7; // 0.8 for some padding
        //float adjustedFontSize = GetScreenWidth() / 50;
        // Recalculate text size with adjusted font size (more accurate for positioning)
        textSize = MeasureTextEx(m_font, text.c_str(), adjustedFontSize, m_spacing);

        Vector2 textPosition;
        textPosition.x = GetRect().x + (GetRect().width - textSize.x) / 2;
        textPosition.y = GetRect().y + (GetRect().height - textSize.y) / 2;

        DrawTextEx(m_font, text.c_str(), textPosition, adjustedFontSize, m_spacing, m_text_tint);
    }

    virtual void Draw() override {
        DrawBase();
        DrawText(m_text);
        DrawBorders();
        DrawChildren();
    }

    void SetTextTint(Color text_tint) { m_text_tint = text_tint;}

protected:
    std::string m_text{};
    Font m_font{};
    float m_font_size{};
    float m_spacing{};
    Color m_text_tint{};
};