#include "GUIManager.h"

#define STB_EASY_FONT_IMPLEMENTATION
#include "stb_easy_font.h"

float buffer[99999]; // big enough

void GUIManager::DrawText(float x, float y, const char* text)
{
    int num_quads = stb_easy_font_print(
        x, y,
        (char*)text,
        NULL,
        buffer,
        sizeof(buffer)
    );   

}
