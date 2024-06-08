#include "memorymapper.h"
#include "address_range.h"

uint32_t MemoryMapper::read32(uint32_t address) const
{
    if (address % 4 != 0)
        VENU_LOG_CRITICAL(fmt::format("Unaligned memory read at address: {:#010x}", address));

    if (auto offset = map::BIOS.contains(address))
    {
        return bios.read32(*offset);
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
