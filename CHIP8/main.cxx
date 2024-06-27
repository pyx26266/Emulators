#include <stdio.h>

#include "chip8_soc.hxx"

int main(int argc, char const *argv[])
{
    Chip8 console;
    console.LoadToMem("chip8_fonts.bin", Chip8::kFontStartAddress);
    
    printf("Hello to CHIP8\n");
    return 0;
}