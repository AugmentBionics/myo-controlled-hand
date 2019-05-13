#ifndef MYOCONTROLLEDHAND_MYOINPUT_H
#define MYOCONTROLLEDHAND_MYOINPUT_H

#include "SensingMessaging.h"

enum GripSelection {
    primary,
    other
};

/*!
 * Class that reads from myo sensors and interprets this as high-level "actions"
 * TODO: Improve action detection
 * TODO: Increase sensor count
 */
class MyoInput {
 public:

    explicit MyoInput(SensingState *state);

    void init(); /*!< Setup pins */

    enum Action {
        open, /*!< User intends to open the grip */
        close, /*!< User intends to close the grip */
        none /*!< No action detected */
    }; /*!< Actions that can be detected */

    bool primaryGripTriggered();

    Action readAction(); /*!< discern current action @note currently must be polled in loop()*/

 private:
    const static unsigned int bufferSize = 40;
    int _m1Raw = 0;
    int _m1Sig = 0;
    int _m2Raw = 0;
    int _m2Sig = 0;
    int _m1RawBuffer[bufferSize];
    int _m2RawBuffer[bufferSize];
    SensingState *state;
};

#endif //MYOCONTROLLEDHAND_MYOINPUT_H
