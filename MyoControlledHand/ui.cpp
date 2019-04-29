//UI
#include "Arduino.h"
#include "UIMessaging.h"

void setup() {
    Serial.begin(9600);
    Serial.println("UI Arduino starting...");
}

UIMessageHandler messageHandler;

void loop() {
    messageHandler.handleSerial();
}