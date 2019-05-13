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

volatile int lastButton1State;
volatile int lastButton2State;
volatile int lastButton3State;
volatile int lastButton4State;

void loop() {
    // Handle serial instructions
    messageHandler.handleSerial();

    const unsigned long t = millis();

    // Read from buttons
    int button1State = digitalRead(BUTTON1_PIN);
    int button2State = digitalRead(BUTTON2_PIN);
    int button3State = digitalRead(BUTTON3_PIN);
    int button4State = digitalRead(BUTTON4_PIN);

    bool button1Up = button1State == HIGH && lastButton1State == LOW;
    bool button2Up = button2State == HIGH && lastButton2State == LOW;
    bool button3Up = button3State == HIGH && lastButton3State == LOW;
    bool button3Down = button3State == LOW && lastButton3State == HIGH;
    bool button4Up = button4State == HIGH && lastButton4State == LOW;
    bool button4Down = button4State == LOW && lastButton4State == HIGH;

    if (button3Down)
        button3PressStart = t;
    if (button4Down)
        button4PressStart = t;

    if (button3Up || button4Up) {
        if (button3Up) {
            if (t - button3PressStart > longPress) {
                if (state.getShownGripIndex() == state.secondaryIndex)
                    state.secondaryIndex = state.primaryIndex;
                state.primaryIndex = state.getShownGripIndex();
                state.showGrip(state.primaryIndex); //update 'P' symbol
            } else {
                state.showGrip(state.primaryIndex);
            }
        }
        if (button4Up) {
            if (t - button4PressStart > longPress) {
                if (state.getShownGripIndex() == state.primaryIndex)
                    state.primaryIndex = state.secondaryIndex;
                state.secondaryIndex = state.getShownGripIndex();
                state.showGrip(state.secondaryIndex); //update 'S' symbol
            } else {
                state.showGrip(state.secondaryIndex);
            }
        }
        lastChangeMillis = t;
    } else {
        // Update UI Selection
        if (button1Up && button2Up) {
            // do nothing
        } else if (button1Up && state.getShownGripIndex() < NUMBER_OF_PRIMARY_GRIPS - 1) {
            state.showNextGrip();
            lastChangeMillis = t;
        } else if (button2Up == LOW && state.getShownGripIndex() > 0) {
            state.showPreviousGrip();
            lastChangeMillis = t;
        }
    }

    // If enough time has passed then send grip selection to motor controller
    if (state.getSelectedGripIndex() != state.getShownGripIndex() && t - lastChangeMillis >= waitMillis) {
        state.selectGrip();
        messageHandler.sendCurrentGripSelection();
    }

    lastButton1State = button1State;
    lastButton2State = button2State;
    lastButton3State = button3State;
}
