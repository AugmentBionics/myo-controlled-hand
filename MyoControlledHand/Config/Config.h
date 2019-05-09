/*! \file Config.h
 * Global configuration file that defines constants and pins
 */
#ifndef Config_h
#define Config_h
#include "Arduino.h"

#define M0_FWD 0
#define M0_REV 1
#define M0_DEL 2

#define M1_FWD 3
#define M1_REV 4
#define M1_DEL 5

#define M2_FWD 6
#define M2_REV 7
#define M2_DEL 8

#define M3_FWD 9
#define M3_REV 10
#define M3_DEL 11

#define MOTOR_1_FWD_PIN 4
#define MOTOR_1_REV_PIN 5
#define MOTOR_1_CUR_PIN 6

#define MOTOR_2_FWD_PIN 7
#define MOTOR_2_REV_PIN 8
#define MOTOR_2_CUR_PIN 9

#define MOTOR_3_FWD_PIN 10
#define MOTOR_3_REV_PIN 11
#define MOTOR_3_CUR_PIN 12

#define MOTOR_4_FWD_PIN A0
#define MOTOR_4_REV_PIN 2
#define MOTOR_4_CUR_PIN A1
#define MOTOR_LIM_PIN 3

#define MYO_1_SIG_PIN A7
#define MYO_1_RAW_PIN A6
#define MYO_2_SIG_PIN A5
#define MYO_2_RAW_PIN A4

#define NUMBER_OF_ACTUATORS 4
#define NUMBER_OF_PRIMARY_GRIPS 6

#endif // Config_h
