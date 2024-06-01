#include "memorymapper.h"
#include "address_range.h"

uint32_t MemoryMapper::read32(uint32_t address) const
{
    if (auto offset = map::BIOS.contains(address))
    {
        return bios.read32(*offset);
    }
    else
    {
        throw std::runtime_error("Unmapped memory read");
    }
}