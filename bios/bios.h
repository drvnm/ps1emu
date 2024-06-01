#pragma once

#include <vector>

#include "../common/defs.h"

struct Bios
{
public:
    std::vector<uint8_t> data;
    Bios(const char* path);

    uint32_t read32(uint32_t offset) const;
};