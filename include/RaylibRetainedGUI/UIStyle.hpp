#pragma once

#include <raylib.h>
#include "UIDefines.hpp"

class UIElement;

struct UIStyle {
    Font m_font;

    Color m_background_color;
    Color m_text_color;

    Color m_line_color;

    Color m_button_text_default_color;
    Color m_button_text_hovered_color;
    Color m_button_text_pressed_color;

    float m_line_thickness;
    float m_text_spacing;

    float m_max_text_size;

    UIStyle(Font font) :
    m_font(font),
    m_background_color(ColorFromHex("#0000007d")),
    m_text_color(ColorFromHex("#F7F7F7")),
    m_line_color(ColorFromHex("#673AB7")),
    m_button_text_default_color(m_text_color),
    m_button_text_hovered_color(ColorFromHex("#e96818ff")),
    m_button_text_pressed_color(ColorFromHex("#777777ff")),
    m_line_thickness(3.f),
    m_text_spacing(5.f),
    m_max_text_size(128)
    {}

    virtual void DrawBase(UIElement& e);
    virtual void DrawBorders(UIElement& e);
};