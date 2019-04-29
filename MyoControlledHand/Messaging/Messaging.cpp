#include "Arduino.h"
#include "Messaging.h"

void MessageHandler::clearMessageBuffer() {
    for (int i = 0; i < 16; ++i) {
        messageBuffer[i] = 0;
    }
}
void MessageHandler::handleSerial() {
    if (newMessage)
        interpretMessage(messageLength);
    if (Serial.available() > 0) {
        char currChar = Serial.read();
        if (currChar == '@') {
            cursor = 0;
            messageBufferFilling = true;
            return;
        }
        if (messageBufferFilling) {
            if (cursor >= 16) {
                Serial.println("Message too long!!!");
                cursor = 0;
                messageBufferFilling = false;
                return;
            }
            if (currChar == '\n' && cursor > 1) {
                newMessage = true;
                messageBufferFilling = false;
                messageLength = cursor + 1;
                cursor = 0;
                return;
            }
            messageBuffer[cursor] = currChar;
            ++cursor;
        }
    }
}