#ifndef MotorMessaging_h
#define MotorMessaging_h

#include "Arduino.h"
#include "Messaging.h"
#include "Config.h"
#include "MotorController.h"

typedef void (MotorController::*MotorControllerFuncPtr)(unsigned int);

class MotorState {
 public:
    void setGripPattern(const char pattern[]);
    void closeGrip();
    void openGrip();
    void brake();
    void idle();
    void init();
    void update();
 private:
    static char currentGripPattern[NUMBER_OF_ACTUATORS];
    static unsigned int rdCounters[NUMBER_OF_ACTUATORS];
    const unsigned int rdThreshold = RD_DELAY;
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
    char lastGripCommand = '\0';
    MotorState *state;
};

#endif // MotorMessaging_h
