# ⚡ VOLTRA – Automated MCB Testing Platform

### Automated High-Current Short-Circuit Test System for IEC 60898-1:2015 MCB Compliance

**SIH 2026 Project | Team: VOLTRA**

---

## 📌 Project Overview

**VOLTRA** is an automated MCB testing and monitoring platform designed to demonstrate the principles of **overcurrent testing, trip detection, measurement, timing, data logging, and automated reporting**.

The system uses an **Arduino UNO**, current and voltage sensors, relay-controlled resistance selection, and a Python-based monitoring interface to automate the complete testing workflow.

> **Note:** This project is an educational prototype/demonstrator and is **not intended for actual IEC compliance certification or commercial MCB testing**.

---

## 🎯 Problem Statement

Manual testing of Miniature Circuit Breakers (MCBs) can require repeated measurements, manual timing, and result recording.

The objective of VOLTRA is to develop a compact automated system that can:

* Generate controlled test conditions
* Measure the test current
* Monitor the MCB/test path
* Detect the trip condition
* Measure trip time automatically
* Shut down the test safely
* Store test data
* Display current measurements and graphs
* Generate a test report

---

## 💡 Proposed Solution

VOLTRA combines hardware sensing, relay-based control, Arduino processing, and Python visualization into a single automated testing workflow.

### System Workflow

```text
START
  ↓
Select Test Resistance
  ↓
Apply Controlled Test
  ↓
Measure Current & Voltage
  ↓
Monitor MCB/Test Status
  ↓
Detect Trip Condition
  ↓
Automatic Shutdown
  ↓
Calculate Trip Time
  ↓
Store Test Data
  ↓
Generate Graphs & Report
```

---

## 🏗️ System Architecture

```text
                  ┌─────────────────────┐
                  │      Python HMI     │
                  │ Monitoring & Report │
                  └──────────┬──────────┘
                             │
                             │ Serial
                             ↓
                  ┌─────────────────────┐
                  │     Arduino UNO     │
                  │ Control & Processing│
                  └──────┬───────┬──────┘
                         │       │
             ┌───────────┘       └────────────┐
             ↓                                ↓
      ┌─────────────┐                  ┌─────────────┐
      │ Relay Module│                  │ ACS712      │
      │ Resistance  │                  │ Current     │
      │ Selection   │                  │ Sensor      │
      └──────┬──────┘                  └──────┬──────┘
             │                                │
             ↓                                ↓
      ┌─────────────┐                  ┌─────────────┐
      │ Test Load / │                  │ Voltage     │
      │ Resistance  │                  │ Sensor      │
      └─────────────┘                  └─────────────┘
```

---

## 🔧 Hardware Components

| Component             | Purpose                                  |
| --------------------- | ---------------------------------------- |
| Arduino UNO           | Main controller                          |
| ACS712                | Current measurement                      |
| Voltage Sensor        | Voltage monitoring                       |
| Relay Module          | Automatic test-path/resistance selection |
| 10Ω Resistor          | Higher-current test path                 |
| 20Ω Resistance        | Higher-current test path                 |
| 82Ω Resistor          | Lower-current test path                  |
| LEDs                  | System and trip indication               |
| Push Buttons          | User control                             |
| Main Power Relay      | Test power switching                     |
| 12-0-12 V Transformer | Low-voltage AC test source               |
| Breadboard & Wires    | Prototype connections                    |
| Buzzer                | Status/alert indication                  |

---

## ⚙️ Automatic Resistance Selection

VOLTRA uses relay-controlled resistance selection to create different test conditions.

### Example Test Paths

| Resistance | Expected Condition                  |
| ---------- | ----------------------------------- |
| **82Ω**    | Lower current / normal condition    |
| **20Ω**    | Higher current / trip demonstration |
| **10Ω**    | Higher-current test path            |

The relay module allows the Arduino to automatically switch between different resistance paths based on the selected test mode.

---

## 📡 Current Measurement

The **ACS712 current sensor** measures the current flowing through the test circuit.

The measured current is obtained from the sensor output and processed by the Arduino.

The Arduino sends the measured values to the Python application through serial communication.

The Python interface can display:

* Real-time current
* Current variation
* Test status
* Trip event
* Trip time
* Recorded test data

---

## 🖥️ Python HMI

The Python software provides a user-friendly monitoring interface for the hardware system.

### Main Functions

* Connect to Arduino
* Start/stop test
* Display measured current
* Display voltage
* Monitor test status
* Detect trip events
* Plot current measurements
* Record test data
* Generate test reports

---

## 📊 Data Visualization

During testing, VOLTRA records the measured electrical parameters.

The software can generate graphs such as:

```text
Current
  │
  │          ┌────────────
  │         /
  │        /
  │_______/________________ Time
          ↑
       Test Event
```

The current measurement graph helps visualize the behavior of the test condition over time.

---

## ⏱️ Trip-Time Measurement

