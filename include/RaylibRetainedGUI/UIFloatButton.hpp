#pragma once
#include "UIStringButton.hpp"
#include <charconv>

class UIFloatButton : public UIStringButton {
    float* m_float_ptr;
public:
    UIFloatButton(float* float_ptr, Rectangle rect = UI_FULL_RECT)
     : UIStringButton(nullptr, rect), m_float_ptr(float_ptr) {
        SetOnlyAllowedCodepoints(true);
        AddAllowedCharacters("0123456789-.");
        
        if (float_ptr) {
            m_buffer = std::to_string(*float_ptr);
            m_text = m_buffer;
        }
        
        UpdateString();
        UpdateFloat();
    }

    void UpdateFloat() {
        const char* str = m_text.c_str();
        float value = 0.0f;
        auto result = std::from_chars(str, str + m_text.size(), value);
        
        if (result.ec == std::errc::invalid_argument || 
            result.ec == std::errc::result_out_of_range) {
            *m_float_ptr = 0;
        } else {
            *m_float_ptr = value;
        }
    }

    virtual void CustomUpdate(std::shared_ptr<UIElement> parent_element) override {
        UpdateButtonState();
        if (m_entering) {
            UpdateString();
            UpdateFloat();
        }
    };
};