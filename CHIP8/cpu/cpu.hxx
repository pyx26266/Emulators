#ifndef CPU_H_
#define CPU_H_

#include <cstdint>

#include "isa.hxx"

class Cpu {
public:
    Cpu(/* args */);
    [[nodiscard]] Instruction Fetch();
    [[nodiscard]] Instruction Decode();
    Instruction Execute();

    ~Cpu();
protected:
    uint8_t  registers_[16] = {};
private:
    Opcode instruction_reg_;
};

Cpu::Cpu(/* args */)
{
}

Cpu::~Cpu()
{
}




#endif // CPU_H_ 