enum class Instruction {
    CLS,        // Clear the screen
    DRW,
    JMP,
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
    struct Nibble
    {
        uint8_t na:4;
        uint8_t x:4;
        uint8_t y:4;
        uint8_t n:4;
    }nibble;

    struct Byte
    {
        uint8_t high;
        uint8_t low;
    }byte;

    struct Duodecimal 
    {
        uint16_t na:4;
        uint16_t address:12;
    }duodecimal ;

    uint16_t reg;
    Instruction decode_reg;    
};

void cls();
void ret();
void jmp();
void rnd();
void drw();
void skp();
void ld_i();
void sknp();
void call();
void ld_dt();
void ld_st();
void shr_vx();
void shl_vx();
void jp_v0();
void ld_vx_k();
void ld_f_vx();
void ld_b_vx();
void ld_i_vx();
void ld_vx_i();
void ld_vx_dt();
void add_i_vx();
void se_vx_vy();
void ld_vx_kk();
void ld_vx_vy();
void or_vx_vy();
void se_vx_kk();
void sne_vx_kk();
void add_vx_kk();
void and_vx_vy();
void xor_vx_vy();
void add_vx_vy();
void sub_vx_vy();
void sne_vx_vy();
void subn_vx_vy();