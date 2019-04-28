#ifndef UIMessaging_h
#define UIMessaging_h

#include "Arduino.h"
#include "Messaging.h"

/*!
 * @brief Handle structured serial communication between Arduinos
 */

class UIMessageHandler : public MessageHandler {
 public:
    UIMessageHandler();
 private:
    void interpretMessage(int length) final;

};

#endif // UIMessaging_h
