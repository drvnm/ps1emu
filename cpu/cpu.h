#pragma once

#include "../common/defs.h"
#include "../memorymapper/memorymapper.h"
#include "registers.h"

class CPU // The CPU of PS1
{
private:
    void reset();
    void run_current_instruction();
    void decode_and_execute(uint32_t instruction);
    uint32_t load32(uint32_t address) const;
public:
    Registers regs = Registers();
    MemoryMapper memoryMapper;
    CPU(MemoryMapper memoryMapper);

    void run();
};