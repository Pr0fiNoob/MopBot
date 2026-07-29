#include "State.h"

State::State()
    : currentState(RobotState::Booting) {
}

void State::begin() {
    transitionTo(RobotState::Idle);
}

bool State::transitionTo(RobotState newState) {
    if (!isTransitionAllowed(currentState, newState)) {
        return false;
    }

    currentState = newState;
    return true;
}

RobotState State::getState() const {
    return currentState;
}

bool State::isInState(RobotState state) const {
    return currentState == state;
}

const char* State::getStateName() const {
    return toString(currentState);
}

const char* State::toString(RobotState state) {
    switch (state) {
        case RobotState::Booting:
            return "Booting";

        case RobotState::Idle:
            return "Idle";

        case RobotState::Driving:
            return "Driving";

        case RobotState::Cleaning:
            return "Cleaning";

        case RobotState::EmergencyStop:
            return "EmergencyStop";

        case RobotState::Fault:
            return "Fault";
    }

    return "Unknown";
}

bool State::isTransitionAllowed(
    RobotState from,
    RobotState to
) const {
    // Re-entering the current state is harmless.
    if (from == to) {
        return true;
    }

    // Safety states must always be reachable.
    if (
        to == RobotState::EmergencyStop ||
        to == RobotState::Fault
    ) {
        return true;
    }

    switch (from) {
        case RobotState::Booting:
            return to == RobotState::Idle;

        case RobotState::Idle:
            return (
                to == RobotState::Driving ||
                to == RobotState::Cleaning
            );

        case RobotState::Driving:
            return (
                to == RobotState::Idle ||
                to == RobotState::Cleaning
            );

        case RobotState::Cleaning:
            return (
                to == RobotState::Idle ||
                to == RobotState::Driving
            );

        // Leaving a safety state is only possible through an explicit
        // transition to Idle. MopBotController performs the safety checks.
        case RobotState::EmergencyStop:
            return to == RobotState::Idle;

        case RobotState::Fault:
            return to == RobotState::Idle;
    }

    return false;
}
