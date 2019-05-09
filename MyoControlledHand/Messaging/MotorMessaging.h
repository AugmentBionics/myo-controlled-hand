#ifndef MotorMessaging_h
#define MotorMessaging_h

#include "Arduino.h"
#include "Messaging.h"
#include "../Config/Config.h"
#include "../MotorController/MotorController.h"

typedef void (MotorController::*MotorControllerFuncPtr)(unsigned int);

class MotorState {
 public:
    void setGripPattern(const char pattern[]);
    void closeGrip();
    void openGrip();
    void brake();
    void idle();
 private:
    static char currentGripPattern[NUMBER_OF_ACTUATORS];
    static bool isClosed[NUMBER_OF_ACTUATORS];
    static bool isOpen[NUMBER_OF_ACTUATORS];
    static MotorController motorController;
    void forEachDynamicActuator(MotorControllerFuncPtr function);
};

/*!
 * @brief Handle structured serial communication between Arduinos
 */
class MotorMessageHandler : public MessageHandler {
 public:
    explicit MotorMessageHandler(MotorState *state);
 private:
    void interpretMessage(int length) final;
    MotorState *state;
};

#endif // MotorMessaging_h
