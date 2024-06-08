#include "../cpu.h"

void CPU::op_lui(Instruction instruction)
{
    uint32_t imm = instruction.get_imm();
    uint32_t rt = instruction.get_rt();
    registers.set_register(rt, imm << 16);
} // LUI <rt>, <immediate>

void CPU::op_sw(Instruction instruction)
{
    if (registers.cop0_registers_union.cop0_registers.cop0_status & 0x10000)
    {
        VENU_LOG_INFO("SW: Cache is isolated, ignoring write");
        return;
    }

    uint32_t base = registers.get_register(instruction.get_rs());
    uint32_t offset = instruction.get_se_imm();
    uint32_t rt = registers.get_register(instruction.get_rt());
    memoryMapper.write32(base + offset, rt);
} // SW <rt>, <offset>(<base>)

void CPU::op_jump(Instruction instruction)
{
    uint32_t address = instruction.get_jump_address();
    registers.pc = (registers.pc & 0xF0000000) | (address << 2);
} // J <address>