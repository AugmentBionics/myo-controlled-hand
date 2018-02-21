#include <Servo.h>
#include "Config.h"
#include "MotorController.h"
#include "GripLoader.h"

const int buttonPin PROGMEM                 = BUTTON_PIN;
const int pins[NUMBER_OF_ACTUATORS] PROGMEM = {
  MOTOR_1_PIN,
  MOTOR_2_PIN,
  MOTOR_3_PIN
};
const struct Mapping linearMapping[2] PROGMEM = {
  { 0,    0 },
  { 0, 1024 }
};

const struct Config actuatorConfigs[NUMBER_OF_ACTUATORS] PROGMEM = {
  {
    "thumb",
    MOTOR_1_PIN,
    linearMapping,
    2,
    0,
    1023
  },
  {
    "indexFinger",
    MOTOR_2_PIN,
    linearMapping,
    2,
    0,
    1023
  },
  {
    "otherFingers",
    MOTOR_3_PIN,
    linearMapping,
    2,
    0,
    1023
  }
};

MotorController mc = MotorController(actuatorConfigs);
GripLoader gl      = GripLoader();

void setup() {}

void loop()  {}
