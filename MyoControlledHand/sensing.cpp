//SENSING
#include <MyoInput.h>
#include "Arduino.h"
#include "SensingMessaging.h"

void setup() {
    Serial.begin(9600);
    Serial.println("Sensing Arduino starting...");
}

SensingState state;
SensingMessageHandler messageHandler(&state);
MyoInput input(&state);
MyoInput::Action lastAction = MyoInput::none;

void loop() {
    messageHandler.handleSerial();

    if (input.primaryGripTriggered()) {
        messageHandler.sendSelectPrimary();
    }

    MyoInput::Action action = input.readAction();

    // ~~~ Testing
    //action = MyoInput::none;
    // ~~~

    if (lastAction != action) {
        switch (action) {
            case MyoInput::open: // Open grip
                messageHandler.sendGripOpen();
                break;
            case MyoInput::close: // Close grip
                messageHandler.sendGripClose();
                break;
            default:  // No instruction
                messageHandler.sendGripIdle();
                break;
        }
        lastAction = action;
    }
}