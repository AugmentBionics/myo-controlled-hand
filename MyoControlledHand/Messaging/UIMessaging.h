#ifndef UIMessaging_h
#define UIMessaging_h

#include "Arduino.h"
#include "Messaging.h"

class UIState {
 public:
    void selectGrip(unsigned int) {

    }
    unsigned int getSelectedGripIndex() {
        return gripIndexSelected;
    }
 private:
    unsigned int gripIndexSelected;
};

/*!
 * @brief Handle structured serial communication between Arduinos
 */
class UIMessageHandler : public MessageHandler {
 public:
    explicit UIMessageHandler(UIState *state);
    void sendCurrentGripSelection();
    void sedCurrentGripDefinition();
 private:
    void interpretMessage(int length) final;
    UIState *state;
};

#endif // UIMessaging_h
