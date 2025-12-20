#pragma once
#include "UIElement.hpp"

enum UITargetDrawMode {
    UITargetDrawModeDefault = 0,
    UITargetDrawModeCentered
};

class UITarget : public UIElement {
private:
    RenderTexture2D m_render_texture;
    UITargetDrawMode m_mode = UITargetDrawModeDefault;
    
    void DrawRenderTexture() {
        Rectangle source = {};
        Rectangle dest = {};
        switch (m_mode) {
        case UITargetDrawModeDefault:
            source = Rectangle{0, 0, (float)m_render_texture.texture.width, -(float)m_render_texture.texture.height};
            dest = Rectangle{GetAbsPos().x, GetAbsPos().y, GetAbsSize().x, GetAbsSize().y};
            break;        
        case UITargetDrawModeCentered:
            source = Rectangle{0, 0, (float)m_render_texture.texture.width, -(float)m_render_texture.texture.height};
            {
                float rect_asp = GetAbsSize().x / GetAbsSize().y;
                float rend_asp = (float)m_render_texture.texture.width / (float)m_render_texture.texture.height;
                if (rend_asp <= rect_asp) {
                    float w_ratio = (rend_asp / rect_asp);
                    dest = Rectangle{GetAbsPos().x + GetAbsSize().x * (w_ratio/2.f), GetAbsPos().y, GetAbsSize().x * (1 - w_ratio), GetAbsSize().y};
                }
                else {
                    float h_ratio = 1.0f / (rend_asp / rect_asp);
                    dest = Rectangle{GetAbsPos().x, GetAbsPos().y + GetAbsSize().y * (h_ratio/2.f), GetAbsSize().x, GetAbsSize().y * (1 - h_ratio)};
                }
            }
            break;
        default:
            break;
        }    

        DrawTexturePro(
            m_render_texture.texture, 
            source,
            dest,
            Vector2{0, 0},
            0.0f,
            WHITE
        );
    }

public:
    UITarget(int target_width, int target_height, Rectangle rect = UI_FULL_RECT) 
    : UIElement(rect)
    {
        m_render_texture = LoadRenderTexture(target_width, target_height);
    }

    void Begin() {
        BeginTextureMode(m_render_texture);
    }

    void End() {
        EndTextureMode();
    }


    virtual void Draw() override {
        GetStyle()->DrawBase(*this);
        DrawRenderTexture();
        GetStyle()->DrawBorders(*this);
        DrawChildren();
    }

    void SetMode(UITargetDrawMode mode) {
        m_mode = mode;
    }
};