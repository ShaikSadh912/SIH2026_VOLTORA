# ⚡ VOLTRA – Automated MCB Testing Platform

### Automated High-Current Short-Circuit Test System for IEC 60898-1:2015 MCB Compliance

**SIH 2026 Project | Team: VOLTRA**

---

## 📌 Project Overview

**VOLTRA** is an automated MCB testing and monitoring platform developed to demonstrate the concepts of **overcurrent testing, current measurement, trip detection, trip-time measurement, automatic shutdown, data logging, visualization, and report generation**.

The system combines an **Arduino UNO**, current and voltage sensing, relay-controlled resistance selection, and a **Python-based monitoring and reporting interface**.

> **Note:** VOLTRA is an educational prototype and engineering demonstrator. It is not intended for actual IEC compliance certification or commercial MCB testing.

---

## 🎯 Problem Statement

Manual MCB testing can involve repeated measurements, manual timing, monitoring, and result recording.

VOLTRA aims to automate these activities by providing a system that can:

- Apply controlled test conditions
- Select different resistance paths
- Measure test current
- Monitor voltage
- Detect the trip condition
- Measure trip time
- Automatically stop the test
- Record test data
- Display current measurement graphs
- Generate a test report

---

## 💡 Proposed Solution

VOLTRA integrates embedded control, electrical sensing, relay switching, serial communication, data visualization, and automated reporting into one testing platform.

### System Workflow

