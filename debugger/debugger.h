#pragma once

#include <vector>
#include <string>
#include "../common/defs.h"

#define LOG_TYPE_ERROR 1
#define LOG_TYPE_INFO 2
#define LOG_TYPE_SUCCESS 3
#define LOG_TYPE uint8_t

struct LogLine
{
    std::string message;
    LOG_TYPE type;
};

class Debugger
{
public:
    static Debugger& getInstance()
    {
        static Debugger instance;
        return instance;
    }

    Debugger(const Debugger&) = delete;
    Debugger& operator=(const Debugger&) = delete;

    bool step_mode = true;
    bool do_step = false;
    int speed = 0;

    std::vector<LogLine> logs;

private:
    Debugger() = default;
};

