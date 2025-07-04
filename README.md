<div align="center">
  <h1>
    SCARA Robot Controller
  </h1>
  <p>
    <b><i>An application for controlling a SCARA robotic arm using a joystick, accelerometer, or autonomous mode</i></b>
  </p>
  <p>
    Developed using&nbsp;&nbsp;
    <a href="https://skillicons.dev">
      <img src="https://skillicons.dev/icons?i=c,vscode,git" />
    </a>
  </p>
</div>

<br />

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Build System](#build-system)
- [Contributors](#contributors)
- [License](#license)

---

## Overview

This project implements firmware for a SCARA robotic arm controlled via an [ADuC834](https://www.analog.com/media/en/technical-documentation/data-sheets/ADUC834.pdf), an 8051-compatible microcontroller . It supports interactive joystick control, motion tracking via an accelerometer and autonomous movement. The system is designed for educational embedded robotics applications, originally conceived as a project in Warsaw University of Technology's course for microcontrollers.

An illustration of the SCARA robotic arm configuration is presented [here](https://www.desmos.com/calculator/3ebmf7hpk8) as an interactive Desmos graph.

---

## Features

- **Modular Peripheral Support**
  - Joystick input for manual control (read using ADCs)
  - Accelerometer-based gesture control ([LSM6DS33](https://www.pololu.com/file/0J1087/LSM6DS33.pdf) read using I2C)
  - LCD screen feedback and mode display
  - Asynchronous control of servo motors with minimal signal jitter
- **State Machine Architecture**
  - Idle, Joystick, Accelerometer, and Auto modes
- **Autonomous Pattern Execution**
  - Custom pre-programmed path using an array of points (defined in `inc/config.h`)
- **Robust Safety & Feedback**
  - Tip control, range checking, and on-screen alerts for invalid positions

---

## Installation

> ⚙️ Ensure you have [SDCC](http://sdcc.sourceforge.net/) and `make` installed on your system (tested on Arch Linux).

1. Clone the repository:

```bash
git clone https://github.com/your-username/scara-robot-controller.git
cd scara-robot-controller
```

2. Compile the project using the provided Makefile:

```bash
make all
```

3. The compiled output (`release.hex`) will be located in the `build/` directory.

Additionally, this repository is compatible with the [EIDE](https://marketplace.visualstudio.com/items?itemName=CL.eide) extension available for Visual Studio Code.

---

## Usage

Flash `build/release.hex` onto your 8051 microcontroller using your preferred flashing tool. Connect the required peripherals (joystick, LCD, accelerometer, servo drivers and buttons as specified by `inc/lab_board.h`), then power on the system.

States:
- **IDLE**: Waits for user input via buttons.
- **JSTK**: Use the joystick to manually move the arm.
- **XLDA**: Use accelerometer tilt to move the arm.
- **AUTO**: Executes a sequence of predefined positions.

State transitions are triggered by hardware button inputs.

---

## Build System

- All compiled artifacts (`.rel`, `.lst`, `.hex`, etc.) are placed in `/build`.
- The Makefile is SDCC-aware:
  - Compiles each `.c` file individually
  - Links `.rel` files with `main.rel` placed first as required by SDCC
- Clean with:
  ```bash
  make clean
  ```

---

## Contributors

- [J.Soto](https://github.com/Soto-Jnthan) — Developer & Maintainer

---

## License

[MIT](https://choosealicense.com/licenses/mit/)
