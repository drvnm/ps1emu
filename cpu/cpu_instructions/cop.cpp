#include "../cpu.h"

void CPU::op_mtc0(Instruction instruction)
{
    uint32_t cpu_r = instruction.get_rt();
    uint32_t cop_r = instruction.get_rd();
    uint32_t v = registers.get_register(cpu_r);

    switch (cop_r)
    {
    case 12:
        registers.cop0_registers_union.cop0_registers.cop0_status = v;
        break;
    case 3:
    case 5:
    case 6:
    case 7:
    case 9:
    case 11:
        if (v != 0)
        {
            VENU_LOG_CRITICAL(fmt::format("MTC0: Writing non-zero value to read-only register: {:b}", cop_r));
        }
        break;
    case 13:
        if (v != 0)
        {
            VENU_LOG_CRITICAL(fmt::format("Unhandles write to CAUSE register: {:b}", v));
        }
        break;
    default:
        VENU_LOG_CRITICAL(fmt::format("Unimplemented COP0 register: {:b}", cop_r));
        break;
    }
} // MTC0 <rt>, <rd> (sets COP0 register <rd> to the value in <rt>)