```text
START
  ↓
Select Test Condition
  ↓
Select Resistance Path
  ↓
Apply Controlled Test
  ↓
Measure Current & Voltage
  ↓
Monitor Test Status
  ↓
Detect Trip Condition
  ↓
Automatic Shutdown
  ↓
Calculate Trip Time
  ↓
Log Test Data
  ↓
Generate Graphs & Report
🏗️ System Architecture
                    ┌────────────────────────┐
                    │       Python HMI       │
                    │                        │
                    │ • Monitoring           │
                    │ • Graphs               │
                    │ • Data Logging         │
                    │ • Report Generation    │
                    └───────────┬────────────┘
                                │
                         Serial Communication
                                │
                                ↓
                    ┌────────────────────────┐
                    │      Arduino UNO       │
                    │                        │
                    │ • Sensor Reading       │
                    │ • Relay Control        │
                    │ • Trip Detection       │
                    │ • System Control       │
                    └───────┬────────┬───────┘
                            │        │
                   ┌────────┘        └─────────┐
                   ↓                           ↓
          ┌─────────────────┐          ┌─────────────────┐
          │  Relay Module   │          │    Sensors      │
          │                 │          │                 │
          │ Resistance      │          │ ACS712 Current  │
          │ Selection       │          │ Voltage Sensor  │
          └────────┬────────┘          └────────┬────────┘
                   │                            │
                   ↓                            │
          ┌─────────────────┐                    │
          │   Test Load     │◄───────────────────┘
          │                 │
          │ 82Ω / 20Ω Path  │
          └─────────────────┘
🔧 Hardware Components
Component	Purpose
Arduino UNO	Main controller and processing unit
ACS712 Current Sensor	Measures current flowing through the test circuit
Voltage Sensor	Measures the test voltage
Relay Module	Selects the required resistance/test path
82Ω Resistor	Lower-current test condition
20Ω Resistance	Higher-current test condition
12-0-12 V Transformer	Provides the low-voltage AC test source
Main Power Relay	Controls test power
LEDs	Status and trip indication
Push Buttons	User control
Buzzer	Status/alert indication
Breadboard & Wires	Prototype circuit connections

Note: The 20Ω resistance is implemented using two 10Ω resistors in series. There is no separate 10Ω test path in the system.

⚙️ Automatic Resistance Selection

VOLTRA uses a relay module to select between different resistance paths.

Test Conditions
Resistance Path	Purpose
82Ω	Lower-current / normal test condition
20Ω	Higher-current / trip demonstration condition

The Arduino controls the relay module to select the required resistance path automatically.

The selected resistance changes the current flowing through the test circuit, allowing different test conditions to be demonstrated.

📡 Current Measurement

The ACS712 current sensor is used to measure the current flowing through the test circuit.

The sensor output is read by the Arduino UNO and processed to obtain the measured current.

The measured data is then transmitted to the Python application through serial communication.

Current Monitoring

The system can display and record:

Current value
Current variation
Test status
Trip event
Trip time
Test data
⚡ Voltage Measurement

A voltage sensor is used to monitor the voltage supplied to the test circuit.

The Arduino reads the sensor output and sends the corresponding measurement to the Python application.

Voltage and current measurements can be used together to observe the electrical behavior of the test condition.

🖥️ Python HMI

The Python application provides the software interface for monitoring and documenting the test.

Main Functions
Connect to Arduino UNO
Start and stop testing
Display current measurements
Display voltage measurements
Monitor test status
Display trip status
Plot current graphs
Store measurement data
Generate test reports
📊 Current Measurement Graphs

During testing, the system records current measurements over time.

The Python application uses the recorded data to generate graphs that show the current behavior during the test.

Current
  │
  │             ┌──────────
  │           /
  │         /
  │________/________________ Time
           ↑
      Test / Trip Event

These graphs provide a visual representation of how the current changes during the test.

⏱️ Trip-Time Measurement

VOLTRA records the time from the beginning of the test until the trip condition is detected.

Test Start
    ↓
Current Measurement
    ↓
Continuous Monitoring
    ↓
Trip Detection
    ↓
Test Power OFF
    ↓
Trip-Time Calculation

The calculated trip time is stored along with the corresponding test data.

🛑 Trip Detection & Automatic Shutdown

The system continuously monitors the test condition.

When the trip condition is detected, the controller activates the shutdown sequence.

Trip Detected
     ↓
Main Power Relay OFF
     ↓
Test Stopped
     ↓
Trip Time Recorded
     ↓
Data Sent to Python

This helps prevent unnecessary continuation of the test after the trip event.

📄 Automated Report Generation

After completing a test, the Python application generates a structured report containing relevant test information.

Report Information
Test identification
Selected resistance
Measured current
Measured voltage
Trip status
Trip time
Current measurement graph
Test data
Date and time

The report generation process reduces manual documentation and provides a consistent record of the test.

🔐 Safety Features

Safety is considered throughout the VOLTRA prototype design.

Safety-Oriented Features
Main power relay
Controlled resistance selection
Automatic shutdown
Trip detection
Sensor monitoring
Emergency stop concept
Fault handling
Low-voltage/current-limited prototype setup
Automatic Shutdown Conditions
MCB / Trip Condition
        OR
STOP Command
        OR
Emergency Stop
        OR
Sensor Fault
        OR
System Fault
        ↓
   POWER OFF
        ↓
   TEST STOPPED

Safety Notice: The prototype should only be operated with appropriate electrical protection, supervision, insulation, and controlled low-voltage test conditions.

🧪 Testing & Validation

VOLTRA is evaluated through both hardware testing and Proteus simulation.

Hardware Testing

The prototype testing includes:

Arduino UNO operation
Relay operation
LED indication
Push-button operation
ACS712 current sensing
Voltage measurement
Resistance selection
Test-path switching
Trip detection
Automatic shutdown
Serial communication
Python monitoring
Current graph generation
Report generation
Proteus Simulation

A Proteus simulation is used to demonstrate the circuit design and control logic.

The simulation provides an additional method for verifying the proposed system architecture before or alongside hardware testing.

🧩 Software Workflow
                   Arduino UNO
                       │
          ┌────────────┼────────────┐
          ↓            ↓            ↓
     Read Current   Read Voltage   Inputs
          │            │            │
          └────────────┼────────────┘
                       ↓
                  Relay Control
                       ↓
                  Trip Detection
                       ↓
                Serial Communication
                       │
                       ↓
                   Python HMI
                       │
          ┌────────────┼────────────┐
          ↓            ↓            ↓
     Live Data      Graphs      Test Report
🔄 Complete System Operation
Step 1 – System Initialization

The Arduino UNO initializes the sensors, relays, LEDs, push buttons, and serial communication.

Step 2 – Test Selection

The required test condition and resistance path are selected.

Step 3 – Resistance Selection

The Arduino activates the appropriate relay to select the 82Ω or 20Ω test path.

Step 4 – Test Activation

The main power relay activates the test circuit.

Step 5 – Measurement

The ACS712 measures current while the voltage sensor monitors the test voltage.

Step 6 – Continuous Monitoring

The Arduino continuously monitors the electrical parameters and test status.

Step 7 – Trip Detection

The system detects the trip condition.

Step 8 – Automatic Shutdown

The main power relay is switched OFF and the test is stopped.

Step 9 – Trip-Time Calculation

The time between test initiation and trip detection is calculated.

Step 10 – Data Logging

Current, voltage, test condition, trip status, and timing information are recorded.

Step 11 – Visualization

The Python application displays the recorded measurements and generates current graphs.

Step 12 – Report Generation

The final test information and graphs are compiled into a structured report.

📁 Repository Structure
SIH2026_VOLTRA/
│
├── README.md
│
├── Arduino/
│   └── VOLTRA_Arduino_Code.ino
│
├── Python/
│   ├── main.py
│   ├── serial_communication.py
│   ├── data_processing.py
│   ├── visualization.py
│   └── report_generation.py
│
├── Simulation/
│   ├── VOLTRA_Proteus_Simulation.pdsprj
│   ├── Circuit_Image.png
│   └── Simulation_Demo.mp4
│
├── Hardware/
│   ├── Circuit_Diagram.png
│   ├── Hardware_Setup.jpg
│   └── Component_List.md
│
├── Presentation/
│   └── VOLTRA_Presentation.pptx
│
└── Documentation/
    ├── 01_Problem_Statement.md
    ├── 02_Solution.md
    ├── 03_Architecture.md
    ├── 04_Hardware_Design.md
    ├── 05_Software_Design.md
    ├── 06_Testing.md
    ├── 07_Safety.md
    ├── 08_Results.md
    └── 09_Future_Scope.md
🌟 Key Features
⚡ Automated test control
🔌 Relay-based resistance selection
📡 ACS712 current sensing
⚡ Voltage monitoring
📊 Current measurement graphs
⏱️ Automatic trip-time calculation
🛑 Automatic shutdown
💻 Python-based HMI
📁 Digital data logging
📄 Automated report generation
🧪 Proteus simulation
🔐 Safety-oriented control logic
🔄 Hardware-software integration
🚀 Future Scope

The VOLTRA prototype can be further developed with:

Higher-accuracy current sensing
Automated multi-level test sequences
Programmable resistance banks
Improved MCB status detection
Database-based test storage
Cloud-based data storage
Automated comparison with specified test limits
Advanced test analytics
Touchscreen HMI
Industrial-grade switching and protection
Calibration and measurement traceability
📚 Reference Standard

The project is developed with reference to:

IEC 60898-1:2015 – Electrical accessories – Circuit-breakers for overcurrent protection for household and similar installations.

The standard is used as a reference for understanding MCB testing concepts and requirements.

VOLTRA is not a certified IEC compliance testing system.

👥 Team
Team VOLTRA

Project:
Automated High-Current Short-Circuit Test System for IEC 60898-1:2015 MCB Compliance

Competition:
Smart India Hackathon 2026

⚠️ Disclaimer

VOLTRA is an educational prototype and engineering demonstrator developed to demonstrate automated sensing, control, timing, data acquisition, visualization, and reporting concepts.

It should not be considered a certified IEC compliance testing system and should not be used for commercial certification or unsafe high-energy electrical testing.

⭐ Project Vision

Sense → Control → Detect → Measure → Record → Report

VOLTRA demonstrates how an automated embedded system can transform a traditionally manual electrical testing workflow into a controlled, repeatable, measurable, and digitally documented process.