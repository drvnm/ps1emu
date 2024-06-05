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

std::string opcodes_disasm[100];

void setup_opcodes() 
{
    opcodes_disasm[0b001111] = "lui $%d, #%i"; // LUI <rt>, <immediate>
    opcodes_disasm[0b001101] = "ori $%d, $%s, #%i"; // ORI <rt>, <rs>, <immediate>
}

std::string get_formatted_instruction(const Instruction& instruction)
{
    uint32_t opcode = instruction.get_opcode();
    uint32_t rs = instruction.get_rs();
    uint32_t rt = instruction.get_rt();
    uint32_t imm = instruction.get_imm();

    if (opcodes_disasm[opcode].empty())
    {
        return "UNKNOWN INSTRUCTION";
    }

    std::string formatted_instruction = opcodes_disasm[opcode];

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
        formatted_instruction.replace(formatted_instruction.find("%i"), 2, std::to_string(imm));
    }

    return formatted_instruction;
}