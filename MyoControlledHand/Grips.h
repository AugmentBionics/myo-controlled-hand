/*! \file Grips.h
 * Grip definitions
 */
#ifndef Grips_h
#define Grips_h
#include "Config.h"
#include "GripUtil.h"

#define OPEN_GRIP {\
"Open",\
simple,\
{0, 0, 0, 0},\
{0, 0, 0, 0},\
{alwaysOpen, alwaysOpen, alwaysOpen, alwaysOpen},\
}

#define POWER_GRIP {\
"Power",\
simple,\
{0, 0, 0, 0},\
{100, 100, 100, 100},\
{myoControl, myoControl, myoControl, myoControl}\
}

#define PINCH_GRIP {\
"Pinch",\
simple,\
{0, 0, 0, 0},\
{100, 100, 0, 0},\
{myoControl, myoControl, alwaysOpen, alwaysOpen}\
}

#define TRIPOD_GRIP {\
"Tripod",\
simple,\
{0, 0, 0, 0},\
{100, 100, 100, 0},\
{myoControl, myoControl, myoControl, alwaysClosed}\
}

#define INDEX_GRIP {\
"Index",\
simple,\
{0, 0, 0, 0},\
{0, 100, 0, 0},\
{alwaysClosed, myoControl, alwaysClosed, alwaysClosed}\
}

#define KEY_GRIP {\
"Key",\
simple,\
{0, 0, 0, 0},\
{100, 0, 0, 0},\
{myoControl, alwaysClosed, alwaysClosed, alwaysClosed}\
}

const Grip PROGMEM grips[NUMBER_OF_PRIMARY_GRIPS] = {OPEN_GRIP, POWER_GRIP, PINCH_GRIP, TRIPOD_GRIP, INDEX_GRIP, KEY_GRIP};

#endif // Grips_h
