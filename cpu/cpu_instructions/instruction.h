#pragma once

#include "../../common/defs.h"

class Instruction
{
    uint32_t instruction;

public:
    Instruction(uint32_t instruction) : instruction(instruction) {}
    Instruction() : instruction(0) {}
    uint32_t get_opcode() const; // get the opcode of the instruction
    uint32_t get_rs() const;     // get source register
    uint32_t get_rt() const;     // get target register
    uint32_t get_imm() const;    // get immediate value
};
