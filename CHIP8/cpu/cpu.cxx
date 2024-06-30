

#include "cpu.hxx"

Instruction Cpu::Fetch() {
    instruction_.reg = (ram_[program_counter_] << 8u) | ram_[program_counter_+1];
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
    return Instruction();
}
