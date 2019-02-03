#ifndef GripUtil_h
#define GripUtil_h

#include "Arduino.h"
#include "Config.h"

enum GripType {
    simple,
    triggered
};

enum ActuationScheme {
    actuate,
    open,
    close
};

struct Grip {
    String name;
    GripType type;
    uint8_t startPercent[NUMBER_OF_ACTUATORS];
    uint8_t finishPercent[NUMBER_OF_ACTUATORS];
    ActuationScheme actuationPattern[NUMBER_OF_ACTUATORS];
};

#endif // GripUtil_h
