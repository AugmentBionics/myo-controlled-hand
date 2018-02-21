#include "Arduino.h"
#include "MotorController.h"
#include "Actuator.h"
#include "GripUtil.h"
#include <Servo.h>

MotorController::MotorController(struct Config configs[NUMBER_OF_ACTUATORS]) {
  _currentGrip = { .name = "initial grip", .type = simple };

  for (int i = 0; i < NUMBER_OF_ACTUATORS; i++) {
    _actuators[i] = Actuator::Actuator(configs[i]);
  }
}

void MotorController::handleDynamicActuation(int myoInput) {
  int constrainedInput = constrain(myoInput, 0, 1023);

  struct ActuationPattern ap = _currentGrip.actuationPattern;
}

void MotorController::setHandPosition(struct Grip grip) {
  if (grip.type != triggered) {
    // First motion -> second motion -> etc.
    // i.e. for each "batch" in the order
    for (int i = 0; i < NUMBER_OF_ACTUATORS; i++) {
      // Scan through order
      for (int j = 0; j < NUMBER_OF_ACTUATORS; j++) {
        // If order value == "batch" number
        if (grip.order[j] == i) {
          // set actuator of corresponding index to move
          moveActuator(_actuators + j, grip.fingerPositions[j]);
        }
      }
      delay(grip.motionStepDelay);
    }
  }
}

void MotorController::moveActuator(Actuator *actuator,
                                   int       position) {
  int remappedPosition = remap(actuator, position);

  actuator->setPosition(remappedPosition);
}

int MotorController::remap(Actuator *actuator, int position) {
  struct Config config = actuator->getConfig();
  int outputPosition   = constrain(position, 0, 1023);

  int i = 0;

  // Scan through mappings to set lower bounds for interpolation
  int inputRangeMin  = 0;
  int outputRangeMin = 0;

  for (i = 0; i < config.controlCurveResolution; i++) {
    if (outputPosition > config.controlCurve[i].input) {
      inputRangeMin  = config.controlCurve[i].input;
      outputRangeMin = config.controlCurve[i].output;
    }
  }

  // Setup upper interpolation bounds
  int inputRangeMax  = 1023;
  int outputRangeMax = 1023;

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
