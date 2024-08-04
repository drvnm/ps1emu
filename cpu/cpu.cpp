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
    next_instruction = Instruction(read32(registers.pc));
    registers.pc += 4;

    // handle load delay
    uint32_t reg = load_delay_register;
    uint32_t value = load_delay_value;
    
    set_regs(reg, value);
    load_delay_register = 0;
    load_delay_value = 0;
    decode_and_execute(instruction);
    
    registers.gp_registers_union = output_registers.gp_registers_union;
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


uint32_t CPU::read32(uint32_t address) const
{
    return memoryMapper.read32(address);
}

void CPU::store16(uint32_t address, uint16_t value)
{
    memoryMapper.store16(address, value);
}

void CPU::step()
{
    run_current_instruction();
}

void CPU::set_regs(uint32_t rd, uint32_t value)
{
    output_registers.set_register(rd, value);
}