#include "../cpu.h"

void CPU::setup_opcodes()
{
    // alu
    set_opcode_function(0b001101, &CPU::op_ori);
    set_opcode_function(0b100101, &CPU::op_or);
    set_opcode_function(0b000000 + 0b000000, &CPU::op_sll);
    set_opcode_function(0b001001, &CPU::op_addiu);

    // loads
    set_opcode_function(0b001111, &CPU::op_lui);
    set_opcode_function(0b101011, &CPU::op_sw);
    set_opcode_function(0b000010, &CPU::op_jump);

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