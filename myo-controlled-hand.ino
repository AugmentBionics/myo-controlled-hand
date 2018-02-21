#include <Servo.h>
#include "Config.h"
#include "MotorController.h"
#include "GripLoader.h"

int buttonPin                 = BUTTON_PIN;
int pins[NUMBER_OF_ACTUATORS] = { MOTOR_1_PIN, MOTOR_2_PIN, MOTOR_3_PIN };
struct Mapping linearMapping[2] = {
  { 0,    0 },
  { 0, 1024 }
};

struct Config actuatorConfigs[NUMBER_OF_ACTUATORS] = {
  {
    "thumb",
    MOTOR_1_PIN,
    linearMapping,
    2,
    0,
    1024
  }
};

MotorController mc = MotorController(actuatorConfigs);
GripLoader gl      = GripLoader();

void setup() {}

void loop() {}
