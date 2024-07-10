#include <stdio.h>
#include "peripherals/display.hxx"
#include <vector>
#include <cstdint>


// #include "chip8_soc.hxx"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void setK(int k, int v) {}

int main(int argc, char const *argv[])
{
    // Chip8 console;
    // console.LoadToMem("chip8_fonts.bin", Chip8::kFontStartAddress);
    
    std::vector<int> buffer(32*64);

    Display screen((uint8_t)32, (uint8_t)64, buffer);
    screen.Initialize(320, 640, "Hello!");
    screen.ClearScreen();
    screen.PollEvents();


    printf("Hello to CHIP8\n");


    return 0;
}