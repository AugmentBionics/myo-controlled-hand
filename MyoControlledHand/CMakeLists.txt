cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)

#General
project(MyoControlledHand)
set(CMAKE_CXX_STANDARD 11)
#---

set(p USB0)


link_directories(~/Arduino/libraries/)

#UI arduino
generate_arduino_firmware(ab_ui
        BOARD nano328
        SRCS Messaging/Messaging.cpp Messaging/UIMessaging.cpp ui.cpp
        HDRS Messaging/Messaging.h Messaging/UIMessaging.h Config/Config.h Config/Grips.h
        PORT /dev/tty${p})
#---

#Myo sensor arduino
generate_arduino_firmware(ab_sensing
        BOARD nano328
        SRCS Messaging/Messaging.cpp Messaging/SensingMessaging.cpp MyoInput/MyoInput.cpp sensing.cpp
        HDRS Messaging/Messaging.h Messaging/SensingMessaging.h MyoInput/MyoInput.h Config/Config.h
        PORT /dev/tty${p})
#---

#Motor control arduino
generate_arduino_firmware(ab_motor
        BOARD nano328
        SRCS Messaging/Messaging.cpp Messaging/MotorMessaging.cpp motor.cpp
        HDRS Messaging/Messaging.h Messaging/MotorMessaging.h Config/Config.h
        PORT /dev/tty${p})
#---