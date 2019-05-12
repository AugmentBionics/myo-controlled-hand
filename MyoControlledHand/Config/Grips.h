/*! \file Grips.h
 * Grip definitions
 */
#ifndef Grips_h
#define Grips_h
#include "Config.h"
#include "../GripUtil/GripUtil.h"

#define OPEN_GRIP {\
"Open",\
simple,\
{0, 0, 0, 0},\
{0, 0, 0, 0},\
{open, open, open, open},\
}

#define POWER_GRIP {\
"Power",\
simple,\
{0, 0, 0, 0},\
{100, 100, 100, 100},\
{actuate, actuate, actuate, actuate}\
}

#define PINCH_GRIP {\
"Pinch",\
simple,\
{0, 0, 0, 0},\
{100, 100, 0, 0},\
{actuate, actuate, open, open}\
}

#define TRIPOD_GRIP {\
"Tripod",\
simple,\
{0, 0, 0, 0},\
{100, 100, 100, 0},\
{actuate, actuate, actuate, close}\
}

#define INDEX_GRIP {\
"Index",\
simple,\
{0, 0, 0, 0},\
{0, 100, 0, 0},\
{close, actuate, close, close}\
}

#define KEY_GRIP {\
"Key",\
simple,\
{0, 0, 0, 0},\
{100, 0, 0, 0},\
{actuate, close, close, close}\
}

const Grip PROGMEM
    grips[NUMBER_OF_PRIMARY_GRIPS] = {OPEN_GRIP, POWER_GRIP, PINCH_GRIP, TRIPOD_GRIP, INDEX_GRIP, KEY_GRIP};

#endif // Grips_h