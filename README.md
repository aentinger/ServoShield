<a href="https://lxrobotics.com/"><img align="right" src="https://assets.lxrobotics.com/logo-old/lxrobotics.png" width="15%"></a>
💾 Servo Shield
===============

[![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg)](http://creativecommons.org/licenses/by-nc-sa/4.0/)

# 📸 Image

![LXRobotics P14 ServoShield](https://raw.githubusercontent.com/lxrobotics/ServoShield/master/images/servo-shield-side-small.JPG)

# 📂 Description

The LXRobotics Servo Shield facilitates the control of up to 32 model making (RC) servos. The control of the servos is done over two special ICs of type PCA9685 which communicates via I2C-Interface with Arduino - for the control of 32 servos only two Arduino Pins are required. For the servo supply, a dedicated linear voltage regulator is built on the Servo Shield, whereat using jumper can be switched over between the voltage regulator of the Servo Shield and the Arduino's power supply. Alternatively, the Servo Shield can be also externally power supplied via plug connector. For the quick start, a finished Arduino Library with sample programs is available.

**Features**

* Control of up to 32 Model making (RC) Servos
* Separate linear voltage regulator 
* Different options for the power supply of servos: Arduino, Servo Shield, Extern
* Control via I2C – thre are only two Arduino-Pins required (SDA, SCL)
* I2C-Address using Jumper adjustable - up to 25 = 32 different addresses possible
* Stackable - multiple Servo Shields can be put on top of each other and controlled over only one Arduino (theoretically 32 Servo Shields are possible)
* I2C-PullUp-Resistor via jumper adjustable
* Status-LED for the visualization of the supply state of the Servo Shields
* Activation/Deactivation of all Servo outputs of PCA 9685 over digital outputs possible ( function via jumper connected/disconnected)
* Arduino Library available for control with example programs

# 🎥 [Video](images/servo_shield_demo.mp4)
