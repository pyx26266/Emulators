#include "chip8_soc.hxx"

#include <fstream>
#include <vector>
#include <filesystem>

void Chip8::LoadToMem(char const* file_name, uint16_t offset) {
    std::ifstream file(file_name, std::ios::binary|std::ios::in);

    // Determine the file size
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    file.read((char*)(&ram_[offset]), size);
}

uint8_t* Chip8::VideoOut() {
    return gpu.VideoOut();
}

uint8_t *Chip8::KeyInput() {
    return &ram_[0x600];
}

Chip8::Chip8() : ram_(6 * ONE_KILO_BYTE),
                 mproc(ram_),
                 gpu(&ram_[kFrameBufferStart]) {
}

Chip8::~Chip8(){}
