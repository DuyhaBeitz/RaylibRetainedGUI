#pragma once
#include "UIElement.hpp"

class UISlider : public UIElement {
private:
    Orientation  m_orient;
    float m_alpha = 0.0f;
    float* m_ptr  = nullptr;

public:
    UISlider(Orientation orient, float* ptr = nullptr, Rectangle rel_rect = UI_FULL_RECT)
        : UIElement(rel_rect), m_orient(orient), m_ptr(ptr)
    {
        if (m_ptr) m_alpha = *m_ptr;
    }

    float GetAlpha() const { return m_alpha; }

    void CustomUpdate(std::shared_ptr<UIElement>) override {
        if (m_ptr) m_alpha = *m_ptr;

        if (MouseOn() && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            Vector2 p = GetAbsPos();
            Vector2 s = GetAbsSize();

            m_alpha = (m_orient == Horizontal)
                ? (m.x - p.x) / s.x
                : (m.y - p.y) / s.y;

            m_alpha = Clamp(m_alpha, 0.0f, 1.0f);
            if (m_ptr) *m_ptr = m_alpha;
        }
    }

    void CustomDraw() override {
        Vector2 p = GetAbsPos();
        Vector2 s = GetAbsSize();

        float t = m_alpha;

        Vector2 a = (m_orient == Horizontal)
            ? Vector2{ p.x,        p.y + s.y * 0.5f }
            : Vector2{ p.x + s.x * 0.5f, p.y };

        Vector2 b = (m_orient == Horizontal)
            ? Vector2{ p.x + s.x, p.y + s.y * 0.5f }
            : Vector2{ p.x + s.x * 0.5f, p.y + s.y };

        //DrawLineEx(a, b, GetStyle()->m_line_thickness, GetStyle()->m_line_color);

        Vector2 knob = (m_orient == Horizontal)
            ? Vector2{ p.x + t * s.x, p.y + s.y * 0.5f }
            : Vector2{ p.x + s.x * 0.5f, p.y + t * s.y };

        Vector2 v = (m_orient == Horizontal)
            ? Vector2{0.0f, s.y * 0.5f}
            : Vector2{s.x * 0.5f, 0.0f};

        DrawLineEx(knob+v, knob-v, GetStyle()->m_line_thickness*3, GetStyle()->m_button_text_hovered_color);
        //DrawCircleV(knob, GetStyle()->m_line_thickness* 3, GetStyle()->m_button_text_hovered_color);
    }
};