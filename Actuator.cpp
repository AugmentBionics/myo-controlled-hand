#include "Arduino.h"
#include "Actuator.h"
#include <Servo.h>


Actuator::Actuator() {}

Actuator::Actuator(struct Config config) {
  init(config);
}

void Actuator::init(struct Config config) {
  if (_servo.attached()) {
    _servo.detach();
  }
  _config = config;
  _servo.attach(_config.pin);
}

void Actuator::setPosition(int position) {
  int remappedPosition = map(constrain(position, 0, 1023), 0, 1023, 0, 90);
  _servo.write(remappedPosition);
}
