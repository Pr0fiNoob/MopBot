#include "CommandParser.h"

#include <string.h>

ParsedCommand CommandParser::parseCommand(char* input) {
    ParsedCommand result {
        CommandType::Unknown,
        nullptr
    };

    if (input == nullptr || input[0] == '\0') {
        return result;
    }

    char* commandString = strtok(input, " ");

    result.command = parseCommandType(commandString);
    result.argument = strtok(nullptr, " ");

    return result;
}

CommandType CommandParser::parseCommandType(const char* command) {
    if (command == nullptr) {
        return CommandType::Unknown;
    }

    if (strcmp(command, "PING") == 0) {
        return CommandType::Ping;
    }

    if (strcmp(command, "STATUS") == 0) {
        return CommandType::Status;
    }

    if (strcmp(command, "SPEED") == 0) {
        return CommandType::Speed;
    }

    if (strcmp(command, "DIR") == 0) {
        return CommandType::Direction;
    }

    if (strcmp(command, "STOP") == 0) {
        return CommandType::Stop;
    }

    if (strcmp(command, "ESTOP") == 0) {
        return CommandType::EmergencyStop;
    }

    if (strcmp(command, "RESET") == 0) {
        return CommandType::Reset;
    }

    return CommandType::Unknown;
}
