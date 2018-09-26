#include <Servo.h>
#include "Config.h"
#include "MotorController.h"
#include "GripLoader.h"
#include "GripUtil.h"

Mapping linearMapping[2] = {
  {0, 0},
  {0, 1024}
};

Config actuatorConfigs[NUMBER_OF_ACTUATORS] = {
  { "thumb",
    MOTOR_1_PIN,
    linearMapping,
    2,
    1711,
    1100
  },
  { "indexFinger",
    MOTOR_2_PIN,
    linearMapping,
    2,
    1720,
    1200
  },
  { "otherFingers",
    MOTOR_3_PIN,
    linearMapping,
    2,
    1695,
    1240
  },
};
// struct Config {
//   String          name;
//   int             pin;
//   Mapping *controlCurve;
//   int             controlCurveResolution;
//   int             lowerLimit;
//   int             upperLimit;
// };

volatile unsigned int gripIndex = 0;
unsigned int currentGripIndex = NUMBER_OF_PRIMARY_GRIPS; // Nonsensical value to trigger first update.

MotorController mc;

Grip openGrip = {
  "Open",
  simple,
  {0, 0, 0},
  {0, 0, 0},
  200UL,
  {none},
  {
    {linearMapping, 2, 0, false},
    {linearMapping, 2, 0, false},
    {linearMapping, 2, 0, false}
  }
};

Grip powerGrip = {
  "Power",
  dynamic,
  {1024, 0, 0},
  {0, 0, 0},
  200UL,
  {none},
  {
    {linearMapping, 2, 0, false},
    {linearMapping, 2, 500, true},
    {linearMapping, 2, 980, true}
  }
};

Grip pinchGrip = {
  "Pinch",
  dynamic,
  {800, 0, 1023},
  {0, 0, 0},
  200UL,
  {none},
  {
    {linearMapping, 2, 0, false},
    {linearMapping, 2, 800, true},
    {linearMapping, 2, 0, false}
  }
};

Grip grips[NUMBER_OF_PRIMARY_GRIPS] = {openGrip, powerGrip, pinchGrip};


// struct Grip {
//   String                  name;
//   GripType                type;
//   int                     fingerPositions[NUMBER_OF_ACTUATORS];
//   int                     order[NUMBER_OF_ACTUATORS];
//   unsigned long           motionStepDelay;
//   FeedbackScheme          hapticFeedbackScheme[NUMBER_OF_TOUCH_SENSORS];
//   ActuationPattern actuationPattern[NUMBER_OF_ACTUATORS];
// };

unsigned long previousMillis = 0;
unsigned long stateUpdateMinMillis = 0;

void setup()
{
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, cycleGrip, FALLING);
}

void loop()
{
  unsigned long currentMillis = millis();
  // If currect grip is not the currently set grip and enough time has passed:
  if ((currentGripIndex != gripIndex) && (currentMillis - previousMillis >= stateUpdateMinMillis))
  {
    // Get the grip by name
    struct Grip grip = gl.load(grips[gripIndex]);
    // Set the motors to the grip
    mc.setHandPosition(grip);
  }
}

void cycleGrip()
{
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if (interruptTime - lastInterruptTime > 200)
  {
    gripIndex = (gripIndex + 1) % NUMBER_OF_PRIMARY_GRIPS;
  }
  lastInterruptTime = interruptTime;
}
