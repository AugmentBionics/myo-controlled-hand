#include "Arduino.h"
#include "Messaging.h"

void MessageHandler::clearMessageBuffer() {
    for (char &c : messageBuffer) {
        c = 0;
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
                Serial.println(F("Message too long!!!"));
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

void MessageHandler::sendMessage(char targetAddress, const String &message) const {
    Serial.write('@');
    Serial.write(targetAddress);
    Serial.println(message);
}