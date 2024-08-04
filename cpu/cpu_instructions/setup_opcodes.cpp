#include "../cpu.h"

void CPU::setup_opcodes()
{
    // alu
    set_opcode_function(0b001101, &CPU::op_ori);
    set_opcode_function(0b000000, &CPU::op_zero);
    set_opcode_function(0b001001, &CPU::op_addiu);
    set_opcode_function(0b001000, &CPU::op_addi);

    // loads
    set_opcode_function(0b001111, &CPU::op_lui);
    set_opcode_function(0b101011, &CPU::op_sw);
    set_opcode_function(0b100011, &CPU::op_lw);
    set_opcode_function(0b000010, &CPU::op_jump);
    set_opcode_function(0b000101, &CPU::op_bne);
    set_opcode_function(0b101001, &CPU::op_sh);
    // coprocessors
    set_opcode_function(0b010000, &CPU::op_cop0);
}

// if there is already a function pointer for the opcode, then we should not overwrite it
void CPU::set_opcode_function(uint32_t opcode, void (CPU::*opcode_function)(Instruction instruction))
{
    if (opcodes[opcode] != nullptr)
    {
        VENU_LOG_ERROR(fmt::format("Opcode {:b} already has a function pointer", opcode));
        return;
    }
    opcodes[opcode] = opcode_function;
}

// handles cop0 instructions
void CPU::op_cop0(Instruction instruction)
{
    uint32_t funct = instruction.get_cop_opcode();
    switch (funct)
    {
    case 0b00100:
        op_mtc0(instruction);
        break;
    default:
        VENU_LOG_CRITICAL(fmt::format("Unimplemented COP0 instruction: {:b}", funct));
        break;
    }
}

void CPU::op_zero(Instruction instruction)
{
    uint32_t funct = instruction.get_sub_opcode();
    switch (funct)
    {
    case 0b000000:
        op_sll(instruction);
        break;
    case 0b101011:
        op_slti(instruction);
        break;
    case 0b100101:
        op_or(instruction);
        break;
    case 0b100001:
        op_addu(instruction);
        break;
    default:
        VENU_LOG_CRITICAL(fmt::format("Unimplemented ZERO instruction: {:b} and subopcode: {:b}", instruction.get_opcode(), funct));
        break;
    }
}