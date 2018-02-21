#ifndef GripUtil_h
#define GripUtil_h

#include "Arduino.h"
#include "Config.h"

enum GripType { simple, dynamic, triggered };
enum FeedbackScheme { continuous, contact, none };

struct Grip {
  String         name;
  GripType       type;
  int            fingerPositions[NUMBER_OF_ACTUATORS];
  int            order[NUMBER_OF_ACTUATORS];
  unsigned long  motionStepDelay;
  FeedbackScheme hapticFeedbackScheme[NUMBER_OF_TOUCH_SENSORS];
  int            actuationGoalPosition[NUMBER_OF_ACTUATORS];
};

#endif // ifndef GripUtil_h
