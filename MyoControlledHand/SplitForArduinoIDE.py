#!/usr/bin/python3
import os
import shutil

print("Creating directory structure...")
if not os.path.exists("Arduino-IDE-Projects"):
    os.makedirs("Arduino-IDE-Projects")

if not os.path.exists("Arduino-IDE-Projects/UI"):
    os.makedirs("Arduino-IDE-Projects/UI")

if not os.path.exists("Arduino-IDE-Projects/SENSING"):
    os.makedirs("Arduino-IDE-Projects/SENSING")

if not os.path.exists("Arduino-IDE-Projects/MOTOR"):
    os.makedirs("Arduino-IDE-Projects/MOTOR")

hdrs_ui = []
hdrs_sensing = []
hdrs_motor = []
hdrs = [hdrs_ui, hdrs_sensing, hdrs_motor]
hdr_index = 0

srcs_ui = []
srcs_sensing = []
srcs_motor = []
srcs = [srcs_ui, srcs_sensing, srcs_motor]
src_index = 0

print("Parsing CMakeLists.txt...")
with open("CMakeLists.txt") as cml:
    raw = cml.readlines()
    lines = raw
    for i in range(len(raw)):
        lines[i] = raw[i].split()
    for line in lines:
        if len(line) > 0 and line[0] == "HDRS":
            for j in range(len(line) - 1):
                hdrs[hdr_index].append(line[j + 1])
            hdr_index = hdr_index + 1
        elif len(line) > 0 and line[0] == "SRCS":
            for j in range(len(line) - 1):
                srcs[src_index].append(line[j + 1])
            src_index = src_index + 1

print("Found headers:")
print(hdrs)
print("Found sources:")
print(srcs)

# UI
shutil.copyfile("ui.cpp", "Arduino-IDE-Projects/UI/UI.ino")
print("Created Arduino-IDE-Projects/UI/UI.ino")
for file in hdrs_ui:
    shutil.copy(file, "Arduino-IDE-Projects/UI/")
print("Copied UI Headers")
for file in srcs_ui:
    shutil.copy(file, "Arduino-IDE-Projects/UI/")
print("Copied UI Sources")

# SENSING
shutil.copyfile("sensing.cpp", "Arduino-IDE-Projects/SENSING/SENSING.ino")
print("Created Arduino-IDE-Projects/SENSING/SENSING.ino")
for file in hdrs_sensing:
    shutil.copy(file, "Arduino-IDE-Projects/SENSING/")
print("Copied SENSING Headers")
for file in srcs_sensing:
    shutil.copy(file, "Arduino-IDE-Projects/SENSING/")
print("Copied SENSING Sources")

# MOTOR
shutil.copyfile("motor.cpp", "Arduino-IDE-Projects/MOTOR/MOTOR.ino")
print("Created Arduino-IDE-Projects/MOTOR/MOTOR.ino")
for file in hdrs_motor:
    shutil.copy(file, "Arduino-IDE-Projects/MOTOR/")
print("Copied MOTOR Headers")
for file in srcs_motor:
    shutil.copy(file, "Arduino-IDE-Projects/MOTOR/")
print("Copied MOTOR Sources")
