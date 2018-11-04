#include "Arduino.h"
#include "Actuator.h"

Actuator::Actuator()
    : _config({"UNINITIALIZED", NOT_A_PIN, NOT_A_PIN, NOT_A_PIN}) {
}

Actuator::Actuator(Config config) : _config(config) {
    pinMode(_config.forwardPin, OUTPUT);
    pinMode(_config.reversePin, OUTPUT);
    pinMode(_config.curretPin, INPUT);
    coast();
}

void Actuator::runForward() {
    drive(HIGH, LOW);
    updateTimeState();
    _state = forward;
}

void Actuator::runReverse() {
    drive(LOW, HIGH);
    updateTimeState();
    _state = reverse;
}

void Actuator::brake() {
    drive(HIGH, HIGH);
    updateTimeState();
    _state = braking;
}

void Actuator::coast() {
    drive(LOW, LOW);
    updateTimeState();
    _state = coasting;
}

void Actuator::drive(uint8_t forward, uint8_t reverse) {
    digitalWrite(_config.forwardPin, forward);
    digitalWrite(_config.reversePin, reverse);
}

bool Actuator::isLimited() {
    return static_cast<bool>(digitalRead(_config.curretPin));
}

void Actuator::updateTimeState() {
    const unsigned long now = millis();
    unsigned long delta = now - _timeOfLastUpdate;
    switch (_state) {
        case forward:_timeState += delta;
            break;
        case reverse:
            if (delta < _timeState)
                _timeState -= delta;
            else _timeState = 0;
            break;
        case unknown:break;
        case braking:break;
        case coasting:break;
    }
    _timeOfLastUpdate = now;
}

unsigned long Actuator::getTimeState() {
    return _timeState;
}

String Actuator::getName() {
    return _config.name;
}
