#include <RaylibRetainedGUI/RaylibRetainedGUI.hpp>

int main() {
    InitWindow(0, 0, "Retained GUI minimal example");

    auto screen = std::make_shared<UIScreen>();
    auto bar = std::make_shared<UIBar>(CenteredRect(0.5, 0.5));
    auto text = std::make_shared<UIText>("Text example", SizeRect(1, 0.25));
    auto button = std::make_shared<UIFuncButton>("Press me!", SizeRect(1, 0.25));

    bar->AddChild(text);
    bar->AddChild(button);
    
    screen->AddChild(bar);

    button->BindOnReleased([bar](){
            bar->Close();
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