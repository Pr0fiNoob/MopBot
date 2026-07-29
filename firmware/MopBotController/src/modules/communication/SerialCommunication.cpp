#include "SerialCommunication.h"

SerialCommunication::SerialCommunication(Stream& port)
    : serialPort(port),
    bufferIndex(0),
    messageAvailable(false) {
    receiveBuffer[0] = '\0';
}

void SerialCommunication::update() {
    while (serialPort.available() > 0 && !messageAvailable) {
        const char receivedCharacter =
            static_cast<char>(serialPort.read());

        if (receivedCharacter == '\r') {
            continue;
        }

        if (receivedCharacter == '\n') {
            receiveBuffer[bufferIndex] = '\0';

            if (bufferIndex > 0) {
                messageAvailable = true;
            }

            bufferIndex = 0;
            continue;
        }

        // Keep one byte free for the terminating null character.
        if (bufferIndex < BUFFER_SIZE - 1) {
            receiveBuffer[bufferIndex] = receivedCharacter;
            bufferIndex++;
        } else {
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

void SerialCommunication::sendBoolean(bool value) {
    if (value) {
        serialPort.print(F("true"));
    } else {
        serialPort.print(F("false"));
    }
}

void SerialCommunication::sendStatusJson(
    const char* state,
    float motor1Current,
    bool motor1Overheated,
    float motor2Current,
    bool motor2Overheated
) {
    serialPort.print(F("{\"State\":\""));
    serialPort.print(state);

    serialPort.print(F("\",\"Motor1\":{\"MotorCurrent\":"));
    serialPort.print(motor1Current, 3);
    serialPort.print(F(",\"isOverheated\":"));
    sendBoolean(motor1Overheated);

    serialPort.print(F("},\"Motor2\":{\"MotorCurrent\":"));
    serialPort.print(motor2Current, 3);
    serialPort.print(F(",\"isOverheated\":"));
    sendBoolean(motor2Overheated);

    serialPort.println(F("}}"));
}
