#pragma once

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Instruction;

// GLOBAL DEFINES
#define BIOS_SIZE 512 * 1024 // 512 KB

// HELPER FUNCTIONS
void VENU_LOG_INFO(const std::string &message);
void VENU_LOG_SUCCESS(const std::string &message);
void VENU_LOG_ERROR(const std::string &message);

// dissasembly array where each index corresponds to an opcode
extern std::string opcodes_disasm[100];
void setup_opcodes();
std::string get_formatted_instruction(const Instruction& instruction);
