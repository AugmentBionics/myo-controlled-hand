//UI
#include "Arduino.h"
#include "UIMessaging.h"

#define BUTTON1_PIN 3
#define BUTTON2_PIN 4
#define BUTTON3_PIN 5
#define BUTTON4_PIN 6

UIState state;
UIMessageHandler messageHandler(&state);

void setup() {
    Serial.begin(9600);
    Serial.println(F("UI Arduino starting..."));

    // Motor
    pinMode(10, OUTPUT);

    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);
    pinMode(BUTTON3_PIN, INPUT_PULLUP);
    pinMode(BUTTON4_PIN, INPUT_PULLUP);

    state.setupScreen();
    state.showGrip(0);
}

unsigned long lastChangeMillis = 0;
unsigned long button3PressStart = 0;
unsigned long button4PressStart = 0;

const unsigned long longPress = 1000;
const unsigned long waitMillis = 1400;

int lastButtonStates[4] = {HIGH, HIGH, HIGH, HIGH};

unsigned long lastDebounceTimes[4] = {};
unsigned long debounceDelay = 50;
bool isDebounced[4];
bool buttonsUp[4];
bool buttonsDown[4];

void loop() {
    // Handle serial instructions
    messageHandler.handleSerial();

    const unsigned long t = millis();

    // Read from buttons
    int buttonStates[4] =
        {digitalRead(BUTTON1_PIN), digitalRead(BUTTON2_PIN), digitalRead(BUTTON3_PIN), digitalRead(BUTTON4_PIN)};

    for (int i = 0; i < 4; ++i) {
        if (buttonStates[i] != lastButtonStates[i]) {
            // reset the debouncing timer
            lastDebounceTimes[i] = t;
        }
    }

    for (int i = 0; i < 4; ++i) {
        isDebounced[i] = (t - lastDebounceTimes[i]) > debounceDelay;
        if (isDebounced[i]) {
            buttonsUp[i] = buttonStates[i] == HIGH && lastButtonStates[i] == LOW;
            buttonsDown[i] = buttonStates[i] == LOW && lastButtonStates[i] == HIGH;
        }
    }

    if (buttonsDown[2])
        button3PressStart = t;
    if (buttonsDown[3])
        button4PressStart = t;

    if (buttonsUp[2]) {
        if (t - button3PressStart > longPress) {
            if (state.getShownGripIndex() == state.secondaryIndex)
                state.secondaryIndex = state.primaryIndex;
            state.primaryIndex = state.getShownGripIndex();
        }
        state.showGrip(state.primaryIndex);
        lastChangeMillis = t;
    } else if (buttonsUp[3]) {
        if (t - button4PressStart > longPress) {
            if (state.getShownGripIndex() == state.primaryIndex)
                state.primaryIndex = state.secondaryIndex;
            state.secondaryIndex = state.getShownGripIndex();
        }
        state.showGrip(state.secondaryIndex);
        lastChangeMillis = t;

    } else {
        // Update UI Selection
        if (buttonsUp[0] && buttonsUp[1]) {
            // do nothing
        } else if (buttonsUp[0] && state.getShownGripIndex() < NUMBER_OF_PRIMARY_GRIPS - 1) {
            state.showNextGrip();
            lastChangeMillis = t;
        } else if (buttonsUp[2] && state.getShownGripIndex() > 0) {
            state.showPreviousGrip();
            lastChangeMillis = t;
        }
    }

    // If enough time has passed then send grip selection to motor controller
    if (state.getSelectedGripIndex() != state.getShownGripIndex() && t - lastChangeMillis >= waitMillis) {
        state.selectGrip();
        messageHandler.sendCurrentGripSelection();
    }

    for (int i = 0; i < 4; ++i)
        lastButtonStates[i] = buttonStates[i];
}
