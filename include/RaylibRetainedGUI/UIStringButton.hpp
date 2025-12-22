#pragma once

#include "UIFuncButton.hpp"

#include "utf8/utf8.h"

class UIStringButton : public UIFuncButton {
protected:
    std::string* m_string_ptr = nullptr;
    bool m_entering = false;
    std::string m_buffer{};
    int m_buffer_cursor_pos = 0;

    bool m_only_allowed_codepoints = false;
    std::set<int> m_allowed_codepoints;

public:
    /*
    m_string_ptr can be nullptr, if the user doesn't need outside string to be controlled
    */
    UIStringButton(std::string* ptr, Rectangle rect = UI_FULL_RECT)
     : UIFuncButton("", rect), m_string_ptr(ptr) {

        BindOnHovered([this](){
            m_entering = true;
        });
        BindOnUnhovered([this](){
            m_entering = false;
        });

        if (m_string_ptr) {
            m_buffer = *m_string_ptr;
            MoveCursorToEnd();
        }

        UpdateString();
    }

    void Clear() {
        m_buffer = "";
        *m_string_ptr = m_buffer;
        m_buffer_cursor_pos = 0;
    }

    void SetOnlyAllowedCodepoints(bool only_allowed) {
        m_only_allowed_codepoints = only_allowed;
    }

    void AddAllowedCharacters(const std::string& str) {
        const char* it = str.c_str();
        const char* end = it + str.size();

        while (it < end) {
            int cp = utf8::next(it, end);
            m_allowed_codepoints.insert(cp);
        }    
    }

    void UpdateString() {
        if (IsKeyPressed(KEY_LEFT)) {
            CursorMove(-1);
        }
        if (IsKeyPressed(KEY_RIGHT)) {
            CursorMove(1);
        }

        int cp = GetCharPressed();
        while (cp > 0 && 
            (!m_only_allowed_codepoints || m_allowed_codepoints.find(cp) != m_allowed_codepoints.end())
        ) {
            std::string utf8char;
            utf8::append(cp, std::back_inserter(utf8char));

            m_buffer.insert(m_buffer_cursor_pos, utf8char);
            CursorMove(1);
        
            cp = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            do {
                CursorMove(-1);
                EraseAtCursor();
            }
            while (m_buffer_cursor_pos > 0 && IsKeyDown(KEY_LEFT_CONTROL));
        }

        if (IsKeyPressed(KEY_DELETE))
        {
            do {
                EraseAtCursor();
            }
            while (m_buffer_cursor_pos < m_buffer.size() && IsKeyDown(KEY_LEFT_CONTROL));
            
        }

        if (IsKeyPressed(KEY_V) && IsKeyDown(KEY_LEFT_CONTROL))
        {
            const char* clipboard = GetClipboardText( );
            std::string temp(clipboard);
            m_buffer.insert(m_buffer_cursor_pos, temp);
        }

        if (IsKeyPressed(KEY_HOME)) {
            MoveCursorToStart();
        }
        if (IsKeyPressed(KEY_END)) {
            MoveCursorToEnd();
        }

        m_text = m_buffer;
        if (m_string_ptr) *m_string_ptr = m_text;
    }

    void EraseAtCursor() {
        if (m_buffer.size() > 0 && m_buffer_cursor_pos < m_buffer.size()) {
            int size = 0;
            GetCodepointNext(m_buffer.c_str() + m_buffer_cursor_pos, &size);
            m_buffer.erase(
                m_buffer.begin()+m_buffer_cursor_pos,
                m_buffer.begin()+m_buffer_cursor_pos+size
            );
        }
    }

    bool CursorCanMoveLeft() {
        return m_buffer_cursor_pos > 0;
    }

    bool CursorCanMoveRight() {
        return m_buffer_cursor_pos < (int)m_buffer.size();
    }

    void ClampStringCursorPos() {
        m_buffer_cursor_pos = std::max(m_buffer_cursor_pos, 0);
        m_buffer_cursor_pos = std::min(m_buffer_cursor_pos, int(m_buffer.size()));
    }

    void MoveCursorToStart() {
        while (CursorCanMoveLeft()) {
            CursorMove(-1);
        }
    }

    void MoveCursorToEnd() {
        while (CursorCanMoveRight()) {
            CursorMove(1);
        }
    }

    void CursorMove(int delta) {
        if (delta == 0 || m_buffer.empty()) return;

        // Move right
        if (delta > 0) {
            int remaining = delta;
            while (remaining-- > 0) {
                // can reach size = the end of the string, past all characters
                if (m_buffer_cursor_pos >= (int)m_buffer.size()) break;

                int size = 0;
                GetCodepointNext(m_buffer.c_str() + m_buffer_cursor_pos, &size);

                if (size <= 0) size = 1; // cursor always advances

                m_buffer_cursor_pos += size;
            }
        }

        // Move left
        else {
            int remaining = -delta;
            while (remaining-- > 0 && m_buffer_cursor_pos > 0) {
                int size = 0;
                GetCodepointPrevious(m_buffer.c_str() + m_buffer_cursor_pos, &size);
                if (size <= 0) size = 1; // cursor always advances
                m_buffer_cursor_pos -= size;
            }
        }

        ClampStringCursorPos();
    }

    virtual void CustomDraw() override {
        std::string text_to_draw = m_text;
        if (m_entering) text_to_draw.insert(text_to_draw.begin()+m_buffer_cursor_pos, '|');
        DrawText(text_to_draw);
    }

    virtual void CustomUpdate(std::shared_ptr<UIElement> parent_element) override {
        UpdateButtonState();
        if (m_entering) UpdateString();
    };
};