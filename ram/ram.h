#pragma once

#include "../common/defs.h"

class Ram
{
    public:
    std::vector<uint8_t> ram; 

    uint32_t read32(uint32_t address) const;
    void write32(uint32_t address, uint32_t value);
    Ram();
};