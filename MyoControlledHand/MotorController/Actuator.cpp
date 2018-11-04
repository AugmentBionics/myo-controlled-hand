#include "Arduino.h"
#include "Actuator.h"
#include <Servo.h>


Actuator::Actuator() {}

Actuator::Actuator(Config config) {
  init(config);
}

Config Actuator::getConfig() {
  return _config;
}

void Actuator::init(Config config) {
  _config = config;
  _servo.attach(_config.pin);
  Serial.print("Servo attached on pin:");
  Serial.println(_config.pin);
}

void Actuator::setPosition(int position) {
  int microseconds = map(constrain(position, 0, 1023), 0, 1023, _config.lowerLimit, _config.upperLimit);
  _servo.writeMicroseconds(microseconds);
  _currentPosition = constrain(position, 0, 1023);
}

int Actuator::getPosition() {
  return _currentPosition;
}
