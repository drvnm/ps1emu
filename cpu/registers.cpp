#include "registers.h"

void Registers::reset()
{
    pc = 0xBFC00000; // BIOS entry point
}