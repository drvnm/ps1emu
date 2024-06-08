#include "registers.h"

void Registers::reset()
{
    pc = 0xBFC00000; // BIOS entry point

    // set all registers to 0
    for (int i = 0; i < 32; i++)
    {
        gp_registers_union.gp_register_values[i] = 0xdeadbeef;
    }

    gp_registers_union.gp_registers.zero = 0; // always 0

    // set cop0 registers to 0
    for (int i = 0; i < 32; i++)
    {
        cop0_registers_union.cop0_registers_values[i] = 0;
    }

}

void Registers::set_register(uint8_t reg, uint32_t value)
{
    gp_registers_union.gp_register_values[reg] = value;
    gp_registers_union.gp_registers.zero = 0; // always 0
}

uint32_t Registers::get_register(uint8_t reg)
{
    return gp_registers_union.gp_register_values[reg];
}

uint32_t Registers::get_register_cop0(uint8_t reg)
{
    return cop0_registers_union.cop0_registers_values[reg];
}

void Registers::set_register_cop0(uint8_t reg, uint32_t value)
{
    cop0_registers_union.cop0_registers_values[reg] = value;
}