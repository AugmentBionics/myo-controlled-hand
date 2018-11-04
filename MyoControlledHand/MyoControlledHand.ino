#include "Config.h"
#include "MotorController.h"
#include "GripUtil.h"

Actuator::Config actuatorConfigs[NUMBER_OF_ACTUATORS] = {
    {"thumb",
     MOTOR_1_FWD_PIN,
     MOTOR_1_REV_PIN,
     MOTOR_1_CUR_PIN
    },
    {"indexFinger",
     MOTOR_2_FWD_PIN,
     MOTOR_2_REV_PIN,
     MOTOR_2_CUR_PIN
    },
    {"middleFinger",
     MOTOR_3_FWD_PIN,
     MOTOR_3_REV_PIN,
     MOTOR_3_CUR_PIN
    },
    {"ringFinger",
     MOTOR_4_FWD_PIN,
     MOTOR_4_REV_PIN,
     MOTOR_4_CUR_PIN
    },
    {"littleFinger",
     MOTOR_5_FWD_PIN,
     MOTOR_5_REV_PIN,
     MOTOR_5_CUR_PIN
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

const PROGMEM Grip openGrip = {
    "Open",
    simple,
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {open, open, open, open, open}
};

const PROGMEM Grip powerGrip = {
    "Power",
    simple,
    {0, 0, 0, 0, 0},
    {100, 100, 100, 100, 100},
    {actuate, actuate, actuate, actuate, actuate}
};

const PROGMEM Grip pinchGrip = {
    "Pinch",
    simple,
    {0, 0, 0, 0, 0},
    {100, 100, 0, 0, 0},
    {actuate, actuate, open, open, open}
};

const PROGMEM Grip tripodGrip = {
    "Tripod",
    simple,
    {0, 0, 0, 0, 0},
    {100, 100, 0, 0, 0},
    {actuate, actuate, close, close, close}
};

const PROGMEM Grip grips[NUMBER_OF_PRIMARY_GRIPS] = {openGrip, powerGrip, pinchGrip, tripodGrip};

    if (interruptTime - lastInterruptTime > 200) {
        gripIndex = (gripIndex + 1) % NUMBER_OF_PRIMARY_GRIPS;
    }
    lastInterruptTime = interruptTime;
}

void cycleInput() {
    static unsigned long lastInterruptTime = 0;
    unsigned long interruptTime = millis();

    if (interruptTime - lastInterruptTime > 200) {
        inputIndex = (inputIndex + 1) % 2;
    }
    lastInterruptTime = interruptTime;
}

void setup() {
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
    attachInterrupt(BUTTON_1_PIN, cycleGrip, LOW);
    attachInterrupt(BUTTON_2_PIN, cycleInput, LOW);
}

void loop() {
    unsigned long currentMillis = millis();
    // If currect grip is not the currently set grip and enough time has passed:
    if ((currentGripIndex != gripIndex) && (currentMillis - previousMillis >= stateUpdateMinMillis)) {
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
