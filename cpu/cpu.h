#pragma once

#include "../common/defs.h"
#include "../memorymapper/memorymapper.h"
#include "cpu_instructions/instruction.h"
#include "registers.h"

class CPU // The CPU of PS1
{
private:
    // OPCODE IMPLEMENTATIONS
    void op_lui(Instruction instruction); // Load Upper Immediate
    void op_ori(Instruction instruction); // Bitwise OR Immediate

    void setup_opcodes(); // setup the array of function pointers to the opcodes

    void run_current_instruction();
    void decode_and_execute(uint32_t instruction);
    void reset();
    void (CPU::*opcodes[0xFF + 1])(Instruction instruction); // array of function pointers to the opcodes
public:
    Instruction currentInstruction;
    Registers registers = Registers();
    MemoryMapper memoryMapper;
    CPU(MemoryMapper memoryMapper);
    
    uint32_t load32(uint32_t address) const;

    void step();
};