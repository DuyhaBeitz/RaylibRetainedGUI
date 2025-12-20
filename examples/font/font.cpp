#include <RaylibRetainedGUI/RaylibRetainedGUI.hpp>
#include <iostream>

std::vector<int> CodepointsFromStr(const char* chars) {
    std::vector<int> codepoints;
    int count = 0;

    int i = 0;
    while (chars[i]) {
        int bytes = 0;
        int cp = GetCodepoint(chars + i, &bytes);
        i += bytes;
        codepoints.push_back(cp);
    }    
    return codepoints;
}
Font LoadFontForCharacters(const char *fileName, int fontSize, const char* chars) {
    std::vector<int> codepoints = CodepointsFromStr(chars);
    return LoadFontEx(fileName, fontSize, codepoints.data(), codepoints.size());
}

int main() {
    InitWindow(1000, 1000, "Retained GUI minimal example");

    Font font = LoadFontForCharacters("examples/font/NotoSans-Black.ttf", 128,
                    " !\"#$%&'()*+,-./0123456789:;<=>?@|"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz"
                    "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                    "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
    );
    UIElement::SetDefaultStyle(std::make_shared<UIStyle>(font));
    
    auto screen = std::make_shared<UIScreen>();
    auto bar = std::make_shared<UIBar>(CenteredRect(0.5, 0.9));
    
    // the position will be handled by the bar
    int elems_count = 1;
    Rectangle rect = SizeRect(1, 1.f/elems_count);

    std::string str_val = "Write something!";
    auto string_button = std::make_shared<UIStringButton>(&str_val, rect);

    bar->AddChild(string_button);
        
    screen->AddChild(bar);

    while (!WindowShouldClose()) {
        screen->Update(nullptr);
        BeginDrawing();
        screen->Draw();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}