#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include "Config.h"
#include "Actuator.h"
#include "GripUtil.h"

class MotorController {
 public:

    MotorController();
    MotorController(bool debug);

    void init(Actuator::Config configs[NUMBER_OF_ACTUATORS]);
    void setGrip(Grip grip);
    void open();
    void close();
    void brake();
    void coast();
    bool *checkCurrentLimiting();
    bool debug;

 private:

    Grip _currentGrip;
    Actuator _actuators[NUMBER_OF_ACTUATORS];
    bool checkCurrentLimiting(uint16_t actuatorIndex);
    bool checkCurrentLimiting(Actuator actuator);
    bool _currentLimitingValues[NUMBER_OF_ACTUATORS];
};

#endif // MotorController_h
