#ifndef Actuator_h
#define Actuator_h

#include "Arduino.h"
#include "Config.h"
#include <Servo.h>

/* Actuator configuration information:
 *
 * controlCurve is a list of mappings from 0-1023 range to 0-1023 range to
 * facilitate non-linear motion curve
 *
 * controlCurveResolution is the number of mappings in the curve
 *
 * lower and upper limits refer to a range to then map the 0-1023 range to
 */
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
