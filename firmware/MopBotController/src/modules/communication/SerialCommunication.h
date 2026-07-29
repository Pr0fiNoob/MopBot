#pragma once

#include <Arduino.h>

class SerialCommunication {
private:
    static constexpr uint8_t BUFFER_SIZE = 64;

    Stream& serialPort;

    char receiveBuffer[BUFFER_SIZE];
    uint8_t bufferIndex;
    bool messageAvailable;

    void sendBoolean(bool value);

public:
    explicit SerialCommunication(Stream& port);

    /**
     * Reads incoming serial data without blocking.
     */
    void update();

    bool hasMessage() const;

    char* getMessage();

    void clearMessage();

    void sendMessage(const char* message);

    /**
     * Sends the complete robot status as one JSON object.
     * Motor currents are sent in amperes with three decimal places.
     */
    void sendStatusJson(
        const char* state,
        float motor1Current,
        bool motor1Overheated,
        float motor2Current,
        bool motor2Overheated
    );
};
