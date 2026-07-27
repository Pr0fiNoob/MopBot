#include <Arduino.h>

// Configuration
#include "src/config/PinConfig.h"

// Modules
#include "src/modules/motors/MotorDriver.h"
#include "src/modules/communication/SerialCommunication.h"
#include "src/modules/communication/CommandParser.h"

MotorDriver mot1 = MotorDriver(
    PinConfig::MOT1_DIR_PIN,
    PinConfig::MOT1_PWM_PIN,
    PinConfig::MOT1_BRK_PIN,
    PinConfig::MOT1_SEN_PIN,
    PinConfig::MOT1_TMP_PIN,
    PinConfig::MOT1_LED_PIN
);

MotorDriver mot2 = MotorDriver(
    PinConfig::MOT2_DIR_PIN,
    PinConfig::MOT2_PWM_PIN,
    PinConfig::MOT2_BRK_PIN,
    PinConfig::MOT2_SEN_PIN,
    PinConfig::MOT2_TMP_PIN,
    PinConfig::MOT2_LED_PIN
);

SerialCommunication serialComm(Serial);
CommandParser commandParser;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    serialComm.sendMessage("Serial Communication Initialized");

    mot1.init();
    mot2.init();
    serialComm.sendMessage("Motor Drivers Initialized");
}

void loop() {
    // put your main code here, to run repeatedly:
    serialComm.update();

    if (serialComm.hasMessage()) {
        char* message = serialComm.getMessage();

        ParsedCommand parsed = commandParser.parseCommand(message);

        switch (parsed.command) {
            case CommandType::Ping:
                serialComm.sendMessage("PONG");
                break;
            
            case CommandType::Status:
                serialComm.sendMessage("STATUS READY");
                break;

            case CommandType::Speed:
                if (parsed.argument == nullptr) {
                    serialComm.sendMessage("ERR: Invalid Argument (nullptr)");
                    break;
                }
                
                {
                    int speed = atoi(parsed.argument);

                    if (speed < 0 || speed > 255) {
                        serialComm.sendMessage("ERR: Argument out of bounds (0-255)");
                        break;
                    }

                    mot1.setSpeed(static_cast<uint8_t>(speed));
                    mot2.setSpeed(static_cast<uint8_t>(speed));

                    serialComm.sendMessage("OK SPEED");
                }
                break;
            
            case CommandType::Direction:
                if (parsed.argument == nullptr) {
                    serialComm.sendMessage("ERR Invalid Argument (nullptr)");
                    break;
                }

                {
                    int direction = atoi(parsed.argument);

                    if (direction != 0 && direction != 1) {
                        serialComm.sendMessage("ERR: Argument out of bounds (0-1)");
                        break;
                    }

                    mot1.setDirection(direction == 1);
                    mot2.setDirection(direction == 1);

                    serialComm.sendMessage("OK DIR");
                }
                break;
            
            case CommandType::Brake:
                if (parsed.argument == nullptr) {
                    serialComm.sendMessage("ERR: Invalid Argument (nullptr)");
                    break;
                }

                {
                    int brake = atoi(parsed.argument);

                    if (brake != 0 && brake != 1) {
                        serialComm.sendMessage("ERR: Argument out of bounds (0-1)");
                        break;
                    }

                    mot1.brake(brake == 1);
                    mot1.brake(brake == 1);

                    serialComm.sendMessage("OK BRAKE");
                }
                break;
            
            case CommandType::Unknown:
            default:
                serialComm.sendMessage("ERR: Unknown Command");
                break;
        }

        serialComm.clearMessage();
    }
}
