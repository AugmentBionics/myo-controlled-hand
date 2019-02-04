> Needs updating

-- Alex 04/02/19!

# myo-controlled-hand

![Augment Bionics Logo][logo]

Muscle-controlled, robotic, below-elbow prosthesis.

## Raw data
Run demo.py to see a sample plot of the data.

### Description
There are 3 folders with approximately 60 seconds of Myo sensor activity recorded. Folders named loc_x record power grips, that is just flexing the forearm muscle, in two slightly different locations on the same muscle. The double grips folder recorded a set of quick succession grips which could be detected and used to lock the hand in a fixed position

### Format
t:xx,s:xx,:mxx \n

  * t - time in ms
  * s - sampled analog value from arduino ADC, range 0:1023
  * m - output value from arduino map function map(s, 0, 1023, 0, 179)

## MyoControlledHand Arduino Project
### Structure
All code is launched from `MyoControlledHand.ino` and all core functionality is included as libraries in C++.

`Config.h` contains compile time parameters for the entire project.

The `GripLoader` class (TODO) read requested grip into the format desribed in `GripUtils.h` and call the `MotorController` to change the grip.

The `MotorController` class takes grips and move the motors to the desired positions in the desired order. It also handles input from the myoelectric sensor and applies the correct motion to the hand.

### Grip Specification

```
struct Grip {
  String                  name;
  // simple, dynamic, or triggered
  GripType                type;
  // 0 to 1023 for each actuator
  int                     fingerPositions[NUMBER_OF_ACTUATORS];
  // 0 to (1 - NUMBER_OF_ACTUATORS) for each actuator e.g. {1, 0, 2} or {1, 0, 0}
  int                     order[NUMBER_OF_ACTUATORS];
  // delay in ms between starting one "batch" of motions and the next
  unsigned long           motionStepDelay;
  // continuous, contact, or none for each touch sensor
  FeedbackScheme          hapticFeedbackScheme[NUMBER_OF_TOUCH_SENSORS];
  // description of actuation for dynamic grips
  struct ActuationPattern actuationPattern[NUMBER_OF_ACTUATORS];
};
struct ActuationPattern {
  // list of points to perform a non-linear mapping between [0-1023] and [0-1023]
  struct Mapping         *controlCurve;
  // number of points
  int                     controlCurveResolution;
  // goal position of dynamic grip
  int                     actuationGoalPosition;
  // whether or not this is actuator is moved during the dynamic grip
  bool                    isActuated;
};
```
[logo]: https://www.eng.ed.ac.uk/sites/eng.ed.ac.uk/files/images/augment-bionics-logo-100h.jpg "Augment Bionics Logo"
