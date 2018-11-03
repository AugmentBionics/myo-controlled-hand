cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)

project(MyoControlledHand)
set(CMAKE_CXX_STANDARD 11)

set(ab_hand_SKETCH
        MyoControlledHand.ino)
set(ab_hand_HDRS
        Config.h)
set(ab_hand_PORT /dev/ttyUSB0)
set(ab_hand_BOARD nano)

generate_arduino_firmware(ab_hand)