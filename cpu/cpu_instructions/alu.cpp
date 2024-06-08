#include "../cpu.h"

void CPU::op_ori(Instruction instruction)
{
    uint32_t imm = instruction.get_imm();
    uint32_t rt = instruction.get_rt();
    uint32_t rs = instruction.get_rs();
    uint32_t rs_value = registers.get_register(rs);
    registers.set_register(rt, rs_value | imm);
} // ORI <rt>, <rs>, <immediate>

void CPU::op_or(Instruction instruction)
{
    uint32_t rs = instruction.get_rs();
    uint32_t rt = instruction.get_rt();
    uint32_t rd = instruction.get_rd();
    uint32_t rs_value = registers.get_register(rs);
    uint32_t rt_value = registers.get_register(rt);
    registers.set_register(rd, rs_value | rt_value);
} // OR <rd>, <rs>, <rt>

void CPU::op_sll(Instruction instruction)
{
    uint32_t shift = instruction.get_shift_imm();
    uint32_t rd = instruction.get_rs();
    uint32_t rt = instruction.get_rt();

    registers.set_register(rd, registers.get_register(rt) << shift);

} // SLL <rd>, <rt>, <sa>

void CPU::op_addiu(Instruction instruction)
{
    uint32_t imm = instruction.get_se_imm();
    uint32_t rs = instruction.get_rs();
    uint32_t rt = instruction.get_rt();
    uint32_t rs_value = registers.get_register(rs);
    registers.set_register(rt, rs_value + imm);
} // ADDIU <rt>, <rs>, <immediate>