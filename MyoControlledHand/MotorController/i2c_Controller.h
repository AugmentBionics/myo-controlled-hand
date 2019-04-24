#ifndef i2c_Controller.h
#define i2c_Controller_h

#include "Arduino.h"
#include "Config.h"
#include "Adafruit_PWMServoDriver.h"
#include "Wire.h"

/*!
 * @brief Represents an actuator (e.g. a motor) with current limiting
 * @note Currently only has basic estimate of position based on time spent traveling in different directions (<b>timeState</b>)
 */
class i2c_Controller {
 public:
    struct Config {
        uint8_t startPin;
        uint8_t currentPin0;
        uint8_t currentPin1;
        uint8_t currentPin2;
        uint8_t currentPin3;
    };

    /*! Default constructor. @note allows pre-allocation of memory */
    i2c_Controller();
    /*!
     * Constructor (that actually initialises Controller)
     * @param config - configuration parameters struct
     */
    explicit i2c_Controller(Config config);

    /*!
     * Low-level function to set motor driver digital pins
     * @param forward - digital value for forward pin (accepts Arduino <b>HIGH</b> or <b>LOW</b>)
     * @param reverse - digital value for reverse pin (accepts Arduino <b>HIGH</b> or <b>LOW</b>)
     */

    void closeHand();

    void openHand();

    void setAllPot(byte b);

    void shiftOutWord(word w);

    void limitBreak();

    void limitIdle();

    bool handStopped(word w);

    bool handBraked(word w);

    bool handIdled(word w);

    bool m0Stopped(word w);

    bool m1Stopped (word w);

    bool m2Stopped (word w);

    bool m3Stopped (word w);

    bool m0Breaked(word w);

    bool m1Breaked(word w);

    bool m2Breaked(word w);

    bool m3Breaked(word w);

    bool m0Idled(word w);

    bool m1Idled(word w);

    bool m2Idled(word w);

    bool m3Idled(word w);

    void closeAll();

    void closeM0();

    void closeM1();

    void closeM2();

    void closeM3();

    void openAll();

    void openM0();

    void openM1();

    void openM2();

    void openM3();

    void idleAll();

    void idleM0();

    void idleM1();

    void idleM2();

    void idleM3();

    void breakAll();

    void breakM0();

    void breakM1();

    void breakM2();

    void breakM3();

    void delEn();

    void delEnM0();

    void delEnM1();

    void delEnM2();

    void delEnM3();

    void delDis();

    void delDisM0();

    void delDisM1();

    void delDisM2();

    void delDisM3();

    void test();

    /*!
     * Check whether current driver's current limiter is limiting
     */
    bool isLimited();
    unsigned long getTimeState();
    String getName();

 private:

    Config _config;
    State _state = coasting;
    /*! basic pseudo-position estimate tracking time
     * running actuator forward subtract time running
     * in reverse */
    unsigned long _timeState = 0;
    unsigned long _timeOfLastUpdate;
    void updateTimeState();
};

#endif // Actuator_h
