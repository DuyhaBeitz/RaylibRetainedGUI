#include <RaylibRetainedGUI/RaylibRetainedGUI.hpp>
#include <iostream>

int main() {
    InitWindow(1000, 1000, "Retained GUI minimal example");
    
    auto screen = std::make_shared<UIScreen>();
    auto bar = std::make_shared<UIBar>(CenteredRect(0.5, 0.9));
    
    // the position will be handled by the bar
    int elems_count = 2;
    Rectangle rect = SizeRect(1, 1.f/elems_count);

    auto target1 = std::make_shared<UITarget>(200, 400, rect);
    auto target2 = std::make_shared<UITarget>(200, 100, rect);

    target1->SetMode(UITargetDrawModeCentered);
    target2->SetMode(UITargetDrawModeCentered);

    bar->AddChild(target1);
    bar->AddChild(target2);
    
    screen->AddChild(bar);

    Camera3D camera{0};
    camera.up = {0, 1, 0};
    camera.fovy = 90;
    camera.target = Vector3{0.0f, 0.0f, 0.0f};
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {

        camera.position = Vector3{sinf(GetTime()), 1.0f, cosf(GetTime())} * 5.0f;

        target1->Begin();
            ClearBackground(RED);
            
            BeginMode3D(camera);
            DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 1, 1, 1, WHITE);
            DrawGrid(100, 10.0f);
            EndMode3D();
        target1->End();

        target2->Begin();
            ClearBackground(WHITE);
            
            BeginMode3D(camera);
            DrawSphere(Vector3{0.0f, 0.0f, 0.0f}, 1, GREEN);
            DrawGrid(100, 10.0f);
            EndMode3D();
        target2->End();

        screen->Update(nullptr);
        BeginDrawing();
        screen->Draw();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}