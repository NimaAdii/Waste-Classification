The development of a Smart Waste Management System incorporating an Image Classification unit running on a Raspberry Pi 4 B single-board computer. The system utilizes a conveyor belt with actuators, sensors, and an Arduino microcontroller board to transfer waste to the correct bin. Additionally, a compressing and sealing unit, controlled by the same Arduino microcontroller board, is connected to the Raspberry Pi via a serial connection. This unit is capable for compressing waste and sealing the corresponding waste collection bag.

# Automatic Garbage Sorting System

This project focuses on designing an automatic garbage sorting system using a conveyor belt, ultrasonic sensors, stepper motors, servo motors, and a deep learning-based image classification model. The system identifies different types of waste and sorts them accordingly.

## Table of Contents

- [Project Overview](#project-overview)
- [Hardware Components](#hardware-components)
- [Software Components](#software-components)
- [Arduino Code](#arduino-code)
  - [Compressing and Sealing](#compressing-and-sealing)
  - [Conveyor Belt Control](#conveyor-belt-control)
- [Image Classification Model](#image-classification-model)
- [Setup and Installation](#setup-and-installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Project Overview

The automatic garbage sorting system uses an image classification model to identify and sort waste into categories such as Paper, Polythene, and Waste Food. The system uses ultrasonic sensors to detect the presence of waste, moves the waste using a conveyor belt, captures images using a camera, and then processes the images to classify the waste type.

### Key Features

- Ultrasonic sensors to detect objects on the conveyor belt.
- Stepper motors and servo motors to control the movement of waste.
- Image classification using a deep learning model to identify waste types.
- Arduino microcontroller to coordinate the system components.

## Hardware Components

- Arduino Uno
- Ultrasonic Sensors (HC-SR04)
- Stepper Motor and Driver
- Servo Motors
- Conveyor Belt System
- Relay Module
- Power Supply
- LEDs and Resistors

## Software Components

- Arduino IDE
- Python 3.x
- OpenCV
- TensorFlow
- Serial Communication Libraries

## Arduino Code

### Compressing and Sealing

The `CompressingAndSealing.ino` script controls the compressing and sealing process using stepper motors, servo motors, and relays.
