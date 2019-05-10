#ifndef SensingMessaging_h
#define SensingMessaging_h

#include "Arduino.h"
#include "Messaging.h"

enum Mode {
    freemove,
    idle,
    locked
};

class SensingState {
    friend class MyoInput;
 public:
    void setMode(Mode mode);
 private:
    Mode mode = idle;
    float t1 = 375.0f;
    float t2 = 380.0f;
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
    void sendSelectPrimary();
 private:
    void interpretMessage(int length) final;
    SensingState *state;
};

#endif // SensingMessaging_h
