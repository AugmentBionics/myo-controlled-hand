#include "MyoInput.h"
#include "MyoDemo.h"

MyoInput::Action MyoDemo::getNextDemoAction() {
    static unsigned long lastInstructionChange = 0;
    static unsigned int i = 0;
    if (millis() - lastInstructionChange >= waitTime) {
        i = (i + 1) % 4;
        lastInstructionChange = millis();
    }
    return actionLoop[i];
}