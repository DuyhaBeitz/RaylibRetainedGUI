#include <RaylibRetainedGUI/RaylibRetainedGUI.hpp>
#include <iostream>

int main() {
    InitWindow(1000, 1000, "Retained GUI minimal example");
    
    auto screen = std::make_shared<UIScreen>();
    auto bar = std::make_shared<UIBar>(CenteredRect(0.5, 0.9));
    
    // the position will be handled by the bar
    int elems_count = 5;
    Rectangle rect = SizeRect(1, 1.f/elems_count);

    auto text = std::make_shared<UIText>("Default string", rect);

    std::string str_val = "";
    auto string_button = std::make_shared<UIStringButton>(&str_val, rect);

    auto apply_button = std::make_shared<UIFuncButton>("Apply string", rect);

    int int_val = 0;
    auto int_button = std::make_shared<UIIntButton>(&int_val, rect);

    float float_val = 0;
    auto float_button = std::make_shared<UIFloatButton>(&float_val, rect);

    bar->AddChild(text);
    bar->AddChild(string_button);
    bar->AddChild(apply_button);
    bar->AddChild(int_button);    
    bar->AddChild(float_button);  
    
    screen->AddChild(bar);

    apply_button->BindOnReleased([text, &str_val](){
            text->SetText(*&str_val);
        }
    );

    while (!WindowShouldClose()) {
        screen->Update(nullptr);
        BeginDrawing();
        screen->Draw();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}