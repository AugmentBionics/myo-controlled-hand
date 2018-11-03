#include "Arduino.h"
#include "MotorController.h"
#include "Actuator.h"
#include "GripUtil.h"

static inline int8_t sgn(int val) {
    if (val < 0) return -1;
    if (val == 0) return 0;
    return 1;
}

MotorController::MotorController() {
    _currentGrip = {.name = "initial grip", .type = simple};
}

void MotorController::init(Config configs[NUMBER_OF_ACTUATORS], int lower, int upper) {
    _upperThreshold = upper;
    _lowerThreshold = lower;
    for (int i = 0; i < NUMBER_OF_ACTUATORS; i++) {
        _actuators[i] = Actuator(configs[i]);
    }
}

void MotorController::handleDynamicActuation(int myoInput) {
    if (_currentGrip.type != dynamic) {
        return;
    }
    for (int i = 0; i < NUMBER_OF_ACTUATORS; i++) {
        ActuationPattern ap = _currentGrip.actuationPattern[i];

        if (!ap.isActuated) {
            //Serial.print(_actuators[i].getConfig().name); Serial.println(" is not actuated");
            continue;
        }
        //Serial.print(_actuators[i].getConfig().name); Serial.println(" is actuated");

        int deltaPosition = ap.actuationGoalPosition - _actuators[i].getPosition();
        int nudge = 0;
        //    Serial.print(deltaPosition); Serial.print(" - ");
        if (myoInput > _upperThreshold) {
            //      Serial.print(myoInput); Serial.print(" > ");
            nudge = 1;
        } else if (myoInput < _lowerThreshold) {
            //      Serial.print(myoInput); Serial.print(" < ");
            nudge = -1;
        }

        //    Serial.println(deltaPosition);

        moveActuator(_actuators + i, _actuators[i].getPosition() + 1 * nudge);
    }
}

void MotorController::setHandPosition(Grip grip) {
    Serial.println("Setting hand position");
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
    _currentGrip = grip;
}

void MotorController::moveActuator(Actuator *actuator,
                                   int position) {
    actuator->setPosition(position);
}

int MotorController::remap(Actuator *actuator, int position) {
    Config config = actuator->getConfig();

    return interpolateOnCurve(
        position,
        0,
        1023,
        config.controlCurve,
        config.controlCurveResolution,
        config.lowerLimit,
        config.upperLimit);
}

int MotorController::interpolateOnCurve(int input,
                                        int rangeMin,
                                        int rangeMax,
                                        Mapping *curve,
                                        int curveResolution,
                                        int finalRangeMin,
                                        int finalRangeMax) {
    int output = constrain(input, rangeMin, rangeMax);

    int i = 0;

    // Scan through mappings to set lower bounds for interpolation
    int inputRangeMin = rangeMin;
    int outputRangeMin = rangeMin;

    for (i = 0; i < curveResolution; i++) {
        if (output > curve[i].input) {
            inputRangeMin = curve[i].input;
            outputRangeMin = curve[i].output;
        }
    }

    // Setup upper interpolation bounds
    int inputRangeMax = rangeMax;
    int outputRangeMax = rangeMax;

    if (i < curveResolution - 1) {
        inputRangeMax = curve[i + 1].output;
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
