#include <Servo.h>
#include "Config.h"
#include "MotorController.h"
#include "GripLoader.h"
#include "StateController.h"

int buttonPin = BUTTON_PIN;
int pins[NUMBER_OF_ACTUATORS] = {
    MOTOR_1_PIN,
    MOTOR_2_PIN,
    MOTOR_3_PIN};
struct Mapping linearMapping[2] = {
    {0, 0},
    {0, 1024}};

struct Config actuatorConfigs[NUMBER_OF_ACTUATORS] = {
    {"thumb",
     MOTOR_1_PIN,
     linearMapping,
     2,
     0,
     1023},
    {"indexFinger",
     MOTOR_2_PIN,
     linearMapping,
     2,
     0,
     1023},
    {"otherFingers",
     MOTOR_3_PIN,
     linearMapping,
     2,
     0,
     1023}};

volatile unsigned int gripIndex = 0;
unsigned int currentGripIndex = NUMBER_OF_PRIMARY_GRIPS; // Nonsensical value to trigger first update.

// "Neutral" "Index" "Power" "Pinch" "Hook"
String grips[NUMBER_OF_PRIMARY_GRIPS] = {"Neutral", "Index", "Power", "Pinch", "Hook"};

MotorController mc = MotorController(actuatorConfigs);
GripLoader gl = GripLoader();

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
