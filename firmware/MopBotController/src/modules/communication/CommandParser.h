#pragma once

#include <Arduino.h>

enum class CommandType : uint8_t {
    Ping,
    Status,
    Speed,
    Direction,
    Stop,
    EmergencyStop,
    Reset,
    Unknown
};

struct ParsedCommand {
    CommandType command;
    char* argument;
};

class CommandParser {
public:
    /**
     * Separates the command and its first argument.
     *
     * @return ParsedCommand struct
     */
    ParsedCommand parseCommand(char* input);

private:
    /**
     * Converts a command string into a CommandType value.
     */
    CommandType parseCommandType(const char* command);
};
