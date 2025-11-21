#pragma once
#include "UIElement.hpp"

class UISplit : public UIElement {
private:
    bool m_horizontal = false;
    float m_alpha = false;
public:
    UISplit(std::shared_ptr<UIElement> elem1, std::shared_ptr<UIElement> elem2, float alpha = 0.5, Rectangle rect = UI_FULL_RECT, bool horizontal_split = true) 
    : UIElement(rect), m_horizontal(horizontal_split), m_alpha(alpha)
    {
        AddChild(elem1);
        AddChild(elem2);
    }

    virtual void Update(std::shared_ptr<UIElement> parent_element) override {
        UpdateAbsTransform(parent_element);

        if (m_horizontal) {
            m_children[0]->SetRelPos(Vector2{0, 0});
            m_children[0]->SetRelSize(Vector2{m_alpha, 1});

            m_children[1]->SetRelPos(Vector2{m_alpha, 0});
            m_children[1]->SetRelSize(Vector2{1-m_alpha, 1});
        }
        else {
            m_children[0]->SetRelPos(Vector2{0, 0});
            m_children[0]->SetRelSize(Vector2{1, m_alpha});

            m_children[1]->SetRelPos(Vector2{0, m_alpha});
            m_children[1]->SetRelSize(Vector2{1, 1-m_alpha});
        }

        UpdateChildren();
    };

    virtual void Draw() {
        GetStyle()->DrawBase(*this);
        DrawChildren();
    }
};