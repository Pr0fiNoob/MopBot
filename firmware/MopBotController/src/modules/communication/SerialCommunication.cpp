#include <Arduino.h>

#include "SerialCommunication.h"

SerialCommunication::SerialCommunication(Stream& port)
    : serialPort(port),
    bufferIndex(0),
    messageAvailable(false) {
    receiveBuffer[0] = '\0';
}

void SerialCommunication::update() {
    while (serialPort.available() > 0 && !messageAvailable) {
        char receivedCharacter =
            static_cast<char>(serialPort.read());

        // Ignore carriage returns.
        if (receivedCharacter == '\r') {
            continue;
        }

        // A newline marks the end of the message.
        if (receivedCharacter == '\n') {
            receiveBuffer[bufferIndex] = '\0';

            if (bufferIndex > 0) {
                messageAvailable = true;
            }

            bufferIndex = 0;
            continue;
        }

        // Leave one byte free for the terminating '\0'.
        if (bufferIndex < BUFFER_SIZE - 1) {
            receiveBuffer[bufferIndex] = receivedCharacter;
            bufferIndex++;
        } else {
            // Discard messages that are too long.
            bufferIndex = 0;
            receiveBuffer[0] = '\0';

            sendMessage("ERROR MESSAGE_TOO_LONG");
        }
    }
}

bool SerialCommunication::hasMessage() const {
    return messageAvailable;
}

char* SerialCommunication::getMessage() {
    return receiveBuffer;
}

void SerialCommunication::clearMessage() {
    messageAvailable = false;
    receiveBuffer[0] = '\0';
}

void SerialCommunication::sendMessage(const char* message) {
    serialPort.println(message);
}