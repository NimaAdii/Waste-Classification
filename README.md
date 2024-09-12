
# Automatic Garbage Sorting System
The development of a Smart Waste Management System incorporating an Image Classification unit running on a Raspberry Pi 4 B single-board computer. The system utilizes a conveyor belt with actuators, sensors, and an Arduino microcontroller board to transfer waste to the correct bin. Additionally, a compressing and sealing unit, controlled by the same Arduino microcontroller board, is connected to the Raspberry Pi via a serial connection. This unit is capable for compressing waste and sealing the corresponding waste collection bag.

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

### Conveyor Belt Control
The 'ConveyorBelt.ino' script handles the movement of the conveyor belt, object detection using ultrasonic sensors, and sending commands to the image classification system.

## Image Classification Model
The img.py script captures images from the camera, classifies them using a pre-trained deep learning model, and communicates with the Arduino system.

## Setup and Installation
1. Arduino: Upload the Arduino codes to the Arduino Uno using the Arduino IDE.
2. Python Environment: Set up Python 3.x and required libraries (TensorFlow, OpenCV) using pip install -r requirements.txt.
3. Model: Place the imageclassifier.h5 model file in the specified location on your device.
4. Camera: Ensure the camera is correctly connected and accessible.

## Usage
Start the Arduino system to initiate the hardware components.
Run the Python script to start the image classification and sorting process.
The system will classify and sort objects as they are placed on the conveyor belt.

![Picture1](https://github.com/user-attachments/assets/c1716ee6-e2ba-4c0f-adeb-385849575401)

