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
        DrawBase();
        if (*m_ptr) DrawRectanglePro(GetInnerRect(UI_LINE_THICKNESS*4), Vector2{0, 0}, 0.f, UI_LINE_COLOR);
        DrawChildren();
        DrawBorders();
    }
};