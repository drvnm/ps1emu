#pragma once

#include "../../common/defs.h"

class Instruction
{
    uint32_t instruction;

public:
    Instruction(uint32_t instruction) : instruction(instruction) {}
    Instruction() : instruction(0) {}
    // get the opcode of the instruction (bits 31-26)
    uint32_t get_opcode() const;
    // get opcode for coprocessor instructions 
    uint32_t get_cop_opcode() const;
    // get source register (bits 11-15)
    uint32_t get_rs() const; 
    // get target register (bits 16-20)
    uint32_t get_rt() const;
    // ?? (11 _ 15)
    uint32_t get_rd() const;
    // get immediate value
    uint32_t get_imm() const;
    // get signed extended immediate value
    int32_t get_se_imm() const;
    // shift imm value?
    uint32_t get_shift_imm() const;
    // sub opcode
    uint32_t get_sub_opcode() const;
    // get jump address (bits 0-25)
    uint32_t get_jump_address() const;

    // pretty print the instruction
    std::string to_string() const;
};
