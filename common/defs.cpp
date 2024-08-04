#include "defs.h"
#include "../cpu/cpu_instructions/instruction.h"
#include "../debugger/debugger.h"

Debugger &debugger = Debugger::getInstance();
const std::string REGISTER_NAMES[32] = {
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};

void VENU_LOG_INFO(const std::string &message)
{
    std::cout << "\033[1;34m[INFO] " << message << "\033[0m" << std::endl;
    debugger.logs.push_back({"[INFO] " + message, LOG_TYPE_INFO});
}

void VENU_LOG_SUCCESS(const std::string &message)
{
    std::cout << "\033[1;32m[SUCCESS] " << message << "\033[0m" << std::endl;
    debugger.logs.push_back({"[SUCCESS] " + message, LOG_TYPE_SUCCESS});
}

void VENU_LOG_ERROR(const std::string &message)
{
    std::cerr << "\033[1;31m[ERROR] " << message << "\033[0m" << std::endl;
    debugger.logs.push_back({"[ERROR] " + message, LOG_TYPE_ERROR});
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
        return "ori $%rt, $%rs, #%i"; // ORI <rt>, <rs>, <immediate>
    case 0b001001:
        return "addiu $%rt, $%rs, #%sei"; // ADDIU <rt>, <rs>, <se immediate>
    case 0b001000:
        return "addi $%rt, $%rs, #%sei"; // ADDI <rt>, <rs>, <se immediate>
    case 0b000000:
        switch (instruction.get_sub_opcode())
        {
        case 0b000000:
            return "sll $%rt, $%rs, #%shi"; // SLL <rd>, <rt>, <shift immediate>
        case 0b101011:
            return "slti $%rd, $%rt, #%rs"; // SLTI <rd>, <rt>, <rs>
          case 0b100101:
            return "or $%rd, $%rs, $%rt"; // OR <rd>, <rs>, <rt>
        case 0b100001:
            return "addu $%rd, $%rs, $%rt"; // ADDU <rd>, <rs>, <rt>
        }
        break;

    case 0b001111:
        return "lui $%rt, #%i"; // LUI <rt>, <immediate>
    case 0b101011:
        return "sw $%rt, #%sei($%rs)"; // SW <rt>, <se offset>($rs)
    case 0b100011:
        return "lw $%rt, #%sei($%rs)"; // LW <rt>, <se offset>($rs)
    case 0b101001:
        return "sh $%rt, #%sei($%rs)"; // SH <rt>, <se offset>($rs)
    case 0b000010:
        return "j #%sei"; // J <se address>
    case 0b000101:
        return "bne $%rs, $%rt, #%sei"; // BNE <rs>, <rt>, <se immediate>
    case 0b010000:
        switch (instruction.get_cop_opcode())
        {
        case 0b00100:
            return "mtc0 $%rt, $%rd"; // MTC0 <rt>, <rd>

        }
        break;
    }
    return "Unknown opcode";
}

std::string get_formatted_instruction(const Instruction &instruction)
{
    uint32_t rs = instruction.get_rs();
    uint32_t rt = instruction.get_rt();
    uint32_t rd = instruction.get_rd();
    uint32_t imm = instruction.get_imm();
    uint32_t shift_imm = instruction.get_shift_imm();
    int32_t se_imm = instruction.get_se_imm();

    std::string formatted_instruction = get_opcode_string(instruction);

    if (formatted_instruction.find("%sei") != std::string::npos)
    {
        formatted_instruction.replace(formatted_instruction.find("%sei"), 4, fmt::format("{:#x}", se_imm));
    }

    if (formatted_instruction.find("%shi") != std::string::npos)
    {
        formatted_instruction.replace(formatted_instruction.find("%shi"), 4, fmt::format("{:#x}", shift_imm));
    }

    if (formatted_instruction.find("%rs") != std::string::npos)
    {
        formatted_instruction.replace(formatted_instruction.find("%rs"), 3, REGISTER_NAMES[rs]);
    }

    if (formatted_instruction.find("%rd") != std::string::npos)
    {
        formatted_instruction.replace(formatted_instruction.find("%rd"), 3, REGISTER_NAMES[rd]);
    }

    if (formatted_instruction.find("%rt") != std::string::npos)
    {
        formatted_instruction.replace(formatted_instruction.find("%rt"), 3, REGISTER_NAMES[rt]);
    }

    if (formatted_instruction.find("%i") != std::string::npos)
    {
        formatted_instruction.replace(formatted_instruction.find("%i"), 2, fmt::format("{:#x}", imm));
    }

    return formatted_instruction;
}
