//MOTOR
#include "Arduino.h"
#include "MotorMessaging.h"

MotorState state;

void setup() {
    Serial.begin(9600);
    Serial.println(F("Motor Arduino starting..."));
    state.init();
}

MotorMessageHandler messageHandler(&state);

void loop() {
    messageHandler.handleSerial();
    state.update();
}
