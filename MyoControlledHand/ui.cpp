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

    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);
    pinMode(BUTTON3_PIN, INPUT_PULLUP);

    state.setupScreen();
    state.showGrip(0);
}

unsigned long lastChangeMillis = 0;
unsigned long button3PressStart = 0;
const unsigned long longPress = 1000;
const unsigned long waitMillis = 1400;

volatile int lastButton1State;
volatile int lastButton2State;
volatile int lastButton3State;

void loop() {
    // Handle serial instructions
    messageHandler.handleSerial();

    const unsigned long t = millis();

    // Read from buttons
    int button1State = digitalRead(BUTTON1_PIN);
    int button2State = digitalRead(BUTTON2_PIN);
    int button3State = digitalRead(BUTTON3_PIN);

    bool button1Up = button1State == HIGH && lastButton1State == LOW;
    bool button2Up = button2State == HIGH && lastButton2State == LOW;
    bool button3Up = button3State == HIGH && lastButton3State == LOW;
    bool button3Down = button3State == LOW && lastButton3State == HIGH;

    if (button3Down)
        button3PressStart = t;


    // Select primary grip if button 3 is LOW
    if (button3Up) {
        if (t - button3PressStart > longPress) {
            state.primaryIndex = state.getShownGripIndex();
            state.showGrip(state.primaryIndex); //update 'P' symbol
            lastChangeMillis = t;
        } else {
            state.showGrip(state.primaryIndex);
            lastChangeMillis = t;
        }
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
    if (state.getSelectedGripIndex() != state.getShownGripIndex() && millis() - lastChangeMillis >= waitMillis) {
        state.selectGrip();
        messageHandler.sendCurrentGripSelection();
    }

    lastButton1State = button1State;
    lastButton2State = button2State;
    lastButton3State = button3State;
}
