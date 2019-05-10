//UI
#include "Arduino.h"
#include "UIMessaging.h"
#include "Config.h"

#define BUTTON1_PIN 3
#define BUTTON2_PIN 4
#define BUTTON3_PIN 5
#define GRIP_PATTERN_COUNT 5

void sendOpenMessage() {

}

void sendCloseMessage() {

}

void sendBrakeMessage() {

}

void sendIdleMessage() {

}

void sendNextGripPattern() {
    static unsigned int i = 0;
    Serial.write('@'); // Instruction code
    Serial.write('m'); // Address 'm' for motor controller
    Serial.write('p'); // 'p' for grip pattern update
    for (int j = 0; j < NUMBER_OF_ACTUATORS; ++j)
        Serial.write(gripPatterns[i][j]);
    Serial.write('\n');
    i = (i + 1) % GRIP_PATTERN_COUNT;
}

void setup() {
    Serial.begin(9600);
    Serial.println(F("Motor testing Arduino starting..."));

    pinMode(BUTTON1_PIN, INPUT);
    pinMode(BUTTON2_PIN, INPUT);
    pinMode(BUTTON3_PIN, INPUT);

    sendNextGripPattern();
}

const char gripPatterns[GRIP_PATTERN_COUNT][NUMBER_OF_ACTUATORS] = {
    {'d', 'i', 'i', 'i'},
    {'i', 'd', 'i', 'i'},
    {'i', 'i', 'd', 'i'},
    {'i', 'i', 'i', 'd'},
    {'d', 'd', 'd', 'd'}
};

void loop() {

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

    if (button1 == LOW && button2 == LOW) {
        // Switch grip
        sendNextGripPattern();
    } else if (button1 == LOW) {
        sendOpenMessage();
    } else if (button2 == LOW) {
        sendCloseMessage();
    }

    if (button3 == LOW) {
        sendBrakeMessage();
    }

}