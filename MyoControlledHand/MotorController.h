#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include "Config.h"
#include <Adafruit_PWMServoDriver.h>


/*!
 * Class that controls a number of Actuators.
 */

#define del     0b0000100100100100
#define mOpen   0b0000001001001001
#define mClose  0b0000010010010010
#define mBrake   0b0000011011011011

#define m0Mask  0b0000000000000111
#define m1Mask  0b0000000000111000
#define m2Mask  0b0000000111000000
#define m3Mask  0b0000111000000000

#define NC      0b1111000000000000

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

    const unsigned int forwardPins[NUMBER_OF_ACTUATORS] = {M0_FWD, M1_FWD, M2_FWD, M3_FWD};
    const unsigned int reversePins[NUMBER_OF_ACTUATORS] = {M0_REV, M1_REV, M2_REV, M3_REV};
    const unsigned int delPins[NUMBER_OF_ACTUATORS] = {M0_DEL, M1_DEL, M2_DEL, M3_DEL};
    const unsigned int
        limPins[NUMBER_OF_ACTUATORS] = {CURRENT_LIMITER_M0, CURRENT_LIMITER_M1, CURRENT_LIMITER_M2, CURRENT_LIMITER_M3};
    const unsigned int rdPins[NUMBER_OF_ACTUATORS] = {M0_RD, M1_RD, M2_RD, M3_RD};

    void setCurrentLimit(unsigned int i, unsigned int limit);
};

#endif // MotorController_h
