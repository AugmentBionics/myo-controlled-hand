#include "Arduino.h"
#include "MotorController.h"
#include "Actuator.h"
#include "GripUtil.h"
#include <Servo.h>

MotorController::MotorController(struct Config *configs) {
  for (int i = 0; i < NUMBER_OF_ACTUATORS; i++) {
    _actuators[i] = Actuator::Actuator(configs[i]);
  }
}

void MotorController::setHandPosition(struct Grip grip) {
  switch (grip.type) {
  case simple:

    for (int i = 0; i < NUMBER_OF_ACTUATORS; i++) {
      for (int j = 0; j < NUMBER_OF_ACTUATORS; j++) {
        if (grip.order[j] == i) {}
      }
    }
    break;

  default:
    break;
  }
}

void MotorController::moveActuator(Actuator     *actuator,
                                   int           position,
                                   unsigned long delay) {
  int remappedPosition = remap(actuator, position);

  actuator->setPosition(remappedPosition);
}

int MotorController::remap(Actuator *actuator, int position) {
  struct Config config = actuator->getConfig();
  int outputPosition   = constrain(position, 0, 1023);

  int inputRangeMin  = 0;
  int inputRangeMax  = 1023;
  int outputRangeMin = 0;
  int outputRangeMax = 1023;
  int i              = 0;

  for (i = 0; i < config.controlCurveResolution; i++) {
    if (outputPosition > config.controlCurve[i].input) {
      inputRangeMin  = config.controlCurve[i].input;
      outputRangeMin = config.controlCurve[i].output;
    }
  }

  if (i < config.controlCurveResolution - 1) {
    inputRangeMax  = config.controlCurve[i + 1].output;
    outputRangeMax = config.controlCurve[i + 1].output;
  }
  outputPosition = map(outputPosition,
                       inputRangeMin,
                       inputRangeMax,
                       outputRangeMin,
                       outputRangeMax);
  outputPosition = map(outputPosition,
                       outputRangeMin,
                       outputRangeMax,
                       config.lowerLimit,
                       config.upperLimit);
  return outputPosition;
}
