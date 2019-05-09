#include "Arduino.h"
#include "UIMessaging.h"
#include "Grips.h"

void UIMessageHandler::interpretMessage(int length) {
    if (length <= 2) return;

    if (messageBuffer[0] == address) {
        // Message is for UI arduino -> interpret

        Serial.print(F("Message: "));
        for (int i = 0; i < length; ++i)
            Serial.write(messageBuffer[i]);
        Serial.print('\n');

        Serial.print("=> ");

        switch (messageBuffer[1]) {

            case 's': // select grip
            {
                int gIndex = int(messageBuffer[2] - '0');
                if (gIndex <= 1) {
                    // primary grip
                    Serial.println(F("Primary grip..."));
                    break;
                } else {
                    // secondary grip
                    Serial.println(F("Secondary grip..."));
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

UIMessageHandler::UIMessageHandler(UIState *state) : MessageHandler('u'), state(state) {}

void UIMessageHandler::sendCurrentGripSelection() {
    unsigned int index = state->getSelectedGripIndex();
    sendMessage('@', "");

}
