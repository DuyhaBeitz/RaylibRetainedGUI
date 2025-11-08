#pragma once

#include "UIDefines.hpp"

#include <functional>
#include <set>
#include <vector>
#include <memory>
#include "UIStyle.hpp"

class UIElement : public std::enable_shared_from_this<UIElement> {
protected:
    // pos
    Vector2 m_rel_pos = Vector2{};
    Vector2 m_abs_pos = Vector2{};

    // size
    Vector2 m_rel_size = Vector2{};
    Vector2 m_abs_size = Vector2{};

    std::vector<std::shared_ptr<UIElement>> m_children{};
    bool m_closed = false;
    
    std::shared_ptr<UIStyle> GetStyle() const {
        if (!default_style) default_style = std::make_shared<UIStyle>(GetFontDefault());
        return default_style;
    }
    static inline std::shared_ptr<UIStyle> default_style = nullptr;

public:

    static void SetDefaultStyle(std::shared_ptr<UIStyle> style) { default_style = style; }

    UIElement(Rectangle rect = UI_FULL_RECT)
    : m_rel_pos(Vector2{rect.x, rect.y}),  m_rel_size(Vector2{rect.width, rect.height})
    {}

    void FitToScreen();
    void UpdateAbsTransform(std::shared_ptr<UIElement> parent_element);
    void UpdateChildren();
    
    virtual void Update(std::shared_ptr<UIElement> parent_element) {
        UpdateAbsTransform(parent_element);
        UpdateChildren();
    }

    void DrawChildren();

    virtual void Draw() {
        GetStyle()->DrawBase(*this);
        GetStyle()->DrawBorders(*this);
        DrawChildren();
    }

    // pos
    Vector2 GetRelPos() { return m_rel_pos; }
    Vector2 GetAbsPos() { return m_abs_pos; }
    void SetRelPos(Vector2 rel_pos) { m_rel_pos = rel_pos; }

    // size
    Vector2 GetRelSize() { return m_rel_size; }
    Vector2 GetAbsSize() { return m_abs_size; }
    void SetRelSize(Vector2 rel_size) { m_rel_size = rel_size; }

    Rectangle GetRect() { return Rectangle{m_abs_pos.x, m_abs_pos.y, m_abs_size.x, m_abs_size.y}; }
    Rectangle GetInnerRect(float padding) { return Rectangle{m_abs_pos.x+padding, m_abs_pos.y+padding, m_abs_size.x-padding*2, m_abs_size.y-padding*2}; }

    std::vector<std::shared_ptr<UIElement>>& GetChildren() {return m_children;}

    bool IsClosed() {return m_closed;}
    void Close() { m_closed = true; }
    void Open() { m_closed = false; }

    virtual void AddChild(std::shared_ptr<UIElement> child) { m_children.push_back(child); }

    virtual bool MouseOn() { return CheckCollisionPointRec(GetMousePosition(), GetRect()); }
};
