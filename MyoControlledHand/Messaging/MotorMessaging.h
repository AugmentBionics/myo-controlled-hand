#ifndef MotorMessaging_h
#define MotorMessaging_h

#include "Arduino.h"
#include "Messaging.h"

/*!
 * @brief Handle structured serial communication between Arduinos
 */

class MotorMessageHandler : public MessageHandler {
 public:
    MotorMessageHandler();
 private:
    void interpretMessage(int length) final;

};

#endif // MotorMessaging_h
