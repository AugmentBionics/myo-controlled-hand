#include "Arduino.h"
#include "UIMessaging.h"
#include "Grips.h"

void UIMessageHandler::interpretMessage(int length) {
    if (length <= 2) return;

    if (messageBuffer[0] == address) {
        // Message is for UI arduino -> interpret

        Serial.print("Message: ");
        for (int i = 0; i < length; ++i)
            Serial.write(messageBuffer[i]);
        Serial.print('\n');

        Serial.print("=> ");

        switch (messageBuffer[1]) {

            case 'l': // update grip list
            {
                int gIndex = int(messageBuffer[2] - '0');
                Serial.print("Update grip[");
                Serial.print(gIndex);
                Serial.print("] name: ");
                int k;
                char nextChar;
                for (k = 4, nextChar = messageBuffer[k];
                     nextChar != '\n' && k < 10; nextChar = messageBuffer[++k]) {
                    grips[gIndex].name[k - 4] = nextChar;
                }
                Serial.print(String(grips[gIndex].name));
                Serial.print('\n');
                break;
            }

            case 's': // select grip
            {
                int gIndex = int(messageBuffer[2] - '0');
                if (gIndex <= 1) {
                    // primary grip
                    Serial.println("Primary grip...");
                    break;
                } else {
                    // secondary grip
                    Serial.println("Secondary grip...");
                    break;
                }
            }

            default:break;
        }
    } else {
        Serial.write('@');
        Serial.println(String(messageBuffer));
    }
    newMessage = false;
    clearMessageBuffer();
}

UIMessageHandler::UIMessageHandler() : MessageHandler('u') {}
