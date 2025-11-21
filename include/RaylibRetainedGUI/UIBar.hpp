#pragma once
#include "UIElement.hpp"

class UIBar : public UIElement {
public:
    UIBar(Rectangle rect = UI_FULL_RECT)
    : UIElement(rect) 
    {}

    virtual void AddChild(std::shared_ptr<UIElement> child) override {
        m_children.push_back(child);
        int size = m_children.size();
        if (size >= 2) {
            auto prev = m_children[size-2];
            Vector2 pos = prev->GetRelPos();
            Vector2 siz = prev->GetRelSize();
            float rel_padd = 0.05;
            m_children[size-1]->SetRelPos(
                Vector2{m_children[size-1]->GetRelPos().x, pos.y+siz.y}
            );
        }
    }
};