#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <string_view>


class Display {
private:
    uint8_t width;
    uint8_t height;
    uint8_t *frame_buffer;
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    // static std::vector<int> kInternalBuffer = "Display not connected...";
public:
    // Display() : Display(32, 64, kInternalBuffer) {}
    // Display(std::vector<int>& buffer);
    Display();
    ~Display();
    void Initialize(int height, int width, const char *title);
    void PollEvents(/* const std::function<void(int, int)>& on_key */);
    void ClearScreen();
    void DrawPixel(int x, int y, int scale);
    void PresentBackBuffer();
    void Refresh();
    void Connect(uint8_t *video_in);
};



#endif // DISPLAY_H_





