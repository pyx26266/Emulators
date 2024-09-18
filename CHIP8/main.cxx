#include <stdio.h>
#include "peripherals/display.hxx"
#include "peripherals/keypad.hxx"
#include "chip8_soc/chip8_soc.hxx"
#include <vector>
#include <cstdint>


// #include "chip8_soc.hxx"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void setK(int k, int v) {}

int main(int argc, char const *argv[]) {
    Chip8 console;
    Display screen; screen.Connect(console.VideoOut());
    Keypad controller; controller.Connect(console.KeyInput());


    console.LoadToMem("chip8_fonts.bin", Chip8::kFontStartAddress);

    screen.Initialize(320, 640, "Hello!");
    screen.ClearScreen();
    screen.Refresh();
    screen.PresentBackBuffer();
    controller.PollEvents();


    printf("Hello to CHIP8\n");


    return 0;
}