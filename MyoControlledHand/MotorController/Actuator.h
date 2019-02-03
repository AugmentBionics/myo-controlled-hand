#ifndef Actuator_h
#define Actuator_h

#include "Arduino.h"
#include "Config.h"

/* Actuator configuration information:

   controlCurve is a list of mappings from 0-1023 range to 0-1023 range to
   facilitate non-linear motion curve

   controlCurveResolution is the number of mappings in the curve

   lower and upper limits refer to a range to then map the 0-1023 range to
*/


class Actuator {
 public:
    struct Config {
        String name;
        uint8_t forwardPin;
        uint8_t reversePin;
        uint8_t curretPin;
    };

    enum State {
        unknown,
        forward,
        reverse,
        braking,
        coasting
    };

    Actuator();
    explicit Actuator(Config config);

    void drive(uint8_t, uint8_t);
    void runForward();
    void runReverse();
    void brake();
    void coast();
    bool isLimited();
    unsigned long getTimeState();
    String getName();

 private:

    Config _config;
    State _state = coasting;
    unsigned long _timeState = 0;
    unsigned long _timeOfLastUpdate;
    void updateTimeState();
};

#endif // Actuator_h
