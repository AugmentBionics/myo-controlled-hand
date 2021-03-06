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

#define CURRENT_LIMITER_ADDR 0x2F
#define CURRENT_LIMITER_M0 0x00
#define CURRENT_LIMITER_M1 0x10
#define CURRENT_LIMITER_M2 0x60
#define CURRENT_LIMITER_M3 0x70

#define M0_RD 3
#define M1_RD 4
#define M2_RD 5
#define M3_RD 6

#define INIT_DEL_PIN_VAL 4096
#define INIT_CURRENT_LIM_M0 200
#define INIT_CURRENT_LIM_M1 200
#define INIT_CURRENT_LIM_M2 200
#define INIT_CURRENT_LIM_M3 200

#define CLOSE_CURRENT_LIM_M0 255
#define CLOSE_CURRENT_LIM_M1 255
#define CLOSE_CURRENT_LIM_M2 255
#define CLOSE_CURRENT_LIM_M3 255

#define OPEN_CURRENT_LIM_M0 200
#define OPEN_CURRENT_LIM_M1 200
#define OPEN_CURRENT_LIM_M2 200
#define OPEN_CURRENT_LIM_M3 200

#define SPEED_CLOSE_M0 4096
#define SPEED_OPEN_M0 4096
#define SPEED_CLOSE_M1 4096
#define SPEED_OPEN_M1 4096
#define SPEED_CLOSE_M2 4096
#define SPEED_OPEN_M2 4096
#define SPEED_CLOSE_M3 4096
#define SPEED_OPEN_M3 4096

#define RD_DELAY 100 // is in cycles of loop()

#define MYO_1_SIG_PIN A7
#define MYO_1_RAW_PIN A6
#define MYO_2_SIG_PIN A5
#define MYO_2_RAW_PIN A4

#define NUMBER_OF_ACTUATORS 4
#define NUMBER_OF_PRIMARY_GRIPS 6

#endif // Config_h
