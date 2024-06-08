#pragma once

#include "../common/defs.h"

struct Registers // The registers of PS1
{
public:
    union
    {
        struct gp_registers_struct
        {
            uint32_t zero;                           // always 0
            uint32_t at;                             // assembler temporary
            uint32_t v0, v1;                         // return values
            uint32_t a0, a1, a2, a3;                 // arguments
            uint32_t t0, t1, t2, t3, t4, t5, t6, t7; // temporaries
            uint32_t s0, s1, s2, s3, s4, s5, s6, s7; // saved registers
            uint32_t t8, t9;                         // more temporaries
            uint32_t k0, k1;                         // kernel registers
            uint32_t gp;                             // global pointer
            uint32_t sp;                             // stack pointer
            uint32_t fp;                             // frame pointer
            uint32_t ra;                             // return address

        } gp_registers;
        uint32_t gp_register_values[32];
    } gp_registers_union;
    uint32_t pc;
    uint32_t hi;
    uint32_t lo;

    union
    {
        struct cop0_registers_struct
        {
            uint32_t cop0_index;
            uint32_t cop0_random;
            uint32_t cop0_entrylo0;
            uint32_t cop0_entrylo1;
            uint32_t cop0_context;
            uint32_t cop0_pagemask;
            uint32_t cop0_wired;
            uint32_t cop0_reserved[24];
            uint32_t cop0_badvaddr;
            uint32_t cop0_count;
            uint32_t cop0_entryhi;
            uint32_t cop0_compare;
            uint32_t cop0_status;
            uint32_t cop0_cause;
            uint32_t cop0_epc;
            uint32_t cop0_prid;
            uint32_t cop0_config;
            uint32_t cop0_lladdr;
            uint32_t cop0_watchlo;
            uint32_t cop0_watchhi;
            uint32_t cop0_xcontext;
            uint32_t cop0_reserved2[3];
            uint32_t cop0_taglo;
            uint32_t cop0_taghi;
            uint32_t cop0_error_epc;
        } cop0_registers;
        uint32_t cop0_registers_values[32];
    } cop0_registers_union;

    // methods
    void reset();
    void set_register(uint8_t reg, uint32_t value);
    uint32_t get_register(uint8_t reg);

    uint32_t get_register_cop0(uint8_t reg);
    void set_register_cop0(uint8_t reg, uint32_t value);
};