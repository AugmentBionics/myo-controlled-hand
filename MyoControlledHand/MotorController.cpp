#include "Grips.h"
#include "MotorController.h"

MotorController::MotorController() {
    _currentGrip = grips[0];
}

void MotorController::init() {
    pwm.begin();
    pwm.setPWMFreq(24.0f);
    Wire.begin();
}

void MotorController::setGrip(Grip grip) {
    _currentGrip = grip;

}

void MotorController::open(unsigned int i) {
    pwm.setPin(reversePins[i], 4096);
    pwm.setPin(forwardPins[i], 0);
}

void MotorController::close(unsigned int i) {
    pwm.setPin(reversePins[i], 4096);
    pwm.setPin(forwardPins[i], 0);
}

void MotorController::brake(unsigned int i) {
    pwm.setPin(reversePins[i], 4096);
    pwm.setPin(forwardPins[i], 4096);
}

void MotorController::idle(unsigned int i) {
    pwm.setPin(reversePins[i], 0);
    pwm.setPin(forwardPins[i], 0);
}

bool MotorController::checkCurrentLimiting(unsigned int i) {
    return false;
}

void MotorController::setCurrentLimit(unsigned int i, unsigned int limit) {
    Wire.beginTransmission(CURRENT_LIMITER_ADDR);//i2c device address
    Wire.write(limPins[i]); //M0 memory address
    Wire.write(limit); //Current limiting value
    Wire.endTransmission();
}
