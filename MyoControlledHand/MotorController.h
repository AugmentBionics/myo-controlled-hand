#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include "Config.h"
#include "GripUtil.h"
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

class MotorController {
 public:
    explicit MotorController();

    void init();

    void setGrip(Grip grip);
    void open(unsigned int i);
    void close(unsigned int i);
    void brake(unsigned int i);
    void idle(unsigned int i);
    bool checkCurrentLimiting(unsigned int i);

 private:

    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
    Grip _currentGrip;
    bool _currentLimitingValues[NUMBER_OF_ACTUATORS];

    word regState = del;
    word outState = 0;
    const word motorMasks[NUMBER_OF_ACTUATORS] = {m0Mask, m1Mask, m2Mask, m3Mask};

    const unsigned int forwardPins[NUMBER_OF_ACTUATORS] = {M0_FWD, M1_FWD, M2_FWD, M3_FWD};
    const unsigned int reversePins[NUMBER_OF_ACTUATORS] = {M0_REV, M1_REV, M2_REV, M3_REV};
    const unsigned int delPins[NUMBER_OF_ACTUATORS] = {M0_DEL, M1_DEL, M2_DEL, M3_DEL};
    const unsigned int
        limPins[NUMBER_OF_ACTUATORS] = {CURRENT_LIMITER_M0, CURRENT_LIMITER_M1, CURRENT_LIMITER_M2, CURRENT_LIMITER_M3};

    void setCurrentLimit(unsigned int i, unsigned int limit);
};

#endif // MotorController_h
