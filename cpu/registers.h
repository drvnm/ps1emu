#pragma once

#include "../common/defs.h"

struct Registers // The registers of PS1
{
public:
    uint32_t pc;

    // methods
    void reset();
};