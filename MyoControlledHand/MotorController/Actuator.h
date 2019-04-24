#ifndef Actuator_h
#define Actuator_h

#include "Arduino.h"
#include "Config.h"

/*!
 * @brief Represents an actuator (e.g. a motor) with current limiting
 * @note Currently only has basic estimate of position based on time spent traveling in different directions (<b>timeState</b>)
 */
class Actuator {
 public:

    /*!
     * @brief Actuator configuration parameters
     */
    struct Config {
        String name;
        uint8_t forwardPin;
        uint8_t reversePin;
        uint8_t currentPin;
    };

    /*!
     * State (action) of an Actuator
     */
    enum State {
        unknown, /*!< State unknown */
        forward, /*!< Actuator is moving in forward direction */
        reverse, /*!< Actuator is moving in reverse direction */
        braking, /*!< Actuator is stopped and actively countering motion */
        coasting /*!< Actuator is stopped but not actively countering motion*/
    };

    /*! Default constructor. @note allows pre-allocation of memory */
    Actuator();
    /*!
     * Constructor (that actually initialises Actuator)
     * @param config - configuration parameters struct
     */
    explicit Actuator(Config config);

    /*!
     * Low-level function to set motor driver digital pins
     * @param forward - digital value for forward pin (accepts Arduino <b>HIGH</b> or <b>LOW</b>)
     * @param reverse - digital value for reverse pin (accepts Arduino <b>HIGH</b> or <b>LOW</b>)
     */
    void drive(uint8_t forward, uint8_t reverse);
    /*!
     * High-level control running actuator in forward direction and updating state
     */
    void runForward();
    /*!
     * High-level control running actuator in reverse direction and updating state
     */
    void runReverse();
    /*!
     * High-level control actively braking actuator and updating state
     */
    void brake();
    /*!
     * High-level control passively stopping actuator and updating state
     */
    void coast();
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
