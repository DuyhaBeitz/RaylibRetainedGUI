#pragma once
#include "UIStringButton.hpp"
#include <stdexcept>

class UIFloatButton : public UIStringButton {
    float* m_float_ptr;
public:
    UIFloatButton(float* float_ptr, Rectangle rect = UI_FULL_RECT)
     : UIStringButton(nullptr, rect, CHAR_DIGIT_MIN, CHAR_DIGIT_MAX), m_float_ptr(float_ptr) {
        AddAllowedCharacter('.');
        AddAllowedCharacter('-');
        
        UpdateString();
        UpdateFloat();
    }

    void UpdateFloat() {
        try {
            *m_float_ptr = std::stof(m_text);
            //std::cout << "Converted integer: " << *m_int_ptr << std::endl;
        } catch (const std::invalid_argument& e) {
            *m_float_ptr = 0;
            //std::cerr << "Invalid argument: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            *m_float_ptr = 0;
            //std::cerr << "Out of range: " << e.what() << std::endl;
        }
    }

    virtual void Update(std::shared_ptr<UIElement> parent_element) override {
        UpdateAbsTransform(parent_element);
        UpdateChildren();
        UpdateButtonState();
        if (m_entering) {
            UpdateString();
            UpdateFloat();
        }
    };
};