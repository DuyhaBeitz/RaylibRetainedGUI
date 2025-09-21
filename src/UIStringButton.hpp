#pragma once

#include "UIFuncButton.hpp"

//#define MAX_INPUT_CHARS     128

#define CHAR_DIGIT_MIN 48 // 0
#define CHAR_DIGIT_MAX 57 // 9

#define CHAR_UPPERCASE_LETTER_MIN 64 // A
#define CHAR_UPPERCASE_LETTER_MAX 90 // Z

#define CHAR_LOWERCASE_LETTER_MIN 97 // a
#define CHAR_LOWERCASE_LETTER_MAX 122 // z

#define CHAR_ANY_MIN 32
#define CHAR_ANY_MAX 127

class UIStringButton : public UIFuncButton {
protected:
    std::string* m_string_ptr = nullptr;
    bool m_entering = false;
    std::string m_buffer{};
    int m_buffer_cursor_pos = 0;

    int m_char_min = 0;
    int m_char_max = 0;

    std::set<char> m_additional_allowed_characters;

public:
    UIStringButton(std::string* ptr, Rectangle rect = UI_FULL_RECT, int char_min = CHAR_ANY_MIN, int char_max = CHAR_ANY_MAX)
     : UIFuncButton("", rect), m_string_ptr(ptr), m_char_min(char_min), m_char_max(char_max) {
        BindOnHovered([this](){
            m_entering = true;
        });
        BindOnUnhovered([this](){
            m_entering = false;
        });
        UpdateString();
    }

    void AddAllowedCharacter(char c) {
        m_additional_allowed_characters.insert(c);
    }

    void UpdateString() {
        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        if (IsKeyPressed(KEY_LEFT)) {
            CursorMove(-1);
        }
        if (IsKeyPressed(KEY_RIGHT)) {
            CursorMove(1);
        }


        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ( ((key >= m_char_min) && (key <= m_char_max)) || m_additional_allowed_characters.find(key) != m_additional_allowed_characters.end())
            {
                m_buffer.insert(m_buffer.begin()+m_buffer_cursor_pos,(char)key);
                CursorMove(1);
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE) && m_buffer.size() > 0 && m_buffer_cursor_pos - 1 >= 0)
        {
            m_buffer.erase(m_buffer.begin()+m_buffer_cursor_pos - 1);
            CursorMove(-1);
        }
        if (IsKeyPressed(KEY_DELETE) && m_buffer.size() > 0 && m_buffer_cursor_pos < m_buffer.size())
        {
            m_buffer.erase(m_buffer.begin()+m_buffer_cursor_pos);
        }

        m_text = m_buffer;
        if (m_string_ptr) *m_string_ptr = m_text;
    }

    void ClampStringCursorPos() {
        m_buffer_cursor_pos = std::max(m_buffer_cursor_pos, 0);
        m_buffer_cursor_pos = std::min(m_buffer_cursor_pos, int(m_buffer.size()));
    }

    void CursorMove(int delta) {
        m_buffer_cursor_pos += delta;
        ClampStringCursorPos();
    }

    virtual void Draw() {
        DrawBase();
        std::string text_to_draw = m_text;
        if (m_entering) text_to_draw.insert(text_to_draw.begin()+m_buffer_cursor_pos, '|');
        DrawText(text_to_draw);
        DrawChildren();
        DrawBorders();
    }

    virtual void Update(std::shared_ptr<UIElement> parent_element) override {
        UpdateAbsTransform(parent_element);
        UpdateChildren();
        UpdateButtonState();
        if (m_entering) UpdateString();
    };
};