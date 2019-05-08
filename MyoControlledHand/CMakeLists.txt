cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)

#General
project(MyoControlledHand)
set(CMAKE_CXX_STANDARD 11)
#---

set(port_prefix USB)
set(ui_port_num 0)
set(sensing_port_num 1)
set(motor_port_num 2)


link_directories(
        ~/Arduino/libraries/
)

#UI arduino
generate_arduino_firmware(ab_ui
        BOARD nano328
        SRCS Messaging/Messaging.cpp Messaging/UIMessaging.cpp ui.cpp
        HDRS Messaging/Messaging.h Messaging/UIMessaging.h Config/Config.h Config/Grips.h
        ARDLIBS Wire SPI
        PORT /dev/tty${port_prefix}{ui_port_num})
#---

#Myo sensor arduino
generate_arduino_firmware(ab_sensing
        BOARD nano328
        SRCS Messaging/Messaging.cpp Messaging/SensingMessaging.cpp MyoInput/MyoInput.cpp sensing.cpp
        HDRS Messaging/Messaging.h Messaging/SensingMessaging.h MyoInput/MyoInput.h Config/Config.h
        PORT /dev/tty${port_prefix}{sensing_port_num})
#---

#Motor control arduino
generate_arduino_firmware(ab_motor
        BOARD nano328
        SRCS MotorController/MotorController.cpp Messaging/Messaging.cpp Messaging/MotorMessaging.cpp motor.cpp
        HDRS MotorController/MotorController.h Messaging/Messaging.h Messaging/MotorMessaging.h Config/Config.h
        ARDLIBS Wire
        PORT /dev/tty${port_prefix}{motor_port_num})
#---