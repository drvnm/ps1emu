// #include "memorymapper/memorymapper.h"
// #include "bios/bios.h"
// #include "cpu/cpu.h"

// int main()
// {
//     Bios bios = Bios("bin/SCPH1001.BIN");
//     MemoryMapper memoryMapper = MemoryMapper(bios);
//     CPU cpu = CPU(memoryMapper);

//     cpu.run();

// }
#include <stdio.h>
#include <cstdint>

union a
{
    struct gp_registers
    {
        uint32_t zero; // always 0
        uint32_t at; // assembler temporary
        uint32_t v0, v1; // return values
        uint32_t a0, a1, a2, a3; // arguments
        uint32_t t0, t1, t2, t3, t4, t5, t6, t7; // temporaries
        uint32_t s0, s1, s2, s3, s4, s5, s6, s7; // saved registers
        uint32_t t8, t9; // more temporaries
        uint32_t k0, k1; // kernel registers
        uint32_t gp; // global pointer
        uint32_t sp; // stack pointer
        uint32_t fp; // frame pointer
        uint32_t ra; // return address

    } gp_registers;
    int gp_register_values[32];
};


int main()
{
    a a1;
    a1.gp_registers.ra = 31;

    for (int i = 0; i < 32; i++)
    {
        printf("Register %d: %d\n", i, a1.gp_register_values[i]);
    }
}