#pragma once

#include <Arduino.h>

class SerialCommunication {
private:
    static constexpr uint8_t BUFFER_SIZE = 64;

    Stream& serialPort;

    char receiveBuffer[BUFFER_SIZE];
    uint8_t bufferIndex;
    bool messageAvailable;

public:
    /**
     * Creates a serial communication interface.
     *
     * @param port Serial interface to use.
     */
    explicit SerialCommunication(Stream& port);

    /**
     * Reads incoming serial data without blocking the program.
     */
    void update();

    /**
     * Checks whether a complete message was received.
     *
     * @return true when a complete message is available.
     */
    bool hasMessage() const;

    /**
     * Returns the received message.
     *
     * @return Pointer to the internal message buffer.
     */
    char* getMessage();

    /**
     * Marks the current message as processed.
     */
    void clearMessage();

    /**
     * Sends a line of text.
     *
     * @param message Null-terminated text to send.
     */
    void sendMessage(const char* message);
};