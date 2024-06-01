#include <fstream>

#include "bios.h"

Bios::Bios(const char *path)
{
    VENU_LOG_INFO(std::string("Loading BIOS from ") + path);
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open BIOS file");
    }

    file.seekg(0, std::ios::end);
    data.resize(file.tellg());
    file.seekg(0, std::ios::beg);

    file.read(reinterpret_cast<char *>(data.data()), data.size());

    file.close();

    if (data.size() != BIOS_SIZE)
    {
        throw std::runtime_error("Invalid BIOS size");
    }
    VENU_LOG_SUCCESS("BIOS loaded successfully");
}

uint32_t Bios::read32(uint32_t offset) const
{

    if (offset >= data.size())
    {
        throw std::runtime_error("BIOS read out of bounds");
    }

    uint8_t byte0 = data[offset + 0];
    uint8_t byte1 = data[offset + 1];
    uint8_t byte2 = data[offset + 2];
    uint8_t byte3 = data[offset + 3];

    return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0; // little endian word size
}