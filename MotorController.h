#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include "Config.h"
#include "Actuator.h"
#include "GripUtil.h"


struct Mapping {
  int input;
  int output;
};

class MotorController {
public:

  MotorController(struct Config *configs);
  void setHandPosition(struct Grip grip);

private:

  Actuator _actuators[NUMBER_OF_ACTUATORS];

  void moveActuator(Actuator     *actuator,
                    int           position);
  int  remap(Actuator *actuator,
             int       position);
};


#endif // ifndef MotorController_h
