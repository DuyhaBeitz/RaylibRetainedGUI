#include <RaylibRetainedGUI/RaylibRetainedGUI.hpp>
#include <iostream>

int main() {
    InitWindow(1000, 1000, "Retained GUI minimal example");
    
    auto screen = std::make_shared<UIScreen>(BLACK);
    int current = 0;
    auto enu = std::make_shared<UIEnum>(&current, CenteredRect(0.8, 0.3));
    
    enu->AddItem("None");
    enu->AddItem("YELLOW");
    enu->AddItem("RED");
    enu->AddItem("GREEN");

    screen->AddChild(enu);

    while (!WindowShouldClose()) {
        screen->Update(nullptr);
        BeginDrawing();
        screen->Draw();
        DrawText(TextFormat("Index: %d", current), 100, 100, 64, WHITE);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}