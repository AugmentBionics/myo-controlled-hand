#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include "Config.h"
#include "Actuator.h"
#include "GripUtil.h"

class MotorController {
 public:

    // Constructor takes an array of Configs for the actuators
    MotorController();

    // Set hand position to the one defined in
    void setHandPosition(Grip grip);
    void handleDynamicActuation(int myoInput);
    void init(Config configs[NUMBER_OF_ACTUATORS], int lower, int upper);

 private:

    Grip _currentGrip;
    Actuator _actuators[NUMBER_OF_ACTUATORS];
    int _upperThreshold;
    int _lowerThreshold;

    void moveActuator(Actuator *actuator,
                      int position);
    int interpolateOnCurve(int input,
                           int rangeMin,
                           int rangeMax,
                           Mapping *curve,
                           int curveResolution,
                           int finalRangeMin,
                           int finalRangeMax);
    int remap(Actuator *actuator,
              int position);
};

#endif // MotorController_h
