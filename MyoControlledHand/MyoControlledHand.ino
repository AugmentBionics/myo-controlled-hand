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

const Grip indexGrip = {
    "index",
    simple,
    {0, 0, 0, 0},
    {0, 100, 0, 0},
    {close, actuate, close, close}
};

const Grip keyGrip = {
    "key",
    simple,
    {0, 0, 0, 0},
    {100, 0, 0, 0},
    {actuate, close, close, close}
};

const Grip grips[NUMBER_OF_PRIMARY_GRIPS] = {openGrip, powerGrip, pinchGrip, tripodGrip, indexGrip, keyGrip};

MotorController mc(true);
MyoInput myo;

byte incomingByte = 0;
unsigned int prevGripIndex = 0;

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
    while (Serial.available() > 0) {
        incomingByte = Serial.read();
    }
    unsigned int index = min(NUMBER_OF_PRIMARY_GRIPS - 1, (uint8_t) incomingByte - 1);
    if (index != prevGripIndex) {
        mc.setGrip(grips[index]);
        prevGripIndex = index;
    }
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
            mc.brake();
            break;
    }
    delay(3);
}
