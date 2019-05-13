#!/usr/bin/python3
import shutil

# UI
shutil.copyfile("ui.cpp", "Arduino-IDE-Projects/UI/UI.ino")
ui_files = ["Messaging/Messaging.cpp", "Messaging/UIMessaging.cpp", "Messaging/Messaging.h", "Messaging/UIMessaging.h",
            "Config/Config.h", "Config/Grips.h", "GripUtil/GripUtil.h"]
for file in ui_files:
    shutil.copy(file, "Arduino-IDE-Projects/UI/")

# SENSING
shutil.copyfile("sensing.cpp", "Arduino-IDE-Projects/SENSING/SENSING.ino")
sensing_files = ["Messaging/Messaging.cpp", "Messaging/SensingMessaging.cpp", "Messaging/Messaging.h",
                 "Messaging/SensingMessaging.h", "Config/Config.h", "MyoInput/MyoInput.cpp", "MyoInput/MyoInput.h"]
for file in sensing_files:
    shutil.copy(file, "Arduino-IDE-Projects/SENSING/")

# MOTOR
shutil.copyfile("motor.cpp", "Arduino-IDE-Projects/MOTOR/MOTOR.ino")
motor_files = ["Messaging/Messaging.cpp", "Messaging/MotorMessaging.cpp", "Messaging/Messaging.h",
               "Messaging/MotorMessaging.h", "Config/Config.h", "MotorController/MotorController.cpp",
               "MotorController/MotorController.h"]
for file in motor_files:
    shutil.copy(file, "Arduino-IDE-Projects/MOTOR/")
