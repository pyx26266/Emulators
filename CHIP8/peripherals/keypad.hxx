#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <cstdint>
#include <SDL2/SDL.h>

class Keypad {
private:
    uint8_t *keypad;
    uint8_t keymap[0x10] = {
        0x78, // X (C8: 0)
        SDLK_1, // 1 (C8: 1)
        0x32, // 2 (C8: 2)
        0x33, // 3 (C8: 3)
        0x71, // Q (C8: 4)
        0x77, // W (C8: 5)
        0x65, // E (C8: 6)
        0x61, // A (C8: 7)
        0x73, // S (C8: 8)
        0x64, // D (C8: 9)
        SDLK_a, // Z (C8: A)
        0x63, // C (C8: B)
        0x34, // 4 (C8: C)
        0x72, // R (C8: D)
        0x66, // F (C8: E)
        0x76, // V (C8: F)
    };
public:
    Keypad(/* args */);
    void Connect(uint8_t *controller_in);
    void PollEvents();
    ~Keypad();
};




#endif // KEYPAD_H_