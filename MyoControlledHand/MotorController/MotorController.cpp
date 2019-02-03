#include "Arduino.h"
#include "MotorController.h"

#define DEBUG_LOG(message) if(debug){Serial.println(message);}
#define DEBUG_LOG_TUPLE(m1, m2) if(debug){Serial.print(m1); Serial.print(", "); Serial.println(m2);}

//#define CURRENT_POLLING_RATE 10
//static const uint16_t ocr1aValue = static_cast<const uint16_t>(62500.0f / float(CURRENT_POLLING_RATE));


MotorController::MotorController(bool debug) : debug(debug) {
    _currentGrip = {.name = "initial grip", .type = simple};
}

MotorController::MotorController() : MotorController(false) {
}

void MotorController::init(Actuator::Config configs[NUMBER_OF_ACTUATORS]) {
    for (int i = 0; i < NUMBER_OF_ACTUATORS; i++) {
        _actuators[i] = Actuator(configs[i]);
    }
}

void MotorController::setGrip(Grip grip) {
    _currentGrip = grip;
    DEBUG_LOG("Set grip to ");
    DEBUG_LOG(_currentGrip.name);

    for (uint16_t i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
        if (_currentGrip.actuationPattern[i] == ActuationScheme::close) {
            _actuators[i].runForward();
            DEBUG_LOG_TUPLE(_actuators[i].getName(), "FWD");
        } else if (_currentGrip.actuationPattern[i] == ActuationScheme::open) {
            _actuators[i].runReverse();
            DEBUG_LOG_TUPLE(_actuators[i].getName(), "REV");
        }
    }

    uint16_t limitCounts[NUMBER_OF_ACTUATORS];
    const uint8_t threshold = 10;
    bool done = false;
    while (!done) {
        done = true;
        for (uint16_t i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
            if (_currentGrip.actuationPattern[i] == ActuationScheme::close
                || _currentGrip.actuationPattern[i] == ActuationScheme::open) {
                if (_actuators[i].isLimited()) {
                    limitCounts[i] += 1;
                    done = done && limitCounts[i] > threshold;
                } else {
                    limitCounts[i] = 0;
                }
            }
        }
    }

    for (uint16_t i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
        if (_currentGrip.actuationPattern[i] == ActuationScheme::close
            || _currentGrip.actuationPattern[i] == ActuationScheme::open) {
            _actuators[i].coast();
            DEBUG_LOG_TUPLE(_actuators[i].getName(), "CST");
        }
    }
}

bool MotorController::checkCurrentLimiting(uint16_t actuatorIndex) {
    return checkCurrentLimiting(_actuators[actuatorIndex]);
}

bool MotorController::checkCurrentLimiting(Actuator actuator) {
    return actuator.isLimited();
}

bool *MotorController::checkCurrentLimiting() {
    for (uint16_t i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
        _currentLimitingValues[i] = checkCurrentLimiting(i);
    }
    return _currentLimitingValues;
}

void MotorController::open() {
    for (uint16_t i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
        if (_currentGrip.actuationPattern[i] == ActuationScheme::actuate)
            _actuators[i].runReverse();
    }
}

void MotorController::close() {
    for (uint16_t i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
        if (_currentGrip.actuationPattern[i] == ActuationScheme::actuate)
            _actuators[i].runForward();
    }
}

void MotorController::brake() {
    for (uint16_t i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
        if (_currentGrip.actuationPattern[i] == ActuationScheme::actuate)
            _actuators[i].brake();
    }
}

void MotorController::coast() {
    for (uint16_t i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
        if (_currentGrip.actuationPattern[i] == ActuationScheme::actuate)
            _actuators[i].coast();
    }
}