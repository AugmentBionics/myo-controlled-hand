#include "Arduino.h"
#include "MotorController.h"
#include "Actuator.h"
#include <Servo.h>

Actuator::Actuator() {}

Actuator::Actuator(struct Config config) {
  _config = config;
  _servo.attach(_config.pin);
}
