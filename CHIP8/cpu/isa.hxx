enum class Instruction {
    ADD_I_VX,
    ADD_VX_KK,
    ADD_VX_VY,
    AND_VX_VY,
    CALL,
    CLS,
    DRW,
    JMP,
    JMP_V0,
    LD_B_VX,
    LD_DT,
    LD_F_VX,
    LD_I,
    LD_I_VX,
    LD_ST,
    LD_VX_DT,
    LD_VX_I,
    LD_VX_K,
    LD_VX_KK,
    LD_VX_VY,
    OR_VX_VY,
    RET,
    RND,
    SE_VX_KK,
    SE_VX_VY,
    SHL_VX,
    SHR_VX,
    SKNP,
    SKP,
    SNE_VX_KK,
    SNE_VX_VY,
    SUBN_VX_VY,
    SUB_VX_VY,
    XOR_VX_VY,
    UNKNOWN
};

struct Opcode {
    uint16_t in;

    
};
