#pragma once

namespace PinConfig {
    constexpr uint8_t MOT1_DIR_PIN = 2;   // Direction Pin for Motorcontroller 1
    constexpr uint8_t MOT1_PWM_PIN = 3;   // PWM Pin for Motorcontroller 1
    constexpr uint8_t MOT1_BRK_PIN = 4;   // Break Pin for Motorcontroller 1
    constexpr uint8_t MOT1_SEN_PIN = A3;  // Motor Current Sense Pin for Motorcontroller 1
    constexpr uint8_t MOT1_TMP_PIN = 7;   // Temperature Warning Pin for Motorcontroller 1
    constexpr uint8_t MOT1_LED_PIN = 9;   // LED Pin for Motorcontroller 1 (Temperature Warning)

    constexpr uint8_t MOT2_DIR_PIN = 8;   // Direction Pin for Motorcontroller 2
    constexpr uint8_t MOT2_PWM_PIN = 5;   // PWM Pin for Motorcontroller 2
    constexpr uint8_t MOT2_BRK_PIN = 12;  // Break Pin for Motorcontroller 2
    constexpr uint8_t MOT2_SEN_PIN = A2;  // Motor Current Sense Pin for Motorcontroller 2
    constexpr uint8_t MOT2_TMP_PIN = 6;   // Temperature Warning Pin for Motorcontroller 2
    constexpr uint8_t MOT2_LED_PIN = 10;  // LED Pin for Motorcontroller 2 (Temperature Warning)
}