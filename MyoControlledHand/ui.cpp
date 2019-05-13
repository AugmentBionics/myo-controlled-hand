//UI
#include "Arduino.h"
#include "UIMessaging.h"

#define BUTTON1_PIN 3
#define BUTTON2_PIN 4
#define BUTTON3_PIN 5

UIState state;
UIMessageHandler messageHandler(&state);

void setup() {
    Serial.begin(9600);
    Serial.println(F("UI Arduino starting..."));

    // Motor
    pinMode(10, OUTPUT);

    pinMode(BUTTON1_PIN, INPUT);
    pinMode(BUTTON2_PIN, INPUT);
    pinMode(BUTTON3_PIN, INPUT);

    state.setupScreen();
    state.showGrip(0);
}

unsigned long lastChangeMillis = 0;
unsigned long waitMillis = 1400;

void loop() {
    // Handle serial instructions
    messageHandler.handleSerial();

    // Read from buttons
    int button1 = digitalRead(BUTTON1_PIN);
    int button2 = digitalRead(BUTTON2_PIN);
    int button3 = digitalRead(BUTTON3_PIN);

    // Select primary grip if button 3 is LOW
    if (button3 == LOW) {
        state.showGrip(state.primaryIndex);
        lastChangeMillis = millis();
        state.selectGrip();
        messageHandler.sendCurrentGripSelection();
        return;
    }

    // Update UI Selection
    if (button1 == LOW && button2 == LOW) {
        // Update primary
        state.primaryIndex = state.getShownGripIndex();
        state.showGrip(state.primaryIndex); //update 'P' symbol
        lastChangeMillis = millis();
    } else if (button1 == LOW && state.getShownGripIndex() < NUMBER_OF_PRIMARY_GRIPS - 1) {
        state.showNextGrip();
        lastChangeMillis = millis();
    } else if (button2 == LOW && state.getShownGripIndex() > 0) {
        state.showPreviousGrip();
        lastChangeMillis = millis();
    }

    // If enough time has passed then send grip selection to motor controller
    if (state.getSelectedGripIndex() != state.getShownGripIndex() && millis() - lastChangeMillis >= waitMillis) {
        state.selectGrip();
        messageHandler.sendCurrentGripSelection();
    }
}
