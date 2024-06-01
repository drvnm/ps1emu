#include "defs.h"

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