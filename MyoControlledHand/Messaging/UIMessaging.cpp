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
                    state->showGrip(state->primaryIndex);
                    state->selectGrip();
                    sendCurrentGripSelection();
                    break;
                } else {
                    // other grip
                    Serial.println(F("Other grip..."));
                    // not implemented
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
    char serializedGrip[NUMBER_OF_ACTUATORS + 1];
    serializeGrip(grips[index], serializedGrip);
    sendMessage('m', serializedGrip);
}

void UIMessageHandler::serializeGrip(const Grip &grip, char *out) {
    char c;
    out[0] = 'p'; // p for pattern
    for (unsigned int i = 1; i <= NUMBER_OF_ACTUATORS; ++i) {
        switch (grip.actuationPattern[i]) {
            case close:c = 'c';
                break;
            case actuate:c = 'd';
                break;
            default:c = 'o';
                break;
        }
        out[i] = c;
    }
}

void UIState::setupScreen() {
    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

    display.setTextColor(WHITE);
    display.clearDisplay();

#if (SPLASH_ENABLED == true)
    // splash
    display.drawBitmap(34, 0, logo16_glcd_bmp, 72, 64, 1);
    display.display();
    delay(1000);
    display.clearDisplay();
#endif
}

void UIState::selectGrip(unsigned int selection) {
    playLockAnimation();
    selectedGripIndex = selection;
}

void UIState::selectGrip() {
    selectGrip(shownGripIndex);
}

void UIState::showGrip(unsigned int gripIndex) {
    display.clearDisplay();

    digitalWrite(10, HIGH); // Motor on

    display.setTextColor(WHITE);

    if (gripIndex > 0) {
        //Display previous grip name at top
        display.setTextSize(1);
        display.setCursor(offsetX, 0);
        display.print('\x10');
        display.println(gripNames[gripIndex - 1]);
    }

    //Display current grip name in middle
    display.setTextSize(2);
    display.setCursor(offsetX + 0, offsetY + 5);
    display.print('\x10');
    display.print(gripNames[gripIndex]);

    //Display grip index + 1 also
    display.setCursor(1, offsetY + 5);
    display.print(gripIndex + 1);

    if (gripIndex < NUMBER_OF_PRIMARY_GRIPS - 1) {
        //Display next grip name at bottom
        display.setTextSize(1);
        display.setCursor(offsetX, 55);
        display.print('\x10');
        display.println(gripNames[gripIndex + 1]);
    }

    if (gripIndex == primaryIndex) {
        //Display P indicator for primary grip
        display.setTextSize(1);
        display.setCursor(offsetX + 100, 0);
        display.println(F("P"));
    } else if (gripIndex == secondaryIndex) {
        //Display S indicator for secondary grip
        display.setTextSize(1);
        display.setCursor(offsetX + 100, 0);
        display.println(F("S"));
    }

    display.display();

    //  delay(20);
    digitalWrite(10, LOW); // Motor off
}

void UIState::showNextGrip() {
    showGrip(++shownGripIndex);
}

void UIState::showPreviousGrip() {
    showGrip(--shownGripIndex);
}

void UIState::flash(unsigned int t) {
    digitalWrite(10, HIGH); // Motor on
    display.invertDisplay(1);
    delay(t);
    display.invertDisplay(0);
    digitalWrite(10, LOW); // Motor off
}

void UIState::playLockAnimation() {
    flash(100);
    delay(45);
    flash(300);
}

Adafruit_SSD1306 UIState::display = Adafruit_SSD1306(OLED_RESET);
