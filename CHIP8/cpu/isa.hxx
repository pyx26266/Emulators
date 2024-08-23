#ifndef ISA_HXX_
#define ISA_HXX_

#include <cstdint>

enum class Register {
    V0, 
    V1, 
    V2, 
    V3, 
    V4,
    V5, 
    V6, 
    V7, 
    V8, 
    V9,
    VA, 
    VB, 
    VC, 
    VD, 
    VE, 
    VF,
    ST, // Sount Timer 
    DT, // Display Timer
    PC, 
    I, 
    SP
};

enum class Instruction {
    CLS,        // 0x00E0, Clear the screen
    JMP,        // 0x1nnn, Jump to location nnn
    DRW,
    RET,
    RND,
    SKP,
    LD_I,
    CALL,
    SKNP,
    LD_DT,
    LD_ST,
    JMP_V0,
    SHL_VX,
    SHR_VX,
    LD_B_VX,
    LD_F_VX,
    LD_I_VX,
    LD_VX_I,
    LD_VX_K,
    LD_VX_KK,
    LD_VX_DT,
    LD_VX_VY,
    OR_VX_VY,
    SE_VX_KK,
    SE_VX_VY,
    ADD_I_VX,
    ADD_VX_KK,
    ADD_VX_VY,
    AND_VX_VY,
    SUB_VX_VY,
    SNE_VX_KK,
    SNE_VX_VY,
    XOR_VX_VY,
    SUBN_VX_VY,
    UNKNOWN
};

union Opcode {
    struct Nibble {
        uint8_t na:4;
        uint8_t x:4;
        uint8_t y:4;
        uint8_t n:4;
    } nibble;

    struct Byte {
        uint8_t high;
        uint8_t low;
    } byte;

    struct Duodecimal {
        uint16_t na:4;
        uint16_t address:12;
    } duodecimal;

    uint16_t reg;
    Instruction decode_reg;    
};

#endif // ISA_HXX_