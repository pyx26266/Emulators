

#include "cpu.hxx"

#include <algorithm>

Instruction Cpu::Fetch() {
    instruction_.reg = (ram_[program_counter_] << 8u) | ram_[program_counter_ + 1u];
    program_counter_ += 2u;
}

Instruction Cpu::Decode() {
    switch (instruction_.byte.high) {
        case 0x00:
            switch (instruction_.byte.low) {
                case 0xE0: return Instruction::CLS;
                case 0xEE: return Instruction::RET;
                default:   return Instruction::UNKNOWN;
            }
        case 0x01: return Instruction::JMP;
        case 0x02: return Instruction::CALL;
        case 0x03: return Instruction::SE_VX_KK;
        case 0x04: return Instruction::SNE_VX_KK;
        case 0x05: return Instruction::SE_VX_VY;
        case 0x06: return Instruction::LD_VX_KK;
        case 0x07: return Instruction::ADD_VX_KK;
        case 0x08:
            switch (instruction_.byte.low) {
                case 0x00: return Instruction::LD_VX_VY;
                case 0x01: return Instruction::OR_VX_VY;
                case 0x02: return Instruction::AND_VX_VY;
                case 0x03: return Instruction::XOR_VX_VY;
                case 0x04: return Instruction::ADD_VX_VY;
                case 0x05: return Instruction::SUB_VX_VY;
                case 0x06: return Instruction::SHR_VX;
                case 0x07: return Instruction::SUBN_VX_VY;
                case 0x0E: return Instruction::SHL_VX;
                default:   return Instruction::UNKNOWN;
            }
        case 0x09: return Instruction::SNE_VX_VY;
        case 0x0A: return Instruction::LD_I;
        case 0x0B: return Instruction::JMP_V0;
        case 0x0C: return Instruction::RND;
        case 0x0D: return Instruction::DRW;
        case 0x0E:
            switch (instruction_.byte.low) {
                case 0x9E: return Instruction::SKP;
                case 0xA1: return Instruction::SKNP;
                default:   return Instruction::UNKNOWN;
            }
        case 0x0F:
            switch (instruction_.byte.low) {
                case 0x07: return Instruction::LD_VX_DT;
                case 0x0A: return Instruction::LD_VX_K;
                case 0x15: return Instruction::LD_DT;
                case 0x18: return Instruction::LD_ST;
                case 0x1E: return Instruction::ADD_I_VX;
                case 0x29: return Instruction::LD_F_VX;
                case 0x33: return Instruction::LD_B_VX;
                case 0x55: return Instruction::LD_I_VX;
                case 0x65: return Instruction::LD_VX_I;
                default:   return Instruction::UNKNOWN;
            }
        default: return Instruction::UNKNOWN;
    }
}

void Cpu::Execute() {
    switch (instruction_.decode_reg) {
        case Instruction::CLS: return cls();
        case Instruction::RET: return ret();
        case Instruction::JMP: return jmp();
        case Instruction::RND: return rnd();
        case Instruction::DRW: return drw();
        case Instruction::SKP: return skp();
        case Instruction::SKNP: return sknp();
        case Instruction::CALL: return call();
        case Instruction::LD_I: return ld_i();
        case Instruction::LD_DT: return ld_dt();
        case Instruction::LD_ST: return ld_st();
        case Instruction::SHR_VX: return shr_vx();
        case Instruction::SHL_VX: return shl_vx();
        case Instruction::JMP_V0: return jp_v0();
        case Instruction::LD_VX_K: return ld_vx_k();
        case Instruction::LD_F_VX: return ld_f_vx();
        case Instruction::LD_B_VX: return ld_b_vx();
        case Instruction::LD_I_VX: return ld_i_vx();
        case Instruction::LD_VX_I: return ld_vx_i();
        case Instruction::LD_VX_DT: return ld_vx_dt();
        case Instruction::ADD_I_VX: return add_i_vx();
        case Instruction::SE_VX_VY: return se_vx_vy();
        case Instruction::LD_VX_KK: return ld_vx_kk();
        case Instruction::LD_VX_VY: return ld_vx_vy();
        case Instruction::OR_VX_VY: return or_vx_vy();
        case Instruction::SE_VX_KK: return se_vx_kk();
        case Instruction::SNE_VX_KK: return sne_vx_kk();
        case Instruction::ADD_VX_KK: return add_vx_kk();
        case Instruction::AND_VX_VY: return and_vx_vy();
        case Instruction::XOR_VX_VY: return xor_vx_vy();
        case Instruction::ADD_VX_VY: return add_vx_vy();
        case Instruction::SUB_VX_VY: return sub_vx_vy();
        case Instruction::SNE_VX_VY: return sne_vx_vy();
        case Instruction::SUBN_VX_VY: return subn_vx_vy();
    }
}

Cpu::~Cpu()
{
}


void Cpu::cls() {
    for (int i = 0xF00; i <= 0xFFF; ++i)
        ram_[i] = 0;
    // std::fill(ram_[0xF00], ram_[0xFFF], 0);
}

void Cpu::ret() {
    // ToDo: make this 12 bit address aware.
    program_counter_ = ram_[kStackEnd + --stack_pointer_];
}

void Cpu::jmp() {
    program_counter_ = instruction_.duodecimal.address;
}

void Cpu::rnd() {
    registers_[instruction_.nibble.x] = /* random_value & */ instruction_.byte.low;
}

void Cpu::drw() {
    registers_[0x0F] = 0; // set the collosion flag to false
    uint8_t x = registers_[instruction_.nibble.x];
    uint8_t y = registers_[instruction_.nibble.y];
    for (int i = 0; i < instruction_.nibble.n; ++i, ++y) {
        uint8_t byte_to_draw = ram_[index_register_ + i];
        for (int j = 0; j < 8; ++j, ++x) {
            if (byte_to_draw & (0x80 >> j)) {
                if (ram_[kFrameBufferStart + x + y])
                    registers_[0x0F] = true; // set the collosion flag
                
                ram_[kFrameBufferStart + x + y] = ram_[kFrameBufferStart + x + y] ^ 1;
            }
        }
    }
}

void Cpu::skp()
{
}

void Cpu::ld_i() {
    index_register_ = instruction_.duodecimal.address;
}

void Cpu::sknp()
{
}

void Cpu::call()
{
}

void Cpu::ld_dt()
{
}

void Cpu::ld_st()
{
}

void Cpu::shr_vx()
{
}

void Cpu::shl_vx()
{
}

void Cpu::jp_v0()
{
}

void Cpu::ld_vx_k()
{
}

void Cpu::ld_f_vx()
{
}

void Cpu::ld_b_vx()
{
}

void Cpu::ld_i_vx()
{
}

void Cpu::ld_vx_i()
{
}

void Cpu::ld_vx_dt()
{
}

void Cpu::add_i_vx()
{
}

void Cpu::se_vx_vy()
{
}

void Cpu::ld_vx_kk()
{
}

void Cpu::ld_vx_vy()
{
}

void Cpu::or_vx_vy()
{
}

void Cpu::se_vx_kk()
{
}

void Cpu::sne_vx_kk()
{
}

void Cpu::add_vx_kk()
{
}

void Cpu::and_vx_vy()
{
}

void Cpu::xor_vx_vy()
{
}

void Cpu::add_vx_vy()
{
}

void Cpu::sub_vx_vy()
{
}

void Cpu::sne_vx_vy()
{
}

void Cpu::subn_vx_vy()
{
}
