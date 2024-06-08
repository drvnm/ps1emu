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

// this is written a bit weird but it basically
// exececutes the instruction fetched from the previous step
// and fetches the next instruction. if the instruction changes the pc it will still execute the next instruction
void CPU::run_current_instruction()
{
    Instruction instruction = next_instruction;
    next_instruction = Instruction(load32(registers.pc));
    registers.pc += 4;
    decode_and_execute(instruction);
}

void CPU::decode_and_execute(Instruction instr)
{
    uint8_t opcode = instr.get_opcode();
    if (opcodes[opcode] != nullptr)
    {
        (this->*opcodes[opcode])(instr);
    }
    else
    {

        VENU_LOG_CRITICAL(std::string("Unimplemented instruction: ") + std::to_string(instr.get_opcode()));
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