#include "../cpu.h"

void CPU::op_ori(Instruction instruction)
{
    uint32_t imm = instruction.get_imm();
    uint32_t rt = instruction.get_rt();
    uint32_t rs = instruction.get_rs();
    uint32_t rs_value = registers.get_register(rs);
    set_regs(rt, rs_value | imm);
} // ORI <rt>, <rs>, <immediate>

void CPU::op_or(Instruction instruction)
{
    uint32_t rs = instruction.get_rs();
    uint32_t rt = instruction.get_rt();
    uint32_t rd = instruction.get_rd();
    uint32_t rs_value = registers.get_register(rs);
    uint32_t rt_value = registers.get_register(rt);
    set_regs(rd, rs_value | rt_value);
} // OR <rd>, <rs>, <rt> (bitwise OR of <rs> and <rt> stored in <rd>)

void CPU::op_sll(Instruction instruction)
{
    uint32_t shift = instruction.get_shift_imm();
    uint32_t rd = instruction.get_rs();
    uint32_t rt = instruction.get_rt();

    set_regs(rd, registers.get_register(rt) << shift);

} // SLL <rd>, <rt>, <sa> (shifts <rt> left by <sa> bits and stores the result in <rd>)

void CPU::op_addiu(Instruction instruction)
{
    uint32_t imm = instruction.get_se_imm();
    uint32_t rs = instruction.get_rs();
    uint32_t rt = instruction.get_rt();
    uint32_t rs_value = registers.get_register(rs);
    set_regs(rt, rs_value + imm);
} // ADDIU <rt>, <rs>, <immediate>

void CPU::op_addi(Instruction instruction)
{
    int32_t imm = instruction.get_se_imm();
    uint32_t rs = instruction.get_rs();
    uint32_t rt = instruction.get_rt();
    int32_t rs_value = registers.get_register(rs);

    // this instruction raises an exception if the addition overflows
    if ((imm > 0 && rs_value > INT32_MAX - imm) || (imm < 0 && rs_value < INT32_MIN - imm))
    {
        VENU_LOG_CRITICAL("ADDI: Addition overflowed");
        return;
    }

    set_regs(rt, rs_value + imm);

} // ADDI <rt>, <rs>, <immediate> (adds <rs> to <immediate> and stores the result in <rt>)

void CPU::op_slti(Instruction instruction)
{
    int32_t  rd = instruction.get_rd();
    uint32_t rs = instruction.get_rs();
    uint32_t rt = instruction.get_rt();
    uint32_t rs_value = registers.get_register(rs);
    uint32_t rt_value = registers.get_register(rt);
    
    if (rs_value < rt_value)
    {
        set_regs(rd, 1);
    }
    else
    {
        set_regs(rd, 0);
    }
} // SLTI <rd>, <rs>, <rt> (if <rs> is less than <rt> then <rd> is set to 1, otherwise it is set to 0)


void CPU::op_addu(Instruction instruction)
{
    uint32_t rs = instruction.get_rs();
    uint32_t rt = instruction.get_rt();
    uint32_t rd = instruction.get_rd();
    uint32_t rs_value = registers.get_register(rs);
    uint32_t rt_value = registers.get_register(rt);
    set_regs(rd, rs_value + rt_value);
} // ADDU <rd>, <rs>, <rt> (adds <rs> to <rt> and stores the result in <rd>)