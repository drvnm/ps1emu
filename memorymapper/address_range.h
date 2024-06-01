#include <optional>

#include "../common/defs.h"

namespace map
{

    struct Range
    {
        uint32_t start;
        uint32_t length;

        Range(uint32_t start, uint32_t length) : start(start), length(length) {}

        std::optional<uint32_t> contains(uint32_t addr) const
        {
            if (addr >= start && addr < start + length)
            {
                return addr - start;
            }
            else
            {
                return std::nullopt;
            }
        }
    };

    const Range BIOS(0xbfc00000, BIOS_SIZE);

}