//MOTOR
#include "Arduino.h"
#include "MotorMessaging.h"

void setup() {
    Serial.begin(9600);
    Serial.println(F("Motor Arduino starting..."));
}

MotorState state;
MotorMessageHandler messageHandler(&state);

void loop() {
    messageHandler.handleSerial();
}
