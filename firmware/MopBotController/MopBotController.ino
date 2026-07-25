#include <Arduino.h>

// Configuration
#include "src/config/PinConfig.h"

// Modules
#include "src/modules/motors/MotorDriver.h"

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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  mot1.init();
  mot2.init();
  Serial.println("Motors Initialized");
}

void loop() {
  // put your main code here, to run repeatedly:

}
