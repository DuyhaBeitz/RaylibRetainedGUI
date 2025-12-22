#pragma once
#include "UIBar.hpp"

/*
Is designed to be moved around, revealing children
It's crop rectangle is of a parent, not new
*/
class UIScrollableChildHolder : public UIBar {
public:
    UIScrollableChildHolder(Rectangle rect = UI_FULL_RECT)
    : UIBar(rect) 
    {}
   
    virtual void Update(std::shared_ptr<UIElement> parent_element) {
        UpdateAbsTransform(parent_element);

        SetCropRect(parent_element->GetCropRect());

        CustomUpdate(parent_element);
        UpdateChildren();
    }
};

class UIScrollable : public UIElement {
private:
    std::shared_ptr<UIScrollableChildHolder> m_children_holder = nullptr;
    float rel_content_height = 0.0f;
    float scroll_alpha = 0.0f;

public:
    UIScrollable(Rectangle rect = UI_FULL_RECT)
    : UIElement(rect) 
    {
        m_children_holder = std::make_shared<UIScrollableChildHolder>();
        m_children.push_back(m_children_holder);
    }

    virtual void AddChild(std::shared_ptr<UIElement> child) override {
        m_children_holder->AddChild(child);
        rel_content_height += child->GetRelSize().y;
    }

    virtual void CustomUpdate(std::shared_ptr<UIElement> parent_element) override {
        if (MouseOn()) {
            scroll_alpha -= GetMouseWheelMove() / 50.0f;
        }
        scroll_alpha = Clamp(scroll_alpha, 0.0f, 1.0f);
        
        float rel_leftover = fmax(0.0f, rel_content_height - 1.0f);
        m_children_holder->SetRelPos(Vector2{
            0.0f,
            -rel_leftover * scroll_alpha
        });
    }
};