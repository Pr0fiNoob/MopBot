#pragma once

namespace PinConfig {
    constexpr uint8_t MOT1_DIR_PIN = 2;   // Direction pin for motor controller 1
    constexpr uint8_t MOT1_PWM_PIN = 3;   // PWM pin for motor controller 1
    constexpr uint8_t MOT1_BRK_PIN = 4;   // Brake pin for motor controller 1
    constexpr uint8_t MOT1_SEN_PIN = A3;  // Current sense pin for motor controller 1
    constexpr uint8_t MOT1_TMP_PIN = 7;   // Temperature warning pin for motor controller 1
    constexpr uint8_t MOT1_LED_PIN = 9;   // Temperature warning LED for motor controller 1

    constexpr uint8_t MOT2_DIR_PIN = 8;   // Direction pin for motor controller 2
    constexpr uint8_t MOT2_PWM_PIN = 5;   // PWM pin for motor controller 2
    constexpr uint8_t MOT2_BRK_PIN = 12;  // Brake pin for motor controller 2
    constexpr uint8_t MOT2_SEN_PIN = A2;  // Current sense pin for motor controller 2
    constexpr uint8_t MOT2_TMP_PIN = 6;   // Temperature warning pin for motor controller 2
    constexpr uint8_t MOT2_LED_PIN = 10;  // Temperature warning LED for motor controller 2
}
