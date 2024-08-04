#pragma once

#include "../bios/bios.h"
#include "../ram/ram.h"

class MemoryMapper // This class is responsible for managing the memory map of the PS1.
{
public:
    Bios bios;
    Ram ram;
    MemoryMapper(Bios bios, Ram ram) : bios(bios), ram(ram) {}
    uint32_t read32(uint32_t address) const;
    void write32(uint32_t address, uint32_t value);
    void store16(uint32_t address, uint16_t value);
}; 