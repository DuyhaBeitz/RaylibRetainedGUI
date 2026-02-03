#pragma once
#include "UIElement.hpp"

class UIScreen : public UIElement {
private:
    Color m_background{};
public:
    UIScreen(Color background = {0, 0, 0, 0}) : m_background(background), UIElement(Rectangle{0, 0, 0, 0}) {}

    virtual void Update(std::shared_ptr<UIElement> parent_element) override {
        FitToScreen();
        m_crop_rect = GetRect();
        UpdateChildren();
    };

    virtual void Draw() override {
        ClearBackground(m_background);
        DrawChildren();
    };
};