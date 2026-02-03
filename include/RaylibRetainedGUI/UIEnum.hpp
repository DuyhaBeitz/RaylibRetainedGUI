#pragma once

#include "UIFuncButton.hpp"
#include "UISplit.hpp"

class UIEnum : public UIElement {
private:
    std::vector<std::string> m_names{};
    int m_current_index = 0;
    
    std::shared_ptr<UISplit> m_split = nullptr;
    std::shared_ptr<UIText> m_current_text = nullptr;
    int* m_int_ptr;

public:
    UIEnum(int* int_ptr = nullptr, Rectangle rect = UI_FULL_RECT) : UIElement(rect), m_int_ptr(int_ptr){
        if (m_int_ptr) m_current_index = *m_int_ptr;

        m_current_text = std::make_shared<UIText>("?");

        auto button_left = std::make_shared<UIFuncButton>("<");
        button_left->BindOnReleased(
            [this](){AddIndex(-1);}
        );

        auto button_right = std::make_shared<UIFuncButton>(">");
        button_right->BindOnReleased(
            [this](){AddIndex(1);}
        );

        auto buttons_split = std::make_shared<UISplit>(button_left, button_right);
        m_split = std::make_shared<UISplit>(buttons_split, m_current_text, 0.3f, Rectangle{0.0f, 0.0f, 1.0f, 0.9f});

        AddChild(m_split);
    }

    virtual void CustomDraw() override {   
        if (MouseOn() && m_current_index < m_names.size() && m_current_index >= 0) {
            Vector2 pos = GetAbsPos();
            Vector2 siz = GetAbsSize();
            float cell_width = siz.x / m_names.size();
            DrawRectangle(pos.x + cell_width * m_current_index, pos.y + siz.y*0.9f, cell_width, siz.y*0.1f, GetStyle()->m_button_text_hovered_color);
        }
    };

    virtual void CustomUpdate(std::shared_ptr<UIElement> parent_element) override {
        if (m_current_index < m_names.size() && m_current_index >= 0) {
            m_current_text->SetText(m_names[m_current_index]);
        }
        else {
            m_current_text->SetText("?");
        }
        if (m_int_ptr) {
            *m_int_ptr = m_current_index;
        }
    };

    void AddIndex(int delta) {
        m_current_index += delta;
        m_current_index %= m_names.size();
    }

    void AddItem(std::string name) {
        m_names.push_back(name);
    }
};