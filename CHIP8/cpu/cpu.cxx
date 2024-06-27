

#include "cpu.hxx"

Instruction Cpu::Fetch() {
    instruction_reg_ = Mem[pc_];
}

Instruction Cpu::Decode() {

}