//SENSING
#include "MyoInput.h"
#include "MyoDemo.h"

void setup() {
    Serial.begin(9600);
    Serial.println("Sensing Arduino starting...");
}

SensingState state;
SensingMessageHandler messageHandler(&state);
MyoInput input(&state);
MyoInput::Action lastAction = MyoInput::none;
MyoDemo d;

void loop() {
    messageHandler.handleSerial();

    if (input.primaryGripTriggered()) {
        messageHandler.sendSelectPrimary();
    }

    MyoInput::Action action = MyoInput::none;
    switch (state.getMode()) {
        case Mode::freemove: // handle real myo input
            action = input.readAction();
            break;
        case Mode::demo: // fake myo input
            action = d.getNextDemoAction();
            break;
        default:break;
    }

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