//MOTOR
#include "Arduino.h"
#include "MotorMessaging.h"

const unsigned int MOTOR_COUNT = 4;

void setup() {
    Serial.begin(9600);
    Serial.println("Motor Arduino starting...");
    pinMode(13, OUTPUT);
}

MotorMessageHandler messageHandler;

void loop() {
    messageHandler.handleSerial();
}