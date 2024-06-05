#include "instruction.h"

uint32_t Instruction::get_opcode() const
{
    return instruction >> 26;
}

uint32_t Instruction::get_rs() const
{
    return (instruction >> 21) & 0x1F;
}

uint32_t Instruction::get_rt() const
{
    return (instruction >> 16) & 0x1F;
}

uint32_t Instruction::get_imm() const
{
    return instruction & 0xFFFF;
}