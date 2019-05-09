#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include "../Config/Config.h"
#include "../GripUtil/GripUtil.h"
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

    void setGrip(Grip grip);
    void open(unsigned int i);
    void close(unsigned int i);
    void brake(unsigned int i);
    void idle(unsigned int i);
    bool checkCurrentLimiting(unsigned int i);

 private:

    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

    void shiftOutWord(word w);

    Grip _currentGrip;
    bool _currentLimitingValues[NUMBER_OF_ACTUATORS];

    word regState = del;
    word outState = 0;
    const word motorMasks[NUMBER_OF_ACTUATORS] = {m0Mask, m1Mask, m2Mask, m3Mask};

};

#endif // MotorController_h
