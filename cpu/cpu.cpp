#include "cpu.h"

CPU::CPU(MemoryMapper memoryMapper) : memoryMapper(memoryMapper)
{
    reset();
}

void CPU::reset()
{
    registers.reset();
    setup_opcodes();
}

void CPU::run_current_instruction()
{
    uint32_t instruction = load32(registers.pc);
    registers.pc += 4;
    decode_and_execute(instruction);
}

void CPU::decode_and_execute(uint32_t instruction)
{
    Instruction instr = Instruction(instruction);
    currentInstruction = instr;
    uint8_t opcode = instr.get_opcode();
    if (opcodes[opcode] != nullptr)
    {
        (this->*opcodes[opcode])(instr);
    }
    else
    {

        throw std::runtime_error(std::string("Unimplemented instruction: ") + std::to_string(instruction));
    }
}

uint32_t CPU::load32(uint32_t address) const
{
    return memoryMapper.read32(address);
}

void CPU::step()
{
    run_current_instruction();
}