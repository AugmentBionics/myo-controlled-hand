//SENSING
#include "Arduino.h"
#include "SensingMessaging.h"

void setup() {
    Serial.begin(9600);
    Serial.println("Sensing Arduino starting...");
}

SensingMessageHandler messageHandler;

void loop() {
    messageHandler.handleSerial();
}