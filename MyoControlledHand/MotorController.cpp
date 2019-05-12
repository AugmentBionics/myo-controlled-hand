#include "Arduino.h"
#include "MotorController.h"

MotorController::MotorController() {}

void MotorController::init() {
    pwm.begin();
    pwm.setPWMFreq(24.0f);
    Wire.begin();
    for (int i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
        setCurrentLimit(i, 200);
        pinMode(rdPins[i], INPUT);
    }
}

void MotorController::open(unsigned int i) {
    Serial.print("MotorController::open\t");
    Serial.println(i);
    pwm.setPin(reversePins[i], 4096);
    pwm.setPin(forwardPins[i], 0);
    lastInstruction[i] = MotorInstruction::open;
}

void MotorController::close(unsigned int i) {
    Serial.print("MotorController::close\t");
    Serial.println(i);
    pwm.setPin(reversePins[i], 0);
    pwm.setPin(forwardPins[i], 4096);
    lastInstruction[i] = MotorInstruction::close;
    isOpen[i] = false;
}

void MotorController::brake(unsigned int i) {
    Serial.print("MotorController::brake\t");
    Serial.println(i);
    pwm.setPin(reversePins[i], 4096);
    pwm.setPin(forwardPins[i], 4096);
    lastInstruction[i] = MotorInstruction::brake;
}

void MotorController::idle(unsigned int i) {
    Serial.print("MotorController::idle\t");
    Serial.println(i);
    pwm.setPin(reversePins[i], 0);
    pwm.setPin(forwardPins[i], 0);
    lastInstruction[i] = MotorInstruction::idle;
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

bool MotorController::isClosed[NUMBER_OF_ACTUATORS] = {};
bool MotorController::isOpen[NUMBER_OF_ACTUATORS] = {};
MotorInstruction MotorController::lastInstruction[NUMBER_OF_ACTUATORS];
