#ifndef MYOCONTROLLEDHAND_MYOINPUT_H
#define MYOCONTROLLEDHAND_MYOINPUT_H

class MyoInput {
 public:

    MyoInput();

    void init();

    enum Action {
        open,
        close,
        none
    };

    Action readAction();

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
