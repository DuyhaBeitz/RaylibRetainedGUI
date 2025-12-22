#pragma once
#include "UIElement.hpp"

class UIScreen : public UIElement {
public:
    UIScreen() : UIElement(Rectangle{0, 0, 0, 0}) {}

    virtual void Update(std::shared_ptr<UIElement> parent_element) override {
        FitToScreen();
        m_crop_rect = GetRect();
        UpdateChildren();
    };

    virtual void Draw() override {
        DrawChildren();
    };
};