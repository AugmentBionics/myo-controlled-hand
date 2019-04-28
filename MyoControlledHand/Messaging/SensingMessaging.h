#ifndef SensingMessaging_h
#define SensingMessaging_h

#include "Arduino.h"
#include "Messaging.h"

/*!
 * @brief Handle structured serial communication between Arduinos
 */

class SensingMessageHandler : public MessageHandler {
 public:
    SensingMessageHandler();
 private:
    void interpretMessage(int length) final;

};

#endif // SensingMessaging_h
