#include "memorymapper.h"
#include "address_range.h"

const uint32_t REGION_MASK[] = {
    // KUSEG: 2048MB:
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    // KSEG0: 512MB:
    0x7fffffff,
    // KSEG1: 512MB:
    0x1fffffff,
    // KSEG2: 1024MB:
    0xffffffff,
    0xffffffff,
};

uint32_t mask_region(uint32_t address)
{
    size_t index = address >> 29;
    return address & REGION_MASK[index];
}

uint32_t MemoryMapper::read32(uint32_t address) const
{
    address = mask_region(address);
    if (address % 4 != 0)
        VENU_LOG_CRITICAL(fmt::format("Unaligned memory read at address: {:#010x}", address));

    if (auto offset = map::BIOS.contains(address))
    {
        return bios.read32(*offset);
    }
    else if (auto offset = map::RAM.contains(address))
    {
        return ram.read32(*offset);
    }
    else
    {
        VENU_LOG_CRITICAL(fmt::format("Unmapped memory read at address: {:#010x}", address));
    }

    VENU_LOG_SUCCESS(fmt::format("Read {:#010x} from address {:#010x}", 0, address));
    return 0;
}

void MemoryMapper::write32(uint32_t address, uint32_t value)
{
    address = mask_region(address);
    if (address % 4 != 0)
        VENU_LOG_CRITICAL(fmt::format("Unaligned memory write at address: {:#010x}", address));

    if (auto offset = map::MemControl.contains(address))
    {
        if (offset == 0 && value != 0x1f000000)
            VENU_LOG_CRITICAL(fmt::format("Invalid MEM_CONTROL write: {:#010x}", value));
        else if (offset == 4 && value != 0x1f802000)
            VENU_LOG_INFO(fmt::format("Invalid MEM_CONTROL write: {:#010x}", value));
        else
            VENU_LOG_INFO(fmt::format("Unmapped memory write to MEM_CONTROL at address: {:#010x}", address));
    }
    else if (auto offset = map::RAM.contains(address))
    {
        ram.write32(*offset, value);
    }
    else if (auto offset = map::RamSize.contains(address))
    {
        VENU_LOG_INFO(fmt::format("Unmapped memory write to RAM_SIZE at address: {:#010x}", address));
    }
    else if (auto offset = map::CacheControl.contains(address))
    {
        VENU_LOG_INFO(fmt::format("Unmapped memory write to CACHE_CONTROL at address: {:#010x}", address));
    }
    else
    {
        VENU_LOG_CRITICAL(fmt::format("Unmapped memory write at address: {:#010x}", address));
    }
}

void MemoryMapper::store16(uint32_t address, uint16_t value)
{
    address = mask_region(address);
    if (address % 2 != 0)
    {
        VENU_LOG_CRITICAL(fmt::format("Unaligned 16 bitmemory write at address: {:#010x}", address));
    }
    VENU_LOG_INFO(fmt::format("Unmapped 16 bit memory write at address: {:#010x}", address));
}