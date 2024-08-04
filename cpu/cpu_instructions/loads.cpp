#include "../cpu.h"

void CPU::op_lui(Instruction instruction)
{
    uint32_t imm = instruction.get_imm();
    uint32_t rt = instruction.get_rt();
    set_regs(rt, imm << 16);
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
} // SW <rt>, <offset>(<base>) (stores the value in <rt> to the address <base> + <offset>)

void CPU::op_lw(Instruction instruction)
{
    if (registers.cop0_registers_union.cop0_registers.cop0_status & 0x10000)
    {
        VENU_LOG_INFO("LW: Cache is isolated, ignoring read");
        return;
    }

    uint32_t base = registers.get_register(instruction.get_rs());
    int32_t offset = instruction.get_se_imm();
    uint32_t rt = instruction.get_rt();
    uint32_t value = memoryMapper.read32(base + offset);

    load_delay_register = rt;
    load_delay_value = value;

} // LW <rt>, <offset>(<base>)

void CPU::branch(uint32_t offset)
{
    registers.pc += offset << 2;
    registers.pc -= 4;
}   

void CPU::op_jump(Instruction instruction)
{
    uint32_t address = instruction.get_jump_address();
    registers.pc = (registers.pc & 0xF0000000) | (address << 2);
} // J <address>

void CPU::op_bne(Instruction instruction)
{
    uint32_t rs = instruction.get_rs();
    uint32_t rt = instruction.get_rt();
    int32_t imm = instruction.get_se_imm();
    uint32_t rs_value = registers.get_register(rs);
    uint32_t rt_value = registers.get_register(rt);

    if (rs_value != rt_value)
    {
        branch(imm);
    }
} // BNE <rs>, <rt>, <immediate> (branches to the address at <pc> + 4 + <immediate> if <rs> != <rt>)

void CPU::op_sh(Instruction instruction)
{
    if (registers.cop0_registers_union.cop0_registers.cop0_status & 0x10000)
    {
        VENU_LOG_INFO("SH: Cache is isolated, ignoring write");
        return;
    }

    uint32_t base = registers.get_register(instruction.get_rs());
    uint32_t offset = instruction.get_se_imm();
    uint32_t rt = registers.get_register(instruction.get_rt());
    memoryMapper.store16(base + offset, rt);
} // SH <rt>, <offset>(<base>) (stores the value in <rt> to the address <base> + <offset>)