#include "Arduino.h"
#include "MotorMessaging.h"

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
                char pattern[NUMBER_OF_ACTUATORS];
                Serial.print("Set grip: ");
                for (int i = 2; i <= NUMBER_OF_ACTUATORS + 2; ++i) {
                    char c = messageBuffer[i];
                    switch (c) {
                        case 'o': // opened
                            pattern[i - 2] = c;
                            break;
                        case 'c': // closed
                            pattern[i - 2] = c;
                            break;
                        case 'd': // dynamic
                            pattern[i - 2] = c;
                            break;
                        default: // ignore other characters
                            break;
                    }
                }
                state->setGripPattern(pattern);
                break;
            }

            case 'm': // move
            {
                Serial.print("Move: ");
                switch (messageBuffer[2]) {
                    case 'o': // open
                        Serial.println("open");
                        state->openGrip();
                        break;
                    case 'c': // close
                        Serial.println("close");
                        state->closeGrip();
                        break;
                    case 'i': // idle
                        Serial.println("idle");
                        state->idle();
                        break;
                    case 'b': // brake
                        Serial.println("brake");
                        state->brake();
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
