#include "Arduino.h"
#include "Config.h"
#include "MotorController.h"

MotorController::MotorController() {}

void MotorController::init() {
    pwm.begin();
    pwm.setPWMFreq(24.0f);
    Wire.begin();
    for (int i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
        setCurrentLimit(i, currentLimits[i]);
        setDelPin(i, INIT_DEL_PIN_VAL);
        pinMode(rdPins[i], INPUT);
    }
}

void MotorController::open(unsigned int i) {
    if (isOpen[i])
        return;
    //Serial.print("MotorController::open\t");
    //Serial.println(i);
    pwm.setPin(reversePins[i], motorOpenSpeed[i]);
    pwm.setPin(forwardPins[i], 0);
    lastInstruction[i] = MotorInstruction::open;
}

void MotorController::close(unsigned int i) {
    //Serial.print("MotorController::close\t");
    //Serial.println(i);
    pwm.setPin(reversePins[i], 0);
    pwm.setPin(forwardPins[i], motorCloseSpeed[i]);
    lastInstruction[i] = MotorInstruction::close;
    isOpen[i] = false;
}

void MotorController::brake(unsigned int i, bool doNotLog) {
    //Serial.print("MotorController::brake\t");
    //Serial.println(i);
    pwm.setPin(reversePins[i], 4096);
    pwm.setPin(forwardPins[i], 4096);
    if (!doNotLog)
        lastInstruction[i] = MotorInstruction::brake;
}

void MotorController::brake(unsigned int i) {
    brake(i, true);
}

void MotorController::idle(unsigned int i, bool doNotLog) {
    //Serial.print("MotorController::idle\t");
    //Serial.println(i);
    pwm.setPin(reversePins[i], 0);
    pwm.setPin(forwardPins[i], 0);
    if (!doNotLog)
        lastInstruction[i] = MotorInstruction::idle;
}

void MotorController::idle(unsigned int i) {
    idle(i, true);
}

bool MotorController::checkCurrentLimiting(unsigned int i) {
    return digitalRead(rdPins[i]) == LOW;
}

void MotorController::setCurrentLimit(unsigned int i, unsigned int limit) {
    Wire.beginTransmission(CURRENT_LIMITER_ADDR);//i2c device address
    Wire.write(limPins[i]); //M0 memory address
    Wire.write(limit); //Current limiting value
    Wire.endTransmission();
}

void MotorController::setDelPin(unsigned int i, unsigned int value) {
    pwm.setPin(delPins[i], value);
}

bool MotorController::isClosed[NUMBER_OF_ACTUATORS] = {};
bool MotorController::isOpen[NUMBER_OF_ACTUATORS] = {};
MotorInstruction MotorController::lastInstruction[NUMBER_OF_ACTUATORS];
