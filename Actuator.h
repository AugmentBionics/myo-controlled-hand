#ifndef Actuator_h
#define Actuator_h

#include "Arduino.h"
#include "Config.h"
#include "MotorController.h"
#include <Servo.h>

struct Config {
  String          name;
  int             pin;
  struct Mapping *controlCurve;
  int             controlCurveResolution;
  int             lowerLimit;
  int             upperLimit;
};

class Actuator {
public:

  Actuator();
  Actuator(struct Config config);

  void init();

private:

  Config   _config;
  Servo    _servo;
  struct Mapping *_controlCurve;
  int _controlCurveResolution;
};


#endif // ifndef Actuator_h
