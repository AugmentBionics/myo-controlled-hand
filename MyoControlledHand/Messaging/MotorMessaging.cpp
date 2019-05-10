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
                }
                state->setGripPattern(pattern);
                break;
            }

            case 'm': // move
            {
                Serial.print("Move: ");
                switch (messageBuffer[2]) {
                    case 'o': // open
                        Serial.println("open");
                        state->openGrip();
                        break;
                    case 'c': // close
                        Serial.println("close");
                        state->closeGrip();
                        break;
                    case 'i': // idle
                        Serial.println("idle");
                        state->idle();
                        break;
                    case 'b': // brake
                        Serial.println("brake");
                        state->brake();
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
                if (!isOpen[i])
                    motorController.open(i);
            }

            case 'c': {
                if (!isClosed[i])
                    motorController.close(i);
            }

            case 'i': {
                if (!isClosed[i])
                    motorController.idle(i);
            }

            default:break;
        }
    }
}

char MotorState::currentGripPattern[NUMBER_OF_ACTUATORS] = {'o', 'o', 'o', 'o'};

bool MotorState::isClosed[NUMBER_OF_ACTUATORS] = {};
bool MotorState::isOpen[NUMBER_OF_ACTUATORS] = {};
MotorController MotorState::motorController = MotorController();