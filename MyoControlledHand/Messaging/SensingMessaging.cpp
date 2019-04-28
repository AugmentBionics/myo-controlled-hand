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
                    case '1': // mode 1: free move
                        Serial.println("mode 1: free move");
                        break;
                    case '2': // mode 2: lock
                        Serial.println("mode 2: lock");
                        break;
                    default:break;
                }
                break;

            case 't': // threshold update
            {
                int myoToEdit = 1;
                String str(messageBuffer);
                int newl;
                int newu;
                int lx = str.indexOf('l');
                int ux = str.indexOf('u');
                if (lx >= 0 && ux > lx) {
                    newl = str.substring(lx + 1, ux).toInt();
                    newu = str.substring(ux + 1).toInt();
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

SensingMessageHandler::SensingMessageHandler() : MessageHandler('m') {}
