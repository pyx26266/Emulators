#include "keypad.hxx"
#include <SDL2/SDL.h>
#include "../logging.hxx"


Keypad::Keypad(/* args */)
{
}

void Keypad::Connect(uint8_t *controller_in) {
    keypad = controller_in;
}

void Keypad::PollEvents() {
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                keypad[keymap[event.key.keysym.sym]] = 1;
                LOG_INFO("key pressed: %d", event.key.keysym.sym)
            }
            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym = SDLK_ESCAPE)
                    quit = true;
                keypad[keymap[event.key.keysym.sym]] = 0;
                LOG_INFO("key released: %d", event.key.keysym.sym)
            }
        }
    }
}

Keypad::~Keypad()
{
}