#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include "Config.h"
#include <Adafruit_PWMServoDriver.h>

enum MotorInstruction {
    none,
    open,
    close,
    brake,
    idle
};

class MotorController {
 public:
    explicit MotorController();

    void init();

    void open(unsigned int i);
    void close(unsigned int i);
    void brake(unsigned int i, bool doNotLog);
    void idle(unsigned int i, bool doNotLog);
    void brake(unsigned int i);
    void idle(unsigned int i);
    bool checkCurrentLimiting(unsigned int i);

    static MotorInstruction lastInstruction[NUMBER_OF_ACTUATORS];
    static bool isClosed[NUMBER_OF_ACTUATORS];
    static bool isOpen[NUMBER_OF_ACTUATORS];

 private:

    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
    bool _currentLimitingValues[NUMBER_OF_ACTUATORS];

    const unsigned int
        forwardPins[NUMBER_OF_ACTUATORS] = {M0_FWD, M1_FWD, M2_FWD, M3_FWD};
    const unsigned int
        reversePins[NUMBER_OF_ACTUATORS] = {M0_REV, M1_REV, M2_REV, M3_REV};
    const unsigned int
        delPins[NUMBER_OF_ACTUATORS] = {M0_DEL, M1_DEL, M2_DEL, M3_DEL};
    const unsigned int
        limPins[NUMBER_OF_ACTUATORS] = {CURRENT_LIMITER_M0, CURRENT_LIMITER_M1, CURRENT_LIMITER_M2, CURRENT_LIMITER_M3};
    const unsigned int
        rdPins[NUMBER_OF_ACTUATORS] = {M0_RD, M1_RD, M2_RD, M3_RD};
    const unsigned int
        motorCloseSpeed[NUMBER_OF_ACTUATORS] = {SPEED_CLOSE_M0, SPEED_CLOSE_M1, SPEED_CLOSE_M2, SPEED_CLOSE_M3};
    const unsigned int
        motorOpenSpeed[NUMBER_OF_ACTUATORS] = {SPEED_OPEN_M0, SPEED_OPEN_M1, SPEED_OPEN_M2, SPEED_OPEN_M3};
    const unsigned int
        initCurrentLimits[NUMBER_OF_ACTUATORS] =
        {INIT_CURRENT_LIM_M0, INIT_CURRENT_LIM_M1, INIT_CURRENT_LIM_M2, INIT_CURRENT_LIM_M3};
    const unsigned int
        openCurrentLimits[NUMBER_OF_ACTUATORS] =
        {OPEN_CURRENT_LIM_M0, OPEN_CURRENT_LIM_M1, OPEN_CURRENT_LIM_M2, OPEN_CURRENT_LIM_M3};
    const unsigned int
        closeCurrentLimits[NUMBER_OF_ACTUATORS] =
        {CLOSE_CURRENT_LIM_M0, CLOSE_CURRENT_LIM_M1, CLOSE_CURRENT_LIM_M2, CLOSE_CURRENT_LIM_M3};

    void setCurrentLimit(unsigned int i, unsigned int limit);

    void setDelPin(unsigned int i, unsigned int value);
};

#endif // MotorController_h
