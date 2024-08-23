#include "memory.hxx"

Memory::Memory(uint16_t size) {
    banks_ = new uint8_t[size];
}

Memory::~Memory() {
    delete[] banks_;
}

uint8_t& Memory::operator[](uint16_t offset)
{
    return banks_[offset];
}