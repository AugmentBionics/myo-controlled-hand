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

  return interpolateOnCurve(
           position,
           0,
           1023,
           config.controlCurveconfig.
           controlCurveResolution,
           config.lowerLimit,
           config.upperLimit);
}

int interpolateOnCurve(int             input,
                       int             rangeMin,
                       int             rangeMax,
                       struct Mapping *curve,
                       int             curveResolution,
                       int             finalRangeMin,
                       int             finalRangeMax) {
  int output = constrain(input, rangeMin, rangeMax);

  int i = 0;

  // Scan through mappings to set lower bounds for interpolation
  int inputRangeMin  = rangeMin;
  int outputRangeMin = rangeMin;

  for (i = 0; i < curveResolution; i++) {
    if (output > curve[i].input) {
      inputRangeMin  = curve[i].input;
      outputRangeMin = curve[i].output;
    }
  }

  // Setup upper interpolation bounds
  int inputRangeMax  = rangeMax;
  int outputRangeMax = rangeMax;

  if (i < curveResolution - 1) {
    inputRangeMax  = curve[i + 1].output;
    outputRangeMax = curve[i + 1].output;
  }
  output = map(output,
               inputRangeMin,
               inputRangeMax,
               outputRangeMin,
               outputRangeMax);
  output = map(output,
               outputRangeMin,
               outputRangeMax,
               finalRangeMin,
               finalRangeMax);
  return output;
}
