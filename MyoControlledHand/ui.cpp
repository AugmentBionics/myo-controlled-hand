//UI
#include "Arduino.h"
#include "UIMessaging.h"
#include "Config.h"

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

    // Select primary grip if button 3 is HIGH
    if (button3 == HIGH) {
        state.showGrip(state.primaryIndex);
        lastChangeMillis = millis();
        state.selectGrip();
        messageHandler.sendCurrentGripSelection();
        return;
    }

    // Update UI Selection
    if (button1 == HIGH && button2 == HIGH) {
        // do nothing
    } else if (button1 == HIGH && state.getShownGripIndex() < NUMBER_OF_PRIMARY_GRIPS - 1) {
        state.showNextGrip();
        lastChangeMillis = millis();
    } else if (button2 == HIGH && state.getShownGripIndex() > 0) {
        state.showPreviousGrip();
        lastChangeMillis = millis();
    }

    // If enough time has passed then send grip selection to motor controller
    if (state.getSelectedGripIndex() != state.getShownGripIndex() && millis() - lastChangeMillis >= waitMillis) {
        state.selectGrip();
        messageHandler.sendCurrentGripSelection();
    }
}
