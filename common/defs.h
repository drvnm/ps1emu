#pragma once
#define FMT_HEADER_ONLY
#include <fmt.h>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Instruction;

// GLOBAL DEFINES
#define BIOS_SIZE 512 * 1024 // 512 KB
#define MEM_CONTROL_SIZE 36
#define RAM_SIZE_SIZE 4
#define CACHE_CONTROL_SIZE 4

// HELPER FUNCTIONS
void VENU_LOG_INFO(const std::string &message);
void VENU_LOG_SUCCESS(const std::string &message);
void VENU_LOG_ERROR(const std::string &message);
void VENU_LOG_CRITICAL(const std::string &message);

std::string get_opcode_string(const Instruction& instruction);
std::string get_formatted_instruction(const Instruction& instruction);
