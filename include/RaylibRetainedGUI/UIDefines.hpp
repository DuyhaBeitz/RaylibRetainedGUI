#pragma once

#include <raylib.h>
#include <raymath.h>
#include <string>

#define UI_FULL_RECT Rectangle{0, 0, 1, 1}
#define UI_FULL_SIZE Vector2{1, 1}

inline Rectangle SizeRect(float width, float height) {
    return Rectangle{0, 0, width, height};
}

inline Rectangle SizeRect(Vector2 size) {
    return SizeRect(size.x, size.y);
}

inline Rectangle CenteredRect(float width, float height) {
    return Rectangle{(1-width)/2, (1-height)/2, width, height};
}

inline Rectangle CenteredRectAlignUp(float width, float height) {
    return Rectangle{(1-width)/2, 0, width, height};
}

inline Color ColorFromHex(const std::string& hex) {
    // Skip the '#' character if present
    size_t start = (hex[0] == '#') ? 1 : 0;
    size_t length = hex.length() - start;
    
    // Helper function to convert a single hex character to its integer value
    auto hexCharToInt = [](char c) -> unsigned char {
        c = std::toupper(c);
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
        return 0; // Invalid character
    };
    
    // Helper function to convert two hex characters to a byte
    auto hexToByte = [&hexCharToInt](const std::string& hex, size_t pos) -> unsigned char {
        return (hexCharToInt(hex[pos]) << 4) | hexCharToInt(hex[pos + 1]);
    };
    
    // Default values
    unsigned char r = 0, g = 0, b = 0, a = 255;
    
    // Parse based on length
    if (length >= 6) {
        r = hexToByte(hex, start);
        g = hexToByte(hex, start + 2);
        b = hexToByte(hex, start + 4);
    }
    
    if (length >= 8) {
        a = hexToByte(hex, start + 6);
    }
    
    return Color{r, g, b, a};
}