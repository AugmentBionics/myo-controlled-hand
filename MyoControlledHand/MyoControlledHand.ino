#include "Config.h"
#include "MotorController.h"
#include "GripUtil.h"
#include "MyoInput.h"

Actuator::Config actuatorConfigs[NUMBER_OF_ACTUATORS] = {
    {"thumb",
     MOTOR_4_REV_PIN,
     MOTOR_4_FWD_PIN,
     MOTOR_4_CUR_PIN
    },
    {"indexFinger",
     MOTOR_1_REV_PIN,
     MOTOR_1_FWD_PIN,
     MOTOR_1_CUR_PIN
    },
    {"middleFinger",
     MOTOR_2_REV_PIN,
     MOTOR_2_FWD_PIN,
     MOTOR_2_CUR_PIN
    },
    {"ringAndLittleFinger",
     MOTOR_3_REV_PIN,
     MOTOR_3_FWD_PIN,
     MOTOR_3_CUR_PIN
    },
};

const Grip openGrip = {
    "Open",
    simple,
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {open, open, open, open}
};

const Grip powerGrip = {
    "Power",
    simple,
    {0, 0, 0, 0},
    {100, 100, 100, 100},
    {actuate, actuate, actuate, actuate}
};

const Grip pinchGrip = {
    "Pinch",
    simple,
    {0, 0, 0, 0},
    {100, 100, 0, 0},
    {actuate, actuate, open, open}
};

const Grip tripodGrip = {
    "Tripod",
    simple,
    {0, 0, 0, 0},
    {100, 100, 100, 0},
    {actuate, actuate, actuate, close}
};

const Grip grips[NUMBER_OF_PRIMARY_GRIPS] = {openGrip, powerGrip, pinchGrip, tripodGrip};
const Grip indexGrip = {
    "index",
    simple,
    {0, 0, 0, 0},
    {0, 100, 0, 0},
    {close, actuate, close, close}
};

volatile unsigned int gripIndex = 0;
unsigned int currentGripIndex = NUMBER_OF_PRIMARY_GRIPS; // Nonsensical value to trigger first update.
const Grip keyGrip = {
    "key",
    simple,
    {0, 0, 0, 0},
    {100, 0, 0, 0},
    {actuate, close, close, close}
};

MotorController mc(true);
MyoInput myo;

void setup() {
    Serial.begin(115200);
    Serial.println("START");

    mc.init(actuatorConfigs);
    myo.init();

    pinMode(MYO_1_RAW_PIN, INPUT);
    pinMode(MYO_1_SIG_PIN, INPUT);
    pinMode(MYO_2_RAW_PIN, INPUT);
    pinMode(MYO_2_SIG_PIN, INPUT);

    mc.setGrip(openGrip);
}

void loop() {
    switch (myo.readAction()) {
        case MyoInput::open:
            // open
            mc.open();
            break;
        case MyoInput::close:
            // close
            mc.close();
            break;
        case MyoInput::none:
            // brake
            mc.coast();
            break;
    }
    delay(3);
}
