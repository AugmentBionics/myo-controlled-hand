#ifndef Actuator_h
#define Actuator_h

#include "Arduino.h"
#include "Config.h"
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

  void          init(struct Config config);
  void          setPosition(int position);

  struct Config getConfig();

private:

  struct Config _config;
  Servo _servo;
};


#endif // ifndef Actuator_h
