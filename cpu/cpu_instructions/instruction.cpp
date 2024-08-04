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

std::string Instruction::to_string() const
{
    return fmt::format("Raw: {:08x}, Opcode: {:02x}, RS: {:02x}, RT: {:02x}, RD: {:02x}, IMM: {:04x}, SE_IMM: {:04x}, SHIFT_IMM: {:02x}, SUB_OPCODE: {:02x}, JUMP_ADDRESS: {:08x}",
                       instruction, get_opcode(), get_rs(), get_rt(), get_rd(), get_imm(), get_se_imm(), get_shift_imm(), get_sub_opcode(), get_jump_address());
}