#pragma once
#include "UIText.hpp"

enum ButtonState {
    BTN_DEFAULT = 0,
    BTN_HOVERED = 1,
    BTN_PRESSED = 2
};

class UIFuncButton : public UIText {
public:
    UIFuncButton(std::string text, Rectangle rect = UI_FULL_RECT)
    : UIText(text, rect)
    {}
    
    void UpdateButtonState() {
        bool in_rec = CheckCollisionPointRec(GetMousePosition(), GetRect());
        bool pressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        prev_state = state;
        if (in_rec) {
            if (pressed) state = BTN_PRESSED;
            else state = BTN_HOVERED;
        }
        else {
            state = BTN_DEFAULT;
        }

        if (prev_state != state) {
            // Released: leaving PRESSED to anything else
            if (prev_state == BTN_PRESSED && on_released && in_rec) {
                on_released();
            }

            // Hovered/unhovered transitions
            if (prev_state == BTN_DEFAULT && state == BTN_HOVERED && on_hovered) {
                on_hovered();
            } else if (prev_state == BTN_HOVERED && state == BTN_DEFAULT && on_unhovered) {
                on_unhovered();
            }

            // Pressed: entering PRESSED
            if (state == BTN_PRESSED && on_pressed) {
                on_pressed();
            }
        }

        switch (state) {
        case BTN_PRESSED:
            m_text_tint = GetStyle()->m_button_text_pressed_color;
            break;
        case BTN_HOVERED:
            m_text_tint = GetStyle()->m_button_text_hovered_color;
            break;
        case BTN_DEFAULT:
            m_text_tint = GetStyle()->m_button_text_default_color;
            break;
        }
    }

    virtual void Update(std::shared_ptr<UIElement> parent_element) {
        UpdateAbsTransform(parent_element);
        UpdateChildren();
        UpdateButtonState();
    };

    // void BindOnPressed(void (*func)()) {on_pressed = func;}
    // void BindOnHovered(void (*func)()) {on_hovered = func;}
    // void BindOnUnhovered(void (*func)()) {on_unhovered = func;}
    // void BindOnReleased(void (*func)()) {on_released = func;}

    void BindOnPressed(std::function<void()> func) {on_pressed = func;}
    void BindOnHovered(std::function<void()> func) {on_hovered = func;}
    void BindOnUnhovered(std::function<void()> func) {on_unhovered = func;}
    void BindOnReleased(std::function<void()> func) {on_released = func;}

    std::function<void()> GetOnPressed() { return on_pressed; }
    std::function<void()> GetOnHovered() { return on_hovered; }
    std::function<void()> GetOnUnhovered() { return on_unhovered; }
    std::function<void()> GetOnReleased() { return on_released; }

private:
    std::function<void()> on_pressed = 0;
    std::function<void()> on_hovered = 0;
    std::function<void()> on_unhovered = 0;
    std::function<void()> on_released = 0;

    ButtonState prev_state = BTN_DEFAULT;
    ButtonState state = BTN_DEFAULT;
};