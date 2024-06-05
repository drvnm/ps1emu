#include "../cpu.h"

void CPU::setup_opcodes()
{
    opcodes[0b001111] = &CPU::op_lui;
    opcodes[0b001101] = &CPU::op_ori;
}