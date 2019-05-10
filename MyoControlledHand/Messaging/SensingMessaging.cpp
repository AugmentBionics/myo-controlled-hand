#include "Arduino.h"
#include "SensingMessaging.h"

void SensingMessageHandler::interpretMessage(int length) {
    if (length <= 2) return;

    if (messageBuffer[0] == address) {
        // Message is for myo -> interpret

        Serial.print("Message: ");
        for (int i = 0; i < length; ++i)
            Serial.write(messageBuffer[i]);
        Serial.print('\n');

        Serial.print("=> ");

        switch (messageBuffer[1]) {

            case 'm': // mode switch

                switch (messageBuffer[2]) {
                    case '1': // mode 1: freemove
                        Serial.println("mode 1: freemove");
                        state->setMode(freemove);
                        break;
                    case '2': // mode 2: locked
                        Serial.println("mode 2: locked");
                        state->setMode(locked);
                        break;
                    case '3': // mode 3: idle
                        Serial.println("mode 3: idle");
                        state->setMode(idle);
                        break;
                    default:break;
                }
                break;

            case 't': // threshold update
            {
                int myoToEdit = 1;
                String str(messageBuffer);
                int newl = -1;
                int newu = -1;
                int lx = str.indexOf('l');
                int ux = str.indexOf('u');
                if (lx >= 0 && ux > lx) {
                    newl = (int)str.substring(lx + 1, ux).toInt();
                    newu = (int)str.substring(ux + 1).toInt();
                }
                Serial.print("Set Thresh.: ");
                switch (messageBuffer[2]) {
                    case '1': // myo 1
                        Serial.print("myo1: ");
                        myoToEdit = 1;
                        break;
                    case '2': // myo 2
                        Serial.print("myo2: ");
                        myoToEdit = 2;
                        break;
                    default:break;
                }
                Serial.print("lower=");
                Serial.print(newl);
                Serial.print("upper=");
                Serial.println(newu);

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

SensingMessageHandler::SensingMessageHandler(SensingState *state) : MessageHandler('m'), state(state) {}

void SensingMessageHandler::sendGripOpen() {
    sendMessage('m', "mo");
}

void SensingMessageHandler::sendGripClose() {
    sendMessage('m', "mc");
}

void SensingMessageHandler::sendGripIdle() {
    sendMessage('m', "mi");
}

void SensingMessageHandler::sendGripBrake() {
    sendMessage('m', "mb");
}

void SensingMessageHandler::sendSelectPrimary() {
    sendMessage('u', "s1");
}

void SensingState::setMode(Mode mode) {
    this->mode = mode;
}
