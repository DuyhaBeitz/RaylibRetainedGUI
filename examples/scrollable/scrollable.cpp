#include <RaylibRetainedGUI/RaylibRetainedGUI.hpp>
#include <iostream>

int main() {
    InitWindow(1000, 1000, "Retained GUI minimal example");
    
    auto screen = std::make_shared<UIScreen>();
    auto scrollable = std::make_shared<UIScrollable>(CenteredRect(0.5, 0.9));
    
    // the position will be handled by the bar
    int elems_count = 10;
    Rectangle rect = SizeRect(1, 1.f/elems_count);
    for (int i = 0; i < elems_count * 4; i++) {
        auto child = std::make_shared<UIText>("Scroll!", rect);
        scrollable->AddChild(child);    
    }    

    screen->AddChild(scrollable);

    while (!WindowShouldClose()) {
        screen->Update(nullptr);
        BeginDrawing();
        screen->Draw();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}