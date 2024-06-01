#include "cpu.h"

CPU::CPU(MemoryMapper memoryMapper) : memoryMapper(memoryMapper)
{
    reset();
}

void CPU::reset()
{
    regs.reset();
}

void CPU::run_current_instruction() 
{
    uint32_t instruction = load32(regs.pc);
    regs.pc += 4;
    decode_and_execute(instruction);
}

void CPU::decode_and_execute(uint32_t instruction)
{
    throw std::runtime_error(std::string("Unimplemented instruction: ") + std::to_string(instruction));
}

uint32_t CPU::load32(uint32_t address) const
{
    return memoryMapper.read32(address);
}

void CPU::run()
{
    while (true)
    {
        run_current_instruction();
    }
}