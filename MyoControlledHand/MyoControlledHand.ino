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
unsigned long stateUpdateMinMillis = 500;

volatile unsigned int inputIndex = 0;
int inputs[2] = {POT_PIN, MYO_PIN};


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

void cycleInput()
{
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if (interruptTime - lastInterruptTime > 200)
  {
    inputIndex = (inputIndex + 1) % 2;
  }
  lastInterruptTime = interruptTime;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("START");
  mc.init(actuatorConfigs, 100, 150);
  delay(2000);
  Serial.println("...");
  pinMode(BUTTON_1_PIN, INPUT);
  pinMode(BUTTON_2_PIN, INPUT);
  pinMode(MYO_PIN, INPUT);
  pinMode(POT_PIN, INPUT);
  // For pot to work
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  attachInterrupt(digitalPinToInterrupt(BUTTON_1_PIN), cycleGrip, LOW);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2_PIN), cycleInput, LOW);
}

void loop()
{
  unsigned long currentMillis = millis();
  // If currect grip is not the currently set grip and enough time has passed:
  if ((currentGripIndex != gripIndex) && (currentMillis - previousMillis >= stateUpdateMinMillis))
  {
    currentGripIndex = gripIndex;
    mc.setHandPosition(grips[currentGripIndex]);
    Serial.println("Grip cycled");
    Serial.println(grips[currentGripIndex].name);
  }
  //  int myoValue = analogRead(inputs[inputIndex]);
  //  Serial.println(myoValue);
  //  mc.handleDynamicActuation(myoValue);
  //Serial.println(myoValue);
}
