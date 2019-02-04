cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)

project(HandInterface)
set(CMAKE_CXX_STANDARD 11)


link_directories(/home/alex/Arduino/libraries/)

set(ab_hand_interface_SKETCH
        HandInterface.ino)
set(ab_hand_interface_PORT /dev/ttyUSB1)
set(ab_hand_interface_BOARD nano328)

generate_arduino_firmware(ab_hand_interface)
