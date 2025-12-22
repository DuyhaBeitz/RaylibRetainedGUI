#pragma once
#include "UIBar.hpp"
#include "UISlider.hpp"
#include "UISplit.hpp"
#include <iostream>

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
    std::shared_ptr<UISplit> m_split = nullptr;
    std::shared_ptr<UISlider> m_slider = nullptr;


    float m_rel_content_height = 0.0f;
    float m_scroll_alpha = 0.0f;

public:
    UIScrollable(Rectangle rect = UI_FULL_RECT)
    : UIElement(rect) 
    {
        m_children_holder = std::make_shared<UIScrollableChildHolder>();

        m_slider = std::make_shared<UISlider>(Orientation::Vertical, &m_scroll_alpha);

        m_split = std::make_shared<UISplit>(m_children_holder, m_slider);

        m_children.push_back(m_split);
    }

    virtual void AddChild(std::shared_ptr<UIElement> child) override {
        m_children_holder->AddChild(child);
        m_rel_content_height += child->GetRelSize().y;
    }

    virtual void CustomUpdate(std::shared_ptr<UIElement> parent_element) override {
        if (MouseOn()) {
            m_scroll_alpha -= GetMouseWheelMove() / 50.0f;
        }
        m_scroll_alpha = Clamp(m_scroll_alpha, 0.0f, 1.0f);
        
        float rel_leftover = fmax(0.0f, m_rel_content_height - 1.0f);
        m_children_holder->SetRelPos(Vector2{
            0.0f,
            -rel_leftover * m_scroll_alpha
        });
        std::cout << m_scroll_alpha << std::endl;

        m_split->SetAlpha(
            1.0f - GetStyle()->m_line_thickness * 30.0f / GetAbsSize().x
        );
    }
};