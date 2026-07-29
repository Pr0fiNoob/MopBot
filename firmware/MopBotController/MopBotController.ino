#include <Arduino.h>
#include <stdlib.h>

// Configuration
#include "src/config/PinConfig.h"

// Modules
#include "src/modules/motors/MotorDriver.h"
#include "src/modules/communication/SerialCommunication.h"
#include "src/modules/communication/CommandParser.h"
#include "src/modules/state/State.h"

MotorDriver mot1(
    PinConfig::MOT1_DIR_PIN,
    PinConfig::MOT1_PWM_PIN,
    PinConfig::MOT1_BRK_PIN,
    PinConfig::MOT1_SEN_PIN,
    PinConfig::MOT1_TMP_PIN,
    PinConfig::MOT1_LED_PIN
);

MotorDriver mot2(
    PinConfig::MOT2_DIR_PIN,
    PinConfig::MOT2_PWM_PIN,
    PinConfig::MOT2_BRK_PIN,
    PinConfig::MOT2_SEN_PIN,
    PinConfig::MOT2_TMP_PIN,
    PinConfig::MOT2_LED_PIN
);

SerialCommunication serialComm(Serial);
CommandParser commandParser;
State state;


void stopMotors(bool engageBrake) {
    mot1.setSpeed(0);
    mot2.setSpeed(0);

    mot1.brake(engageBrake);
    mot2.brake(engageBrake);
}

bool parseIntegerArgument(const char* argument, long minimum, long maximum, long& result) {
    if (argument == nullptr || argument[0] == '\0') {
        return false;
    }

    char* endPointer = nullptr;
    const long parsedValue = strtol(argument, &endPointer, 10);

    // Reject text such as "120abc" and completely non-numeric arguments.
    if (
        endPointer == argument ||
        *endPointer != '\0' ||
        parsedValue < minimum ||
        parsedValue > maximum
    ) {
        return false;
    }

    result = parsedValue;
    return true;
}

void sendStatus() {
    const bool mot1Overheated = mot1.isOverheated();
    const bool mot2Overheated = mot2.isOverheated();

    const float mot1Current = mot1.readCurrent();
    const float mot2Current = mot2.readCurrent();

    serialComm.sendStatusJson(
        state.getStateName(),
        mot1Current,
        mot1Overheated,
        mot2Current,
        mot2Overheated
    );
}

void updateSafetyState() {
    const bool mot1Overheated = mot1.isOverheated();
    const bool mot2Overheated = mot2.isOverheated();

    if (!mot1Overheated && !mot2Overheated) {
        return;
    }

    // Send the event only when Fault is entered, not on every loop.
    if (!state.isInState(RobotState::Fault)) {
        stopMotors(false);
        state.transitionTo(RobotState::Fault);

        if (mot1Overheated && mot2Overheated) {
            serialComm.sendMessage(
                "{\"Event\":\"Fault\",\"Reason\":\"BothMotorsOverheated\"}"
            );
        } else if (mot1Overheated) {
            serialComm.sendMessage(
                "{\"Event\":\"Fault\",\"Reason\":\"Motor1Overheated\"}"
            );
        } else {
            serialComm.sendMessage(
                "{\"Event\":\"Fault\",\"Reason\":\"Motor2Overheated\"}"
            );
        }
    }
}

void processCommand() {
    if (!serialComm.hasMessage()) {
        return;
    }

    char* message = serialComm.getMessage();
    const ParsedCommand parsed = commandParser.parseCommand(message);

    switch (parsed.command) {
        case CommandType::Ping:
            serialComm.sendMessage("PONG");
            break;

        case CommandType::Status:
            sendStatus();
            break;

        case CommandType::Speed: {
            long speed = 0;

            if (!parseIntegerArgument(parsed.argument, 0, 255, speed)) {
                serialComm.sendMessage("ERR SPEED_ARGUMENT_MUST_BE_0_TO_255");
                break;
            }

            if (
                state.isInState(RobotState::Booting) ||
                state.isInState(RobotState::EmergencyStop) ||
                state.isInState(RobotState::Fault)
            ) {
                serialComm.sendMessage("ERR SPEED_NOT_ALLOWED_IN_CURRENT_STATE");
                break;
            }

            if (speed == 0) {
                stopMotors(false);
                state.transitionTo(RobotState::Idle);
                serialComm.sendMessage("OK IDLE");
                break;
            }

            if (!state.transitionTo(RobotState::Driving)) {
                serialComm.sendMessage("ERR TRANSITION_TO_DRIVING_NOT_ALLOWED");
                break;
            }

            mot1.brake(false);
            mot2.brake(false);

            mot1.setSpeed(static_cast<uint8_t>(speed));
            mot2.setSpeed(static_cast<uint8_t>(speed));

            serialComm.sendMessage("OK DRIVING");
            break;
        }

        case CommandType::Direction: {
            long direction = 0;

            if (!parseIntegerArgument(parsed.argument, 0, 1, direction)) {
                serialComm.sendMessage("ERR DIR_ARGUMENT_MUST_BE_0_OR_1");
                break;
            }

            // Changing direction while moving could reverse the motors abruptly.
            if (!state.isInState(RobotState::Idle)) {
                serialComm.sendMessage("ERR DIRECTION_ONLY_ALLOWED_WHILE_IDLE");
                break;
            }

            const bool forward = direction == 1;

            mot1.setDirection(forward);
            mot2.setDirection(forward);

            serialComm.sendMessage("OK DIRECTION");
            break;
        }

        case CommandType::Stop:
            stopMotors(true);

            // STOP never clears an EmergencyStop or Fault state.
            if (
                !state.isInState(RobotState::EmergencyStop) &&
                !state.isInState(RobotState::Fault)
            ) {
                state.transitionTo(RobotState::Idle);
            }

            serialComm.sendMessage("OK STOPPED");
            break;

        case CommandType::EmergencyStop:
            stopMotors(true);
            state.transitionTo(RobotState::EmergencyStop);
            serialComm.sendMessage("OK EMERGENCY_STOP");
            break;

        case CommandType::Reset: {
            const bool mot1Overheated = mot1.isOverheated();
            const bool mot2Overheated = mot2.isOverheated();

            if (mot1Overheated || mot2Overheated) {
                serialComm.sendMessage("ERR RESET_BLOCKED_BY_OVERHEAT");
                break;
            }

            if (
                !state.isInState(RobotState::EmergencyStop) &&
                !state.isInState(RobotState::Fault)
            ) {
                serialComm.sendMessage("ERR RESET_NOT_REQUIRED");
                break;
            }

            stopMotors(false);

            if (state.transitionTo(RobotState::Idle)) {
                serialComm.sendMessage("OK IDLE");
            } else {
                serialComm.sendMessage("ERR RESET_TRANSITION_FAILED");
            }

            break;
        }

        case CommandType::Unknown:
        default:
            serialComm.sendMessage("ERR UNKNOWN_COMMAND");
            break;
    }

    serialComm.clearMessage();
}


void setup() {
    Serial.begin(115200);

    mot1.init();
    mot2.init();

    // Start in a safe, stationary condition.
    stopMotors(true);

    state.begin();

    serialComm.sendMessage("MOPBOT READY");
}


void loop() {
    serialComm.update();

    updateSafetyState();
    processCommand();
}
