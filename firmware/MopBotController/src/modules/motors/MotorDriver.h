#pragma once

#include <Arduino.h>

class MotorDriver {
private:
    uint8_t dirPin;
    uint8_t pwmPin;
    uint8_t brkPin;
    uint8_t senPin;
    uint8_t tmpPin;
    uint8_t ledPin;

public:
    MotorDriver(
        uint8_t dir,
        uint8_t pwm,
        uint8_t brk,
        uint8_t sen,
        uint8_t tmp,
        uint8_t led
    );

    /**
    Initializes the motor driver by setting the pin modes.
    */
    void init();

    /**
    Sets the direction of the motor.
    @param forward: True for forward, False for backward
    */
    void setDirection(bool forward);

    /**
    Sets the speed of the motor using PWM.
    @param speed: Speed value (0-255)
    */
    void setSpeed(uint8_t speed);

    /**
    Engages or disengages the brake.
    @param engage: True to engage the brake, False to disengage
    */
    void brake(bool engage);

    /**
    Checks if the motor driver is overheated.
    @return: True if overheated, False otherwise
    */
    bool isOverheated();

    /**
    Reads the current draw of the motor.
    The current is calculated as follows:
    I = V / (0.000377 * R)
    @return: Current draw of the motor
    */
    float readCurrent();
};