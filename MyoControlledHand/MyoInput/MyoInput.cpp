#include "Arduino.h"
#include "MyoInput.h"
#include "Config.h"

MyoInput::MyoInput() {
}

float range(int *buffer, unsigned int length) {
    int minVal = UINT16_MAX;
    int maxVal = 0;
    for (int i = 0; i < length; ++i) {
        minVal = min(minVal, buffer[i]);
        maxVal = max(maxVal, buffer[i]);
    }
    return abs(maxVal - minVal);
}

MyoInput::Action MyoInput::readAction() {
    static unsigned int i = 0;

    float t1 = 375;
    float t2 = 380;

    _m1Raw = analogRead(MYO_1_RAW_PIN);
    _m1Sig = analogRead(MYO_1_SIG_PIN);
    _m2Raw = analogRead(MYO_2_RAW_PIN);
    _m2Sig = analogRead(MYO_2_SIG_PIN);

    _m1RawBuffer[i] = _m1Raw;
    _m2RawBuffer[i] = _m2Raw;

    i = (i + 1) % bufferSize;

    float r1 = range(_m1RawBuffer, bufferSize);
    float r2 = range(_m2RawBuffer, bufferSize);

    bool b1 = r1 > t1;
    bool b2 = r2 > t2;

    if (b1 && (r1 - r2) > 25) {
        return MyoInput::close;
    } else if (b2 && (r2 - r1) > 25) {
        return MyoInput::open;
    } else {
        return MyoInput::none;
    }
}

void MyoInput::init() {
    pinMode(MYO_1_RAW_PIN, INPUT);
    pinMode(MYO_1_SIG_PIN, INPUT);
    pinMode(MYO_2_RAW_PIN, INPUT);
    pinMode(MYO_2_SIG_PIN, INPUT);
}

bool MyoInput::gripNeedsUpdating() {
    // check for triggers
    return false;
}

GripSelection MyoInput::lastSelectedGrip() {
    // check last selection
    return primary;
}

