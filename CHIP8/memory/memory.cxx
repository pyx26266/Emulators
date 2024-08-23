#include "memory.hxx"

Memory::Memory(/* args */)
{
}

Memory::~Memory()
{
}

uint8_t& Memory::operator[](uint16_t offset)
{
    return banks[offset];
}