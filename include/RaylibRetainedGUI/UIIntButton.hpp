#pragma once

#include "UIStringButton.hpp"
#include <charconv>

class UIIntButton : public UIStringButton {
    int* m_int_ptr;
public:
    UIIntButton(int* int_ptr, Rectangle rect = UI_FULL_RECT)
     : UIStringButton(nullptr, rect), m_int_ptr(int_ptr) {
        SetOnlyAllowedCodepoints(true);
        AddAllowedCharacters("0123456789-");
       
        UpdateString();
        UpdateInt();
    }

    void UpdateInt() {
        const char* str = m_text.c_str();
        int value = 0.0f;
        auto result = std::from_chars(str, str + m_text.size(), value);
        
        if (result.ec == std::errc::invalid_argument || 
            result.ec == std::errc::result_out_of_range) {
            *m_int_ptr = 0;
        } else {
            *m_int_ptr = value;
        }
    }

    virtual void CustomUpdate(std::shared_ptr<UIElement> parent_element) override {
        UpdateButtonState();
        if (m_entering) {
            UpdateString();
            UpdateInt();
        }
    };
};