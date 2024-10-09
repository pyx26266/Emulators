#ifndef CPU_H_
#define CPU_H_

#include <cstdint>

#include "isa.hxx"
#include "../memory/memory.hxx" // has-a relationship

class Cpu {
public:
    static const uint16_t kStackStart = 0xEA0;
    static const uint16_t kStackEnd = 0xEFF;
    static const uint16_t kFrameBufferStart = 0xF00;
    static const uint16_t kFrameBufferEnd = 0xFFF;
    static const uint16_t kProgramStart = 0x200;
    
    Cpu(Memory &ram): ram_(ram) {
        program_counter_ = kProgramStart;
    }
    /* [[nodiscard]] */ Instruction Fetch();
    /* [[nodiscard]] */ Instruction Decode();
    void Execute();
    // void Run();
    ~Cpu();
    Opcode instruction_;
    Instruction decode_reg; 
protected:
private:

    uint8_t  registers_[0x0F] = {}; // V0-VF
    uint16_t index_register_ = {}; // I
    uint8_t  stack_pointer_ = {};
    uint16_t program_counter_ = {};
    uint8_t delay_timer_ = {};
    uint8_t sound_timer_ = {};
    Memory &ram_;

    void cls();
    void ret();
    void jmp();

    /// @brief Cxnn - Set Vx = random byte AND nn
    void rnd();
    void drw();


    /// @brief Ex9E - Skip instruction if key with the value of Vx is pressed.
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
};



#endif // CPU_H_ 