#pragma once
#include "UIElement.hpp"

class UISplit : public UIElement {
private:
    Orientation  m_orient;
    float m_alpha = false;
public:
    UISplit(std::shared_ptr<UIElement> elem1, std::shared_ptr<UIElement> elem2, float alpha = 0.5, Rectangle rect = UI_FULL_RECT, Orientation orient = Horizontal) 
    : UIElement(rect), m_orient(orient), m_alpha(alpha)
    {
        AddChild(elem1);
        AddChild(elem2);
        
        UpdateSplittedElems();
    }

    void UpdateSplittedElems() {
        if (m_orient == Horizontal) {
            m_children[0]->SetRelPosX(0);
            m_children[0]->SetRelWidth(m_alpha);

            m_children[1]->SetRelPosX(m_alpha);
            m_children[1]->SetRelWidth(1.0f - m_alpha);
        }
        else {
            m_children[0]->SetRelPosY(0);
            m_children[0]->SetRelHeight(m_alpha);

            m_children[1]->SetRelPosY(m_alpha);
            m_children[1]->SetRelHeight(1.0f - m_alpha);
        }
    }

    void SetAlpha(float alpha) {
        m_alpha = alpha;
        UpdateSplittedElems();
    }

    virtual void Draw() {
        GetStyle()->DrawBase(*this);
        CustomDraw();
        DrawChildren();
    }
};