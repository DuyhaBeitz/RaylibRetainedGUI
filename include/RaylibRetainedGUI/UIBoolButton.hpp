#pragma once
#include "UIFuncButton.hpp"

class UIBoolButton : public UIFuncButton {
private:
    bool* m_ptr = nullptr;
public:
    UIBoolButton(bool* ptr, Rectangle rect = UI_FULL_RECT)
     : UIFuncButton(""), m_ptr(ptr) {
        BindOnReleased([this](){
            *m_ptr = !*m_ptr;
        });
    }

    virtual void Draw() {
        GetStyle()->DrawBase(*this);
        if (*m_ptr) DrawRectanglePro(GetInnerRect(GetStyle()->m_line_thickness*4), Vector2{0, 0}, 0.f, GetStyle()->m_line_color);
        GetStyle()->DrawBorders(*this);
        DrawChildren();
    }
};