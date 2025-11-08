#include "UIElement.hpp"

void UIElement::FitToScreen() {
    m_abs_pos = Vector2{0, 0};
    m_abs_size.x = GetScreenWidth();
    m_abs_size.y = GetScreenHeight();
}

void UIElement::UpdateAbsTransform(std::shared_ptr<UIElement> parent_element) {
    m_abs_pos = parent_element->GetAbsPos() + parent_element->GetAbsSize() * m_rel_pos;
    m_abs_size = parent_element->GetAbsSize() * m_rel_size;
}

void UIElement::UpdateChildren() {
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->Update(shared_from_this());
    }

    int i = 0;
    while (i < m_children.size()) {
        if (m_children[i]->IsClosed()) {
            m_children.erase(m_children.begin() + i);
        } else {
            i++;
        }
    }
}

void UIElement::DrawChildren() {
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->Draw();
    }
}