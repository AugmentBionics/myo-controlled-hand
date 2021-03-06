#include "Arduino.h"
#include "MotorMessaging.h"

void MotorMessageHandler::interpretMessage(int length) {
    if (length <= 2) return;

    if (messageBuffer[0] == address) {
        // Message is for motor arduino -> interpret

        Serial.print("Message: ");
        for (int i = 0; i < length - 1; ++i)
            Serial.write(messageBuffer[i]);
        Serial.print('\n');

        Serial.print("=> ");

        switch (messageBuffer[1]) {

            case 'p': // set grip pattern
            {
                char pattern[NUMBER_OF_ACTUATORS];
                Serial.print("Set grip: ");
                for (int i = 2; i <= NUMBER_OF_ACTUATORS + 2; ++i) {
                    char c = messageBuffer[i];
                    switch (c) {
                        case 'o': // opened
                            pattern[i - 2] = c;
                            break;
                        case 'c': // closed
                            pattern[i - 2] = c;
                            break;
                        case 'd': // dynamic
                            pattern[i - 2] = c;
                            break;
                        case 'i': // idle
                            pattern[i - 2] = c;
                            break;
                        default: // ignore other characters
                            break;
                    }
                    Serial.write(c);
                }
                state->setGripPattern(pattern);
                Serial.write('\n');
                break;
            }

            case 'm': // move
            {
                Serial.print("Move: ");
                switch (messageBuffer[2]) {
                    case 'o': // open
                        if (lastGripCommand != messageBuffer[2]) {
                            Serial.println("open");
                            state->openGrip();
                            lastGripCommand = messageBuffer[2];
                        }
                        break;
                    case 'c': // close
                        if (lastGripCommand != messageBuffer[2]) {
                            Serial.println("close");
                            state->closeGrip();
                            lastGripCommand = messageBuffer[2];
                        }
                        break;
                    case 'i': // idle
                        if (lastGripCommand != messageBuffer[2]) {
                            Serial.println("idle");
                            state->idle();
                            lastGripCommand = messageBuffer[2];
                        }
                        break;
                    case 'b': // brake
                        if (lastGripCommand != messageBuffer[2]) {
                            Serial.println("brake");
                            state->brake();
                            lastGripCommand = messageBuffer[2];
                        }
                        break;
                    default:break;
                }
                break;
            }

            default:break;
        }
    } else {
        Serial.write('@');
        Serial.println(String(messageBuffer));
    }
    newMessage = false;
    clearMessageBuffer();
}

MotorMessageHandler::MotorMessageHandler(MotorState *state) : MessageHandler('m'), state(state) {}

void MotorState::setGripPattern(const char pattern[]) {
    unsigned int iMax = NUMBER_OF_ACTUATORS - 1;
    for (unsigned int i = 0; i <= iMax; ++i) {
        currentGripPattern[i] = pattern[i];
    }
}

void MotorState::closeGrip() {
    forEachDynamicActuator(&MotorController::close);
}

void MotorState::openGrip() {
    forEachDynamicActuator(&MotorController::open);
}

void MotorState::brake() {
    forEachDynamicActuator(&MotorController::brake);
}

void MotorState::idle() {
    forEachDynamicActuator(&MotorController::idle);
}

void MotorState::forEachDynamicActuator(MotorControllerFuncPtr function) {
    for (unsigned int i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
        switch (currentGripPattern[i]) {
            case 'd': {
                (motorController.*function)(i);
                break;
            }

            case 'o': {
                motorController.open(i);
                break;
            }

            case 'c': {
                if (!motorController.isClosed[i])
                    motorController.close(i);
                break;
            }

            case 'i': {
                motorController.idle(i);
                break;
            }

            default:break;
        }
    }
}

void MotorState::init() {
    motorController.init();
}

void MotorState::update() {
    for (unsigned int i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
        if (motorController.checkCurrentLimiting(i)) {
            ++rdCounters[i];
        } else {
            rdCounters[i] = 0;
        }
    }
    for (unsigned int i = 0; i < NUMBER_OF_ACTUATORS; ++i) {
        if (rdCounters[i] >= rdThreshold) {
            switch (motorController.lastInstruction[i]) {
                default:break;
                case MotorInstruction::open: // open -> idle and set isOpen to true
                    motorController.idle(i, true);
                    motorController.isOpen[i] = true;
                    break;
                case MotorInstruction::close: // brake
                    motorController.brake(i, true);
                    break;
            }
            rdCounters[i] = 0;
        }
    }
}

char MotorState::currentGripPattern[NUMBER_OF_ACTUATORS] = {'o', 'o', 'o', 'o'};
unsigned int MotorState::rdCounters[NUMBER_OF_ACTUATORS];
MotorController MotorState::motorController = MotorController();
