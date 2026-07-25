#include <Arduino.h>
#include "MotorDriver.h"
#include "../../config/CircuitConfig.h"

MotorDriver::MotorDriver(uint8_t dir, uint8_t pwm, uint8_t brk, uint8_t sen, uint8_t tmp, uint8_t led) {
    dirPin = dir;
    pwmPin = pwm;
    brkPin = brk;
    senPin = sen;
    tmpPin = tmp;
    ledPin = led;
}

void MotorDriver::init() {
    pinMode(dirPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);
    pinMode(brkPin, OUTPUT);
    pinMode(senPin, INPUT);
    pinMode(tmpPin, INPUT);
    pinMode(ledPin, OUTPUT);
}

void MotorDriver::setDirection(bool forward) {
    if (forward) {
        digitalWrite(dirPin, HIGH);
    } else {
        digitalWrite(dirPin, LOW);
    }
}

void MotorDriver::setSpeed(uint8_t speed) {
    analogWrite(pwmPin, speed);
}

void MotorDriver::brake(bool engage) {
    if (engage) {
        digitalWrite(brkPin, HIGH);
    } else {
        digitalWrite(brkPin, LOW);
    }
}

bool MotorDriver::isOverheated() {
    if (digitalRead(tmpPin) == LOW) {
        digitalWrite(ledPin, HIGH);
        return true;
    } else {
        digitalWrite(ledPin, LOW);
        return false;
    }
}

float MotorDriver::readCurrent() {
    float voltage = analogRead(senPin) * (CircuitConfig::ADC_REFERENCE / CircuitConfig::ADC_MAX); // Convert analog reading to voltage
    float current = voltage / (CircuitConfig::MOT_CURRENT_SENSE_CONVERSION_FACTOR * CircuitConfig::MOT_CURRENT_SENSE_RESISTANCE); // Calculate current using the conversion factor and resistance

    return current;
}
