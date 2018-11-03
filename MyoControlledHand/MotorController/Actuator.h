#ifndef Actuator_h
#define Actuator_h

#include "Arduino.h"
#include "Config.h"
#include "GripUtil.h"
#include <Servo.h>

/* Actuator configuration information:

   controlCurve is a list of mappings from 0-1023 range to 0-1023 range to
   facilitate non-linear motion curve

   controlCurveResolution is the number of mappings in the curve

   lower and upper limits refer to a range to then map the 0-1023 range to
*/
struct Config {
    String name;
    int pin;
    Mapping *controlCurve;
    int controlCurveResolution;
    int lowerLimit;
    int upperLimit;
};

class Actuator {
 public:

    Actuator();
    Actuator(Config config);

    void init(Config config);
    void setPosition(int position);
    int getPosition();

    Config getConfig();

 private:

    Config _config;
    Servo _servo;
    int _currentPosition;
};

#endif // Actuator_h
