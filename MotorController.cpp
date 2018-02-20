#include "Arduino.h"
#include "MotorController.h"
#include "Actuator.h"
#include <Servo.h>

MotorController::MotorController(struct Config *configs) {
  for (int i = 0; i < NUMBER_OF_ACTUATORS; i++) {
    _actuators[i] = Actuator::Actuator(configs[i]);
  }
}
