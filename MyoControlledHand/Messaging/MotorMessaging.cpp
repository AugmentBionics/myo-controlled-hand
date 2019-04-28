#include "Arduino.h"
#include "MotorMessaging.h"
#include "../Config/Grips.h"

void MotorMessageHandler::interpretMessage(int length) {
    if (length <= 2) return;

    if (messageBuffer[0] == address) {
        // Message is for motor arduino -> interpret

        Serial.print("Message: ");
        for (int i = 0; i < length - 1; ++i)
            Serial.write(messageBuffer[i]);
        Serial.print('\n');

        Serial.print("=> ");

        switch (messageBuffer[1]) {

            case 'p': // set grip pattern
            {
                Serial.print("Set grip: ");
                for (int i = 2; i <= NUMBER_OF_ACTUATORS + 2; ++i) {
                    switch (messageBuffer[i]) {
                        case 'o': // opened
                            break;
                        case 'c': // closed
                            break;
                        case 'd': // dynamic
                            break;
                        default:break;
                    }
                    Serial.print(messageBuffer[i]);
                }
                Serial.print('\n');
                break;
            }

            case 'm': // move
            {
                Serial.print("Move: ");
                switch (messageBuffer[2]) {
                    case 'o': // open
                        Serial.println("open");
                        break;
                    case 'c': // close
                        Serial.println("close");
                        break;
                    case 'i': // idle
                        Serial.println("idle");
                        break;
                    case 'b': // brake
                        Serial.println("brake");
                        break;
                    default:break;
                }
                break;
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

MotorMessageHandler::MotorMessageHandler() : MessageHandler('m') {}
