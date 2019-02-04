#ifndef MYOCONTROLLEDHAND_MYOINPUT_H
#define MYOCONTROLLEDHAND_MYOINPUT_H

/*!
 * Class that reads from myo sensors and interprets this as high-level "actions"
 * TODO: Improve action detection
 * TODO: Increase sensor count
 */
class MyoInput {
 public:

    MyoInput();

    void init(); /*!< Setup pins */

    enum Action {
        open, /*!< User intends to open the grip */
        close, /*!< User intends to close the grip */
        none /*!< No action detected */
    }; /*!< Actions that can be detected */

    Action readAction(); /*!< discern current action @note currently must be polled in loop()*/

 private:
    const static unsigned int bufferSize = 40;
    int _m1Raw = 0;
    int _m1Sig = 0;
    int _m2Raw = 0;
    int _m2Sig = 0;
    int _m1RawBuffer[bufferSize];
    int _m2RawBuffer[bufferSize];
};

#endif //MYOCONTROLLEDHAND_MYOINPUT_H
