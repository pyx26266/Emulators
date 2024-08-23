#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

class Display {
private:
    uint8_t width;
    uint8_t height;
    std::vector<int>& frame_buffer;
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    // static std::vector<int> kInternalBuffer = "Display not connected...";
public:
    // Display() : Display(32, 64, kInternalBuffer) {}
    Display(std::vector<int>& buffer);
    ~Display();
    void Initialize(int height, int width, std::string_view title);
    void PollEvents(/* const std::function<void(int, int)>& on_key */);
    void ClearScreen();
    void DrawPixel(int x, int y, int scale);
    void PresentBackBuffer();
};



#endif // DISPLAY_H_