When a trip condition is detected, the system records the time between test initiation and trip detection.

```text
Test Start
    ↓
Current Measurement
    ↓
Trip Detection
    ↓
Test Stop
    ↓
Trip Time Calculation
```

The calculated trip time can then be stored along with the corresponding test data.

---

## 📄 Automated Report Generation

After completing a test, the Python software can generate a structured test report containing:

* Test identification
* Test condition
* Resistance selected
* Measured current
* Measured voltage
* Trip status
* Trip time
* Current graph
* Test result
* Date/time information

This reduces manual data recording and provides a consistent format for documenting tests.

---

## 🔐 Safety Features

Safety is an important part of the VOLTRA prototype.

The system includes:

* Main power relay
* Relay-controlled test path
* Fuse/protection considerations
* Emergency stop concept
* Automatic shutdown
* MCB/test-status monitoring
* Sensor fault detection
* System fault handling

### Automatic Shutdown Conditions

```text
MCB/Test Trip
     OR
STOP Command
     OR
Emergency Stop
     OR
Sensor Fault
     OR
System Fault
        ↓
Test Power OFF
```

> **Safety Notice:** The prototype should only be operated with appropriate electrical protection, supervision, insulation, and low-voltage/current-limited test conditions.

---

## 🧪 Testing & Validation

The project is validated through both hardware testing and simulation.

### Hardware Testing

The hardware testing includes:

* Relay operation
* LED indication
* Current sensor testing
* Voltage measurement
* Resistance selection
* Test-path switching
* Trip detection
* Automatic shutdown
* Serial communication
* Python monitoring
* Report generation

### Simulation

A **Proteus simulation** is used to demonstrate the circuit architecture and control logic before and alongside hardware implementation.

---

## 🧩 Software Workflow

```text
Arduino
   │
   ├── Read Current
   ├── Read Voltage
   ├── Monitor Inputs
   ├── Control Relays
   ├── Detect Trip
   └── Send Data
          │
          ↓
   Serial Communication
          │
          ↓
      Python HMI
          │
     ┌────┼────┐
     ↓    ↓    ↓
   Graph Data Report
```

---

## 🔄 Complete System Operation

### Step 1 – System Initialization

Arduino initializes sensors, relays, LEDs, buttons, and serial communication.

### Step 2 – Test Selection

The required test condition and resistance path are selected.

### Step 3 – Relay Activation

The corresponding relay activates the selected resistance path.

### Step 4 – Measurement

The ACS712 measures current and the voltage sensor monitors the test voltage.

### Step 5 – Monitoring

Arduino continuously monitors the test condition.

### Step 6 – Trip Detection

The system detects the MCB/test trip condition.

### Step 7 – Automatic Shutdown

The main power relay is switched OFF to terminate the test.

### Step 8 – Trip-Time Calculation

The software calculates the time between test initiation and trip detection.

### Step 9 – Data Logging

The measured values and test information are stored.

### Step 10 – Report Generation

The Python application generates graphs and a structured test report.

---

## 📁 Repository Structure

```text
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
```

---

## 🌟 Key Features

* ⚡ Automated test control
* 🔌 Relay-based resistance selection
* 📡 ACS712 current sensing
* 📊 Real-time measurement visualization
* ⏱️ Automatic trip-time calculation
* 🛑 Automatic shutdown
* 💻 Python-based HMI
* 📈 Current measurement graphs
* 📄 Automated report generation
* 🧪 Proteus simulation
* 🔐 Safety-oriented control logic
* 📁 Digital test-data logging

---

## 🚀 Future Scope

The prototype can be extended with:

* Higher-accuracy current sensing
* Automated multi-level test sequences
* Larger programmable resistance banks
* Improved MCB status detection
* Cloud-based test-data storage
* Automatic comparison with specified test limits
* Database integration
* Advanced test analytics
* Touchscreen HMI
* Industrial-grade switching and protection
* Calibration and traceability features

---

## 📚 Reference Standard

The project is developed with reference to:

**IEC 60898-1:2015 – Electrical accessories – Circuit-breakers for overcurrent protection for household and similar installations.**

The standard is used as a conceptual reference for understanding MCB testing requirements.

---

## 👥 Team

### **Team VOLTRA**

**Project:**
**Automated High-Current Short-Circuit Test System for IEC 60898-1:2015 MCB Compliance**

**Competition:**
**Smart India Hackathon 2026**

---

## ⚠️ Disclaimer

VOLTRA is an **educational prototype and engineering demonstrator** developed to demonstrate automated sensing, control, timing, data acquisition, visualization, and reporting concepts.

It should **not be considered a certified IEC compliance testing system** and should not be used for commercial certification or unsafe high-energy electrical testing.

---

## ⭐ Project Vision

> **Sense → Control → Detect → Measure → Record → Report**

VOLTRA demonstrates how an automated embedded system can transform a traditionally manual electrical testing workflow into a **safer, repeatable, measurable, and digitally documented process**.
