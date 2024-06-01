#pragma once

#include "../bios/bios.h"

class MemoryMapper // This class is responsible for managing the memory map of the PS1.
{
public:
    Bios bios;
    MemoryMapper(Bios bios) : bios(bios) {}
    uint32_t read32(uint32_t address) const;
    void write32(uint32_t address, uint32_t value);
}; 