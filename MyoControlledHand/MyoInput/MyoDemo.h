#ifndef MYOCONTROLLEDHAND_MYODEMO_H
#define MYOCONTROLLEDHAND_MYODEMO_H

#include "MyoInput.h"

class MyoDemo {
 public:
    MyoInput::Action getNextDemoAction();
 private:
    const unsigned long waitTime = 3000;
    const MyoInput::Action actionLoop[4] = {MyoInput::close, MyoInput::none, MyoInput::open, MyoInput::none};
};

#endif //MYOCONTROLLEDHAND_MYODEMO_H
