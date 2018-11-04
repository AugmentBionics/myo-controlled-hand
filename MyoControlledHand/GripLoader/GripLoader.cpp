#include "Arduino.h"
#include "GripLoader.h"

GripLoader::GripLoader() {}

Grip GripLoader::load(String gripName)
{
  return
  {
    "Neutral",
    simple,
    {15, 15, 10},
    {0, 0, 1},
    40,
    continuous,
    {{NULL, 0, 0, false}, {NULL, 0, 0, false}, {NULL, 0, 0, false}}
  };
}
// struct Grip {
//   String                  name;
//   GripType                type;
//   int                     fingerPositions[NUMBER_OF_ACTUATORS];
//   int                     order[NUMBER_OF_ACTUATORS];
//   unsigned long           motionStepDelay;
//   FeedbackScheme          hapticFeedbackScheme[NUMBER_OF_TOUCH_SENSORS];
//   ActuationPattern actuationPattern[NUMBER_OF_ACTUATORS];
// };

// struct ActuationPattern {
//   Mapping *controlCurve;
//   int             controlCurveResolution;
//   int             actuationGoalPosition;
//   bool            isActuated;
// };
