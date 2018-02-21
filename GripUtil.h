#ifndef GripUtil_h
#define GripUtil_h

#include "Arduino.h"
#include "Config.h"

enum GripType { simple, dynamic, triggered };
enum FeedbackScheme { continuous, contact, none };

struct ActuationScheme {
  int actuationStartPosition[NUMBER_OF_ACTUATORS];
  int actuationGoalPosition[NUMBER_OF_ACTUATORS];
};

struct Grip {
  char                  *name;
  GripType               type;
  int                    fingerPositions[NUMBER_OF_ACTUATORS];
  int                    order[NUMBER_OF_ACTUATORS][NUMBER_OF_ACTUATORS];
  FeedbackScheme         hapticFeedbackScheme[NUMBER_OF_TOUCH_SENSORS];
  struct ActuationScheme dynamicActuationScheme;
};

#endif // ifndef GripUtil_h
