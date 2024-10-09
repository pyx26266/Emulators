

#include "cpu.hxx"
#include "../logging.hxx"

#include <algorithm>

Instruction Cpu::Fetch() {
    instruction_.reg = (ram_[program_counter_] << 8u) | ram_[program_counter_ + 1u];
    program_counter_ += 2u;
}

Instruction Cpu::Decode() {
    LOG_INFO("instruction 0x%X:", instruction_.reg);
    switch (instruction_.nibble.low) {
        case 0x00:
            switch (instruction_.byte.high) {
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
            switch (instruction_.byte.high) {
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
            switch (instruction_.byte.high) {
                case 0x9E: return Instruction::SKP;
                case 0xA1: return Instruction::SKNP;
                default:   return Instruction::UNKNOWN;
            }
        case 0x0F:
            switch (instruction_.byte.high) {
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
        default:
            LOG_INFO("Unknown Instruction 0x%X", instruction_.reg) 
            return Instruction::UNKNOWN;
    }
}

void Cpu::Execute() {
    switch (decode_reg) {
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

Cpu::~Cpu() {
    LOG_INFO("destructing CPU...");
}



void Cpu::cls() {
    LOG_INFO("%s called.", __FUNCTION__);
    for (int i = 0xF00; i <= 0xFFF; ++i)
        ram_[i] = 0;
    // std::fill(ram_[0xF00], ram_[0xFFF], 0);
}

void Cpu::ret() {
    LOG_INFO("%s called.", __FUNCTION__);
    // ToDo: make this 12 bit address aware.
    program_counter_ = ram_[kStackEnd + --stack_pointer_];
}

void Cpu::jmp() {
    LOG_INFO("%s called.", __FUNCTION__);
    program_counter_ = instruction_.duodecimal.address;
}

void Cpu::rnd() {
    LOG_INFO("%s called.", __FUNCTION__);
    registers_[instruction_.nibble.x] = /* random_value & */ 5 & instruction_.byte.high;
}

void Cpu::drw() {
    LOG_INFO("%s called.", __FUNCTION__);
    registers_[0x0F] = 0; // set the collosion flag to false
    // uint8_t x_cord = registers_[instruction_.nibble.x];
    // uint8_t y_cord = registers_[instruction_.nibble.y];
    for (int y = 0; y < instruction_.nibble.high; ++y) {
        uint8_t byte_to_draw = ram_[index_register_ + y];
        for (int x = 0; x < 8; ++x) {
            // uint8_t draw_bit = byte_to_draw & (0x80 >> x);
            if (byte_to_draw & (0x80 >> x)) {
                uint16_t px = registers_[instruction_.nibble.x] + x;
                uint16_t py = registers_[instruction_.nibble.y] + y;
                uint16_t pixel = px + (py * 64);
                int arrayIndex = pixel / 8;
                int bitPosition = pixel % 8;

                if ((ram_[kFrameBufferStart + arrayIndex] >> bitPosition) & 0x01) registers_[0x0F] = true;
                ram_[kFrameBufferStart + arrayIndex] ^= (1 << (7 - bitPosition));

                // if (ram_[kFrameBufferStart + x + y])
                //     registers_[0x0F] = true; // set the collosion flag
                
                // ram_[kFrameBufferStart + x + y] = ram_[kFrameBufferStart + x + y] ^ 1;
            }
        }
    }
}

void Cpu::skp() {
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::ld_i() {
    LOG_INFO("%s called.", __FUNCTION__);
    index_register_ = instruction_.duodecimal.address;
}

void Cpu::sknp()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::call()
{
    LOG_INFO("%s called.", __FUNCTION__);
    ram_[kStackEnd - stack_pointer_] = program_counter_ >> 8u;
    stack_pointer_++;
    ram_[kStackEnd - stack_pointer_] = program_counter_ & 0xFF;
    stack_pointer_++;

    program_counter_ = instruction_.duodecimal.address;
}

void Cpu::ld_dt()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::ld_st()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::shr_vx()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::shl_vx()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::jp_v0()
{
    LOG_INFO("%s called.", __FUNCTION__);
    program_counter_ = instruction_.duodecimal.address + registers_[0x00];
}

void Cpu::ld_vx_k()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::ld_f_vx()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::ld_b_vx()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::ld_i_vx()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::ld_vx_i()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::ld_vx_dt()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::add_i_vx()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::se_vx_vy() {
    LOG_INFO("%s called.", __FUNCTION__);
    if (registers_[instruction_.nibble.x] == instruction_.nibble.y) {
        program_counter_ += 2;
    }
}

void Cpu::ld_vx_kk() {
    LOG_INFO("%s called.", __FUNCTION__);
    registers_[instruction_.nibble.x] = instruction_.byte.high;
}

void Cpu::ld_vx_vy()
{
    LOG_INFO("%s called.", __FUNCTION__);
    registers_[instruction_.nibble.x] = instruction_.nibble.y;
}

void Cpu::or_vx_vy()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::se_vx_kk()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::sne_vx_kk()
{
    LOG_INFO("%s called.", __FUNCTION__);
    if (registers_[instruction_.nibble.x] != instruction_.byte.high) {
        program_counter_ += 2;
    }
}

void Cpu::add_vx_kk()
{
    LOG_INFO("%s called.", __FUNCTION__);
    registers_[instruction_.nibble.x] += instruction_.byte.high;
}

void Cpu::and_vx_vy()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::xor_vx_vy()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::add_vx_vy()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::sub_vx_vy()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}

void Cpu::sne_vx_vy()
{
    LOG_INFO("%s called.", __FUNCTION__);
    if (registers_[instruction_.nibble.x] != registers_[instruction_.nibble.y]) {
        program_counter_ += 2;
    }
}

void Cpu::subn_vx_vy()
{
    LOG_INFO("%s called.", __FUNCTION__);
    LOG_INFO("%s not implemented.", __FUNCTION__);
}
