#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include "Config.h"
#include "Actuator.h"
#include <Servo.h>


struct Mapping {
  int input;
  int output;
};

class MotorController {
public:

  MotorController(struct Config *configs);
  void setHandPosition();

private:

  Actuator _actuators[NUMBER_OF_ACTUATORS];
};


#endif // ifndef MotorController_h
