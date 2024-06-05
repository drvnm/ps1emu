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
        int gp_register_values[32];
    } gp_registers_union;
    uint32_t pc;
    uint32_t hi;
    uint32_t lo;

    // methods
    void reset();
    void set_register(uint8_t reg, uint32_t value);

    uint32_t get_register(uint8_t reg);
};