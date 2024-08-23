#include <stdio.h>
#include "peripherals/display.hxx"
#include "chip8_soc.hxx"
#include <vector>
#include <cstdint>


// #include "chip8_soc.hxx"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void setK(int k, int v) {}

int main(int argc, char const *argv[]) {
    Chip8 console;
    Display screen;

    console.LoadToMem("chip8_fonts.bin", Chip8::kFontStartAddress);
    screen.Connect(console.VideoOut());

    screen.Initialize(320, 640, "Hello!");
    screen.ClearScreen();
    screen.PollEvents();


    printf("Hello to CHIP8\n");


    return 0;
}