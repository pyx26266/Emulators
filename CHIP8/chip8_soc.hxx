// ToDo: Add license comment here.

#ifndef CHIP8_SOC_H_
#define CHIP8_SOC_H_

#include <cstdint>

#include "cpu/cpu.hxx"
#include "memory/memory.hxx"

class Chip8 {
public:
    static const uint32_t kStartAddress = 0x200;
    static const uint32_t kFontStartAddress = 0x50;

    Chip8();
    ~Chip8();
    void LoadToMem(char const *file_name, uint16_t offset);
private:
    Memory ram_; // RAM slot
    Cpu microprocessor; // CPU slot
    uint32_t video_[64*32] = {};
    uint8_t  delay_timer_ = {};
    uint8_t  sound_timer_ = {};
    uint8_t  keypad_[16] = {};
    uint16_t index_ = {};
};

#endif  // CHIP8_SOC_H_