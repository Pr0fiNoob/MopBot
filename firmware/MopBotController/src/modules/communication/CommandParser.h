#pragma once

#include <Arduino.h>

enum class CommandType : uint8_t {
    Ping,
    Status,
    Speed,
    Direction,
    Brake,
    Unknown
};

struct ParsedCommand {
    CommandType command;
    char* argument;
};

class CommandParser {
    public:
        /**
        Seperates the command and its arguments.
        @return ParsedCommand struct
        */
        ParsedCommand parseCommand(char* input);
    
    private:
        /**
        Parses a Command-String.
        @return CommandType Enum
        */
        CommandType parseCommandType (const char* command);
};
