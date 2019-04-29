#ifndef SensingMessaging_h
#define SensingMessaging_h

#include "Arduino.h"
#include "Messaging.h"
#include "../MyoInput/MyoInput.h"

enum Mode {
    freemove,
    idle,
    locked
};

class SensingState {
 public:
    void setMode(Mode mode);
 private:
    Mode mode;
};

/*!
 * @brief Handle structured serial communication between Arduinos
 */
class SensingMessageHandler : public MessageHandler {
 public:
    explicit SensingMessageHandler(SensingState *state);
    void sendGripOpen();
    void sendGripClose();
    void sendGripIdle();
    void sendGripBrake();
    void sendGripSelection(GripSelection selection);
 private:
    void interpretMessage(int length) final;
    SensingState *state;
};

#endif // SensingMessaging_h
