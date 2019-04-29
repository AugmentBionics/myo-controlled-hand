#ifndef Messaging_h
#define Messaging_h

#include "Arduino.h"

/*!
 * @brief Handle structured serial communication between Arduinos
 */
class MessageHandler {
 public:
    void handleSerial();
 protected:
    explicit MessageHandler(char address) : address(address) {}
    virtual void interpretMessage(int length) = 0;
    void sendMessage(char targetAddress, const String &message) const;
    void clearMessageBuffer();
    char messageBuffer[16]{};
    unsigned int cursor = 0;
    bool newMessage = false;
    bool messageBufferFilling = false;
    int messageLength = 0;
    char address;
};

#endif // Messaging_h
