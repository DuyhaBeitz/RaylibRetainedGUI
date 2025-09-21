#include <RaylibRetainedGUI/RaylibRetainedGUI.hpp>

int main() {
    InitWindow(1000, 1000, "Retained GUI minimal example");

    auto screen = std::make_shared<UIScreen>();
    auto bar = std::make_shared<UIBar>(CenteredRect(0.5, 0.5));
    
    // the position will be handled by the bar
    Rectangle rect = SizeRect(1, 0.33);

    auto text = std::make_shared<UIText>("Default text", rect);

    std::string str = "";
    auto string_button = std::make_shared<UIStringButton>(&str, rect);
    
    auto apply_button = std::make_shared<UIFuncButton>("Apply", rect);

    bar->AddChild(text);
    bar->AddChild(string_button);
    bar->AddChild(apply_button);
    
    screen->AddChild(bar);

    apply_button->BindOnReleased([text, &str](){
            text->SetText(*&str);
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