#ifndef CPU_H_
#define CPU_H_

#include <cstdint>

#include "isa.hxx"
#include "../memory/memory.hxx" // has-a relationship

class Cpu {
public:
    Memory ram_;
    Cpu(/* args */);
    [[nodiscard]] Instruction Fetch();
    [[nodiscard]] Instruction Decode();
    void Execute();

    ~Cpu();
protected:
private:
    Opcode instruction_;
    uint8_t  registers_[16] = {};
    uint8_t  stack_pointer_ = {};
    uint16_t program_counter_ = {};
    uint16_t stack_[16] = {};
};

Cpu::Cpu(/* args */)
{
}

Cpu::~Cpu()
{
}




#endif // CPU_H_ 