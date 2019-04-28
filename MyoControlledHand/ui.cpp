//UI
#include "Arduino.h"
#include "UIMessaging.h"

void setup() {
    Serial.begin(9600);
    Serial.println("UI Arduino starting...");

    delay(1000);
    Serial.write('@');
    Serial.write('s');
    Serial.write('t');
    Serial.write('1');
    Serial.print("l54");
    Serial.print("u123");
    Serial.write('\n');
    delay(500);
    Serial.write('@');
    Serial.write('m');
    Serial.write('p');
    Serial.write('o');
    Serial.write('d');
    Serial.write('c');
    Serial.write('c');
    Serial.write('\n');
    delay(500);
    Serial.write('@');
    Serial.write('u');
    Serial.write('l');
    Serial.write('5');
    Serial.write('n');
    Serial.print("Key");
    Serial.write('\n');
    delay(500);
    Serial.write('@');
    Serial.write('m');
    Serial.write('m');
    Serial.write('o');
    Serial.write('\n');
    delay(500);
}

UIMessageHandler messageHandler;

void loop() {
    messageHandler.handleSerial();
}