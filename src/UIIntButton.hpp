#pragma once

#include "UIStringButton.hpp"
#include <stdexcept>

class UIIntButton : public UIStringButton {
    int* m_int_ptr;
public:
    UIIntButton(int* int_ptr, Rectangle rect = UI_FULL_RECT)
     : UIStringButton(nullptr, rect, CHAR_DIGIT_MIN, CHAR_DIGIT_MAX), m_int_ptr(int_ptr) {
        AddAllowedCharacter('-');
       
        UpdateString();
        UpdateInt();
    }

    void UpdateInt() {
        try {
            *m_int_ptr = std::stoi(m_text);
            //std::cout << "Converted integer: " << *m_int_ptr << std::endl;
        } catch (const std::invalid_argument& e) {
            *m_int_ptr = 0;
            //std::cerr << "Invalid argument: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            *m_int_ptr = 0;
            //std::cerr << "Out of range: " << e.what() << std::endl;
        }
    }

    virtual void Update(std::shared_ptr<UIElement> parent_element) override {
        UpdateAbsTransform(parent_element);
        UpdateChildren();
        UpdateButtonState();
        if (m_entering) {
            UpdateString();
            UpdateInt();
        }
    };
};