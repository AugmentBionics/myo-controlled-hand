//SENSING
#include "Arduino.h"
#include "SensingMessaging.h"

void setup() {
    Serial.begin(9600);
    Serial.println("Sensing Arduino starting...");
}

SensingState state;
SensingMessageHandler messageHandler(&state);
MyoInput input;
MyoInput::Action lastAction = MyoInput::none;

void loop() {
    messageHandler.handleSerial();

    if (input.gripNeedsUpdating()) {
        messageHandler.sendGripSelection(input.lastSelectedGrip());
    }

    MyoInput::Action action = input.readAction();

    // ~~~ Testing
    action = MyoInput::none;
    // ~~~

    if (lastAction != action) {
        switch (action) {
            case MyoInput::open:messageHandler.sendGripOpen();
                break;
            case MyoInput::close:messageHandler.sendGripClose();
                break;
            default:messageHandler.sendGripIdle();
                break;
        }
        lastAction = action;
    }
}