#pragma once

#include <Arduino.h>

enum class RobotState : uint8_t {
    Booting,
    Idle,
    Driving,
    Cleaning,
    EmergencyStop,
    Fault
};

class State {
private:
    RobotState currentState;

    bool isTransitionAllowed(RobotState from, RobotState to) const;

public:
    State();

    /**
     * Finishes the boot process and changes the state to Idle.
     */
    void begin();

    /**
     * Attempts to change the current robot state.
     *
     * @return true if the transition was allowed.
     */
    bool transitionTo(RobotState newState);

    RobotState getState() const;

    bool isInState(RobotState state) const;

    /**
     * Returns the current state as a null-terminated string.
     */
    const char* getStateName() const;

    /**
     * Converts any RobotState value into a null-terminated string.
     */
    static const char* toString(RobotState state);
};
