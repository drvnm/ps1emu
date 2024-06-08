#include "instruction.h"

uint32_t Instruction::get_opcode() const
{
    return instruction >> 26;
}

uint32_t Instruction::get_cop_opcode() const
{
    return (instruction >> 21) & 0x1F;
}

uint32_t Instruction::get_sub_opcode() const
{
    return instruction & 0x3F;
}

uint32_t Instruction::get_rs() const
{
    return (instruction >> 21) & 0x1F;
}

uint32_t Instruction::get_rt() const
{
    return (instruction >> 16) & 0x1F;
}

uint32_t Instruction::get_rd() const
{
    return (instruction >> 11) & 0x1F;
}

uint32_t Instruction::get_imm() const
{
    return instruction & 0xFFFF;
}

int32_t Instruction::get_se_imm() const
{
    return static_cast<int16_t>(instruction & 0xFFFF);
}

uint32_t Instruction::get_shift_imm() const
{
    return (instruction >> 6) & 0x1F;
}

uint32_t Instruction::get_jump_address() const
{
    return instruction & 0x3FFFFFF;
}