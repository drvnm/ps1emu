#pragma once

#include "../common/defs.h"
#include "../memorymapper/memorymapper.h"
#include "cpu_instructions/instruction.h"
#include "registers.h"

class CPU // The CPU of PS1
{
private:
    // OPCODE IMPLEMENTATIONS
    // alus
    void op_ori(Instruction instruction);   // Bitwise OR Immediate
    void op_or(Instruction instruction);    // Bitwise OR
    void op_sll(Instruction instruction);   // Shift Left Logical
    void op_addiu(Instruction instruction); // Add Immediate Unsigned

    // loads
    void op_lui(Instruction instruction);  // Load Upper Immediate
    void op_sw(Instruction instruction);   // Store Word
    void op_jump(Instruction instruction); // Jump

    // handle coprocessor 0 
    void op_cop0(Instruction instruction); // Coprocessor 0
    void op_mtc0(Instruction instruction); // Move To Coprocessor 0

    void setup_opcodes();                                                                             // setup the array of function pointers to the opcodes
    void set_opcode_function(uint32_t opcode, void (CPU::*opcode_function)(Instruction instruction)); // set the function pointer for the opcode

    void run_current_instruction();
    void decode_and_execute(Instruction instr);
    void reset();
    void (CPU::*opcodes[0xFF + 1])(Instruction instruction) = {nullptr}; // array of function pointers to the opcodes

public:
    Instruction next_instruction = Instruction(0);
    Registers registers = Registers();
    MemoryMapper memoryMapper;
    CPU(MemoryMapper memoryMapper);

    uint32_t load32(uint32_t address) const;

    void step();
};