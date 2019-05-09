#include <Grips.h>
#include "MotorController.h"

MotorController::MotorController() {
    _currentGrip = grips[0];
    pwm.begin();
    pwm.setPWMFreq(24.0f);
    Wire.begin();
}

void MotorController::setGrip(Grip grip) {
    _currentGrip = grip;

}

void MotorController::open(unsigned int i) {
    regState = regState & ~mBrake;
    regState = regState | (motorMasks[i] & mOpen);
    shiftOutWord(regState);
}

void MotorController::close(unsigned int i) {
    regState = regState & ~mBrake;
    regState = regState | (motorMasks[i] & mClose);
    shiftOutWord(regState);
}

void MotorController::brake(unsigned int i) {
    regState = regState & ~mBrake;
    regState = regState | (motorMasks[i] & mBrake);
    shiftOutWord(regState);

}

void MotorController::idle(unsigned int i) {
    //Not Implemented
}

bool MotorController::checkCurrentLimiting(unsigned int i) {
    return false;
}

void MotorController::shiftOutWord(unsigned int w) {
    for (unsigned int i = 0; i < 16; i++) {
        if (bitRead(w, i) == true) {
            if (bitRead(outState, i) == false) {
                //pwm.setPin(i, 4095);
            }
        } else if (bitRead(w, i) == false) {
            if (bitRead(outState, i) == true) {
                //pwm.setPin(i, 0);
            }
        }
    }
    outState = w;

}
