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

  // Constructor takes an array of struct Configs for the actuators
  MotorController(struct Config configs[NUMBER_OF_ACTUATORS]);

  // Set hand position to the one defined in
  void setHandPosition(struct Grip grip);
  void handleDynamicActuation(int myoInput);

private:

  struct Grip _currentGrip;
  Actuator    _actuators[NUMBER_OF_ACTUATORS];

  void moveActuator(Actuator *actuator,
                    int       position);
  int  remap(Actuator *actuator,
             int       position);
};


#endif // ifndef MotorController_h
