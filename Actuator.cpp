#include "Arduino.h"
#include "Actuator.h"
#include <Servo.h>


Actuator::Actuator() {}

Actuator::Actuator(struct Config config) {
  init(config);
}

struct Config Actuator::getConfig() {
  return _config;
}

void Actuator::init(struct Config config) {
  if (_servo.attached()) {
    _servo.detach();
  }
  _config = config;
  _servo.attach(_config.pin);
}

void Actuator::setPosition(int position) {
  int microseconds = map(constrain(position, 0, 1023), 0, 1023, 2000, 1000);

  _servo.writeMicroseconds(microseconds);
}
