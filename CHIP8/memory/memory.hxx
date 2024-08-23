#ifndef MEMORY_H_
#define MEMORY_H_

#include <cstdint>

class Memory
{
private:
    uint8_t *banks_;
public:
    Memory(uint16_t size);
    ~Memory();
    uint8_t& operator [] (uint16_t);
};

#endif // MEMORY_H_
