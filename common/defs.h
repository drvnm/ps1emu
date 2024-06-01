#pragma once

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// GLOBAL DEFINES
#define BIOS_SIZE 512 * 1024 // 512 KB

// HELPER FUNCTIONS
void VENU_LOG_INFO(const std::string &message);
void VENU_LOG_SUCCESS(const std::string &message);
void VENU_LOG_ERROR(const std::string &message);

