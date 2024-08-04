#include "./ram.h"

Ram::Ram()
{
    ram.resize(RAM_SIZE);
    for (size_t i = 0; i < ram.size(); i++)
    {
        ram[i] = 0xca;
    }
}

uint32_t Ram::read32(uint32_t address) const
{
    uint32_t value = 0;
    value |= ram[address + 0] << 0;
    value |= ram[address + 1] << 8;
    value |= ram[address + 2] << 16;
    value |= ram[address + 3] << 24;
    return value;
}

void Ram::write32(uint32_t address, uint32_t value)
{
    ram[address + 0] = (value >> 0) & 0xFF;
    ram[address + 1] = (value >> 8) & 0xFF;
    ram[address + 2] = (value >> 16) & 0xFF;
    ram[address + 3] = (value >> 24) & 0xFF;
}