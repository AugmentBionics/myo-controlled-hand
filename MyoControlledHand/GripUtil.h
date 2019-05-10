/*! @file GripUtil.h
 * Data structures for dealing with grips
 * TODO: Consolidate scattered grip utility code in this file
 */
#ifndef GripUtil_h
#define GripUtil_h

#include "Arduino.h"
#include "Config.h"

/*! @brief Type of grip
 * (to support future expansion to different grip control schemes
 * and possible haptic feedback) */
enum GripType {
    simple, /*!< Simple grip control:<br>Has open and closed position and moves motors between these. */
    triggered /*!< [NOT IMPLEMENTED] Planned grip control scheme with concept of locking and triggering. */
};
/*!
 * @brief Representation of whether an actuator responds to input (<b>actuate</b>),
 * is locked open (<b>open</b>), or is locked closed (<b>close</b>).
 */
enum ActuationScheme {
    actuate,
    open,
    close
};

/*! @brief Describes a grip
 * @note Currently only <b>GripType::simple</b> is used and grips are only defined by there <b>actuationPatter</b>.
 */
struct Grip {
 public:
    char name[8];
    GripType type;
    uint8_t startPercent[NUMBER_OF_ACTUATORS]; /*!< [UNUSED] see note */
    uint8_t finishPercent[NUMBER_OF_ACTUATORS]; /*!< [UNUSED] see note */
    ActuationScheme actuationPattern[NUMBER_OF_ACTUATORS];
};

#endif // GripUtil_h
