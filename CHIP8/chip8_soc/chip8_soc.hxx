// ToDo: Add license comment here.

#ifndef CHIP8_SOC_H_
#define CHIP8_SOC_H_

#define ONE_KILO_BYTE (1024)

#include <cstdint>

#include "../cpu/cpu.hxx"
#include "../memory/memory.hxx"
#include "../gfx/gfx.hxx"

class Chip8 {
public:
    static const uint16_t kStartAddress = 0x200;
    static const uint16_t kFontStartAddress = 0x50;
    static const uint16_t kFrameBufferStart = 0xF00;

    Chip8();
    ~Chip8();
    void LoadToMem(char const *file_name, uint16_t offset);
    void ClockTick();
    uint8_t* VideoOut();
    uint8_t* KeyInput();
private:
    Memory ram_; // RAM slot
    Cpu mproc; // CPU slot, single core
    GFX gpu;
    
    uint32_t video_[64*32] = {};
    uint8_t  delay_timer_ = {};
    uint8_t  sound_timer_ = {};
    uint8_t  keypad_[16] = {};
    uint16_t index_ = {};
};

#endif  // CHIP8_SOC_H_