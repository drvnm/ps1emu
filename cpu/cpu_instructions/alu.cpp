#include "../cpu.h"

void CPU::op_ori(Instruction instruction)
{
    uint32_t imm = instruction.get_imm();
    uint32_t rs = instruction.get_rs();
    uint32_t rt = instruction.get_rt();
    uint32_t rs_value = registers.get_register(rs);
    registers.set_register(rt, rs_value | imm);
} // ORI <rt>, <rs>, <immediate>