/*! \file Grips.h
 * Grip definitions
 */
#ifndef Grips_h
#define Grips_h
#include "Config.h"
#include "../GripUtil/GripUtil.h"

Grip openGrip = {
    "Open",
    simple,
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {open, open, open, open}
};

Grip powerGrip = {
    "Power",
    simple,
    {0, 0, 0, 0},
    {100, 100, 100, 100},
    {actuate, actuate, actuate, actuate}
};

Grip pinchGrip = {
    "Pinch",
    simple,
    {0, 0, 0, 0},
    {100, 100, 0, 0},
    {actuate, actuate, open, open}
};

Grip tripodGrip = {
    "Tripod",
    simple,
    {0, 0, 0, 0},
    {100, 100, 100, 0},
    {actuate, actuate, actuate, close}
};

Grip indexGrip = {
    "Index",
    simple,
    {0, 0, 0, 0},
    {0, 100, 0, 0},
    {close, actuate, close, close}
};

Grip keyGrip = {
    "Key",
    simple,
    {0, 0, 0, 0},
    {100, 0, 0, 0},
    {actuate, close, close, close}
};

Grip grips[NUMBER_OF_PRIMARY_GRIPS] = {openGrip, powerGrip, pinchGrip, tripodGrip, indexGrip, keyGrip};

#endif // Grips_h