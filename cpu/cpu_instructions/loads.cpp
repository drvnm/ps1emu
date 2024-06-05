#include "../cpu.h"

void CPU::op_lui(Instruction instruction)
{
    uint32_t imm = instruction.get_imm();
    uint32_t rt = instruction.get_rt();
    registers.set_register(rt, imm << 16);
} // LUI <rt>, <immediate>