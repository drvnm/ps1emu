#include "defs.h"
#include "../cpu/cpu_instructions/instruction.h"

void VENU_LOG_INFO(const std::string &message)
{
    std::cout << "\033[1;34m[INFO] " << message << "\033[0m" << std::endl;
}

void VENU_LOG_SUCCESS(const std::string &message)
{
    std::cout << "\033[1;32m[SUCCESS] " << message << "\033[0m" << std::endl;
}

void VENU_LOG_ERROR(const std::string &message)
{
    std::cerr << "\033[1;31m[ERROR] " << message << "\033[0m" << std::endl;
}

void VENU_LOG_CRITICAL(const std::string &message)
{
    std::cerr << "\033[1;31m[CRITICAL] " << message << "\033[0m" << std::endl;
    throw std::runtime_error(message);
}

std::string get_opcode_string(const Instruction &instruction)
{

    // convert above to switch case

    uint32_t opcode = instruction.get_opcode();
    switch (opcode)
    {
    case 0b001101:
        return "ori $%d, $%s, #%i"; // ORI <rt>, <rs>, <immediate>
    case 0b100101:
        return "or $%d, $%s, $%d"; // OR <rd>, <rs>, <rt>
    case 0b001001:
        return "addiu $%d, $%s, #%i"; // ADDIU <rt>, <rs>, <immediate>
    case 0b000000 + 0b000000:
        return "sll $%d, $%s, #%i"; // SLL <rd>, <rt>, <sa>
    case 0b001111:
        return "lui $%d, #%i"; // LUI <rt>, <immediate>
    case 0b101011:
        return "sw $%d, #%i($%s)"; // SW <rt>, <offset>($rs)
    case 0b000010:
        return "j #%i"; // J <address>
    case 0b010000:
        switch (instruction.get_cop_opcode())
        {
        case 0b00100:
            return "mtc0 $%d, $%s"; // MTC0 <rt>, <rd>
        }
    default:
    }
}

std::string get_formatted_instruction(const Instruction &instruction)
{
    uint32_t opcode = instruction.get_opcode();
    uint32_t rs = instruction.get_rs();
    uint32_t rt = instruction.get_rt();
    uint32_t imm = instruction.get_imm();

    std::string formatted_instruction = get_opcode_string(instruction);

    if (formatted_instruction.find("%s") != std::string::npos)
    {
        formatted_instruction.replace(formatted_instruction.find("%s"), 2, std::to_string(rs));
    }

    if (formatted_instruction.find("%d") != std::string::npos)
    {
        formatted_instruction.replace(formatted_instruction.find("%d"), 2, std::to_string(rt));
    }

    if (formatted_instruction.find("%i") != std::string::npos)
    {
        formatted_instruction.replace(formatted_instruction.find("%i"), 2, fmt::format("{:#x}", imm));
    }

    return formatted_instruction;
}