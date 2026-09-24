# ⚡ VOLTRA
## Automated MCB Testing & Monitoring Platform

<p align="center">

**Smart India Hackathon 2026**

### 🔌 Automating Electrical Testing with Embedded Systems, Sensing & Data Analytics

</p>

---

## 🚀 Project Overview

**VOLTRA** is an automated prototype platform developed to demonstrate the **testing, monitoring, trip detection, timing, data acquisition, and automated reporting of Miniature Circuit Breakers (MCBs).**

The system combines an **Arduino UNO**, **current and voltage sensing**, **relay-based resistance selection**, and a **Python monitoring application** to create an automated testing workflow.

Instead of manually performing each testing step, VOLTRA demonstrates how the process can be integrated into a single automated system.

> ⚠️ **Educational Prototype:** VOLTRA is developed as a college-level demonstrator based on concepts referenced in **IEC 60898-1:2015**. It is not a certified compliance-testing system.

---

## 🎯 The Problem

Traditional electrical protection testing can involve several manual activities:

- Manual test-condition selection
- Manual measurement and observation
- Manual trip-time recording
- Manual result documentation
- Difficulty in maintaining consistent test records

These processes can make testing **time-consuming and dependent on manual observation**.

### 💡 Our Approach

VOLTRA introduces an automated workflow that combines:

**Control → Measurement → Monitoring → Trip Detection → Timing → Data Logging → Visualization → Reporting**

---

# ⚙️ How VOLTRA Works

```text
             ┌──────────────────┐
             │      USER        │
             │   Python HMI     │
             └────────┬─────────┘
                      │
                      ▼
             ┌──────────────────┐
             │   ARDUINO UNO    │
             │  Control System  │
             └────────┬─────────┘
                      │
        ┌─────────────┼─────────────┐
        │             │             │
        ▼             ▼             ▼
   ┌─────────┐   ┌─────────┐   ┌─────────┐
   │ RELAYS  │   │ ACS712  │   │ VOLTAGE │
   │         │   │ CURRENT │   │ SENSOR  │
   └────┬────┘   │ SENSOR  │   └────┬────┘
        │        └────┬────┘        │
        │             │             │
        ▼             ▼             ▼
   ┌────────────────────────────────────┐
   │       CONTROLLED TEST CIRCUIT      │
   └──────────────────┬─────────────────┘
                      │
                      ▼
              ┌───────────────┐
              │ TRIP / STATUS │
              │   DETECTION   │
              └───────┬───────┘
                      │
                      ▼
              ┌───────────────┐
              │ AUTO SHUTDOWN │
              └───────┬───────┘
                      │
                      ▼
              ┌───────────────┐
              │ DATA LOGGING  │
              │   & GRAPHS    │
              └───────┬───────┘
                      │
                      ▼
              ┌───────────────┐
              │ AUTO REPORT   │
              │  GENERATION   │
              └───────────────┘
🔄 Complete Testing Workflow
START
  │
  ▼
Initialize System
  │
  ▼
Select Test Condition
  │
  ▼
Activate Required Relay
  │
  ▼
Apply Test Supply
  │
  ▼
Measure Current & Voltage
  │
  ▼
Monitor Test Status
  │
  ├───────────────┐
  │               │
  ▼               ▼
Normal         Trip Detected
  │               │
  │               ▼
  │        Stop Test Supply
  │               │
  │               ▼
  │        Calculate Trip Time
  │               │
  └───────┬───────┘
          ▼
    Store Test Data
          │
          ▼
    Generate Graphs
          │
          ▼
    Generate Report
          │
          ▼
         END
✨ Key Features
Feature	Description
🎛️ Automated Control	Arduino UNO controls the complete test sequence
🔀 Automatic Resistance Selection	Relay module selects the required test path
📊 Current Measurement	ACS712 continuously monitors test current
⚡ Voltage Monitoring	Voltage sensor monitors the test supply
🔴 Trip Detection	System identifies the test/MCB trip condition
⏱️ Trip-Time Measurement	Automatically calculates the elapsed trip time
🛑 Automatic Shutdown	Test supply is disconnected after trip/fault detection
📈 Real-Time Graphs	Current measurements can be visualized through Python
💾 Data Logging	Test measurements are recorded for analysis
📄 Report Generation	Test results can be converted into an automated report
🧪 Proteus Simulation	Circuit operation is verified through simulation
🔧 Hardware
Main Components
Component	Function
Arduino UNO	Main controller
ACS712	Current measurement
Voltage Sensor	Voltage measurement
Relay Module	Resistance-path selection
Main Power Relay	Test-power switching
Resistance Bank	Controlled test-load selection
LEDs	System status indication
Push Buttons	User control
Buzzer	Audible indication
MCB / Switching Arrangement	Trip-status demonstration
Transformer / Low-Voltage Supply	Controlled test supply
Breadboard & Wires	Prototype interconnection
🔀 Automatic Resistance Selection

VOLTRA uses relay-controlled resistance paths to demonstrate different test-current conditions.

Current Prototype Configuration
          Relay Module
               │
       ┌───────┴───────┐
       │               │
       ▼               ▼
    82 Ω Path       20 Ω Path
       │               │
       ▼               ▼
 Low-Current       Higher-Current
  Condition          Condition
Resistance Configuration
82 Ω → Low-current test condition
20 Ω → Higher-current test condition
20 Ω is implemented using two 10 Ω resistors in series

The Arduino controls the relay to select the required resistance path automatically.

🧠 Arduino UNO Control

The Arduino UNO acts as the central controller of VOLTRA.

Controller Responsibilities
Sensor Reading
      ↓
Condition Monitoring
      ↓
Relay Control
      ↓
Test Sequencing
      ↓
Trip Detection
      ↓
Timing
      ↓
Safety Shutdown
      ↓
Data Transmission

The controller manages the interaction between the sensing, switching, test circuit, and software interface.

📡 Current & Voltage Measurement
ACS712 Current Sensor

The ACS712 measures the current flowing through the test circuit.

The measured data can be used for:

Current monitoring
Test-condition verification
Trip detection
Graph generation
Data logging
Report generation
Voltage Sensor

The voltage sensor provides monitoring of the test supply and allows the system to record the applied test condition.

💻 Software

VOLTRA combines Arduino firmware with a Python-based monitoring and reporting system.

Arduino Firmware

Responsible for:

Sensor acquisition
Relay control
Test sequencing
Trip detection
Timing
LED/buzzer control
Main power control
Serial communication
Python Application

Responsible for:

Receiving Arduino data
Displaying measurements
Monitoring test status
Plotting current graphs
Logging test data
Processing measurements
Generating test reports
📈 Data Visualization

The Python application can visualize the collected electrical measurements.

Example Data Flow
Arduino
   │
   │ Serial Data
   ▼
Python Application
   │
   ├── Current Data
   ├── Voltage Data
   ├── Trip Status
   └── Timing Data
          │
          ▼
     Data Processing
          │
          ▼
      Graphs + Logs

This allows the test process to be observed and analyzed rather than relying only on manual readings.

📄 Automated Report Generation

After a test is completed, the collected measurements can be processed into a structured report.

Report Information
Test identification
Selected resistance
Current measurements
Voltage measurements
Current graph
Trip status
Trip time
Test result
Date and time
Test summary
Workflow
Test Data
    ↓
Data Processing
    ↓
Measurement Graphs
    ↓
Result Calculation
    ↓
Automated Report
🛡️ Safety-Oriented Design

Safety is incorporated into the prototype through controlled switching and automatic shutdown logic.

Shutdown Conditions
       ┌─────────────────┐
       │  Trip Detected  │
       └────────┬────────┘
                │
       ┌────────▼────────┐
       │                 │
       │  AUTO SHUTDOWN  │
       │                 │
       └────────┬────────┘
                │
     ┌──────────┼──────────┐
     ▼          ▼          ▼
   STOP      E-STOP     SENSOR /
  COMMAND              SYSTEM FAULT

Safety-oriented features include:

Controlled test supply
Relay-based switching
Automatic shutdown
Emergency-stop provision
Protection/fuse arrangement
Sensor-fault handling
System-fault handling
Controlled resistance selection
🧪 Testing & Validation

Testing is performed at multiple levels.

🔹 Hardware Testing
Arduino UNO
Relay module
ACS712
Voltage sensor
LEDs
Buzzer
Resistance paths
Main power relay
🔹 Software Testing
Sensor data acquisition
Relay control
Trip detection
Timing calculation
Serial communication
Data logging
Graph generation
Report generation
🔹 System Testing

The complete workflow is validated as:

Test Start
    ↓
Resistance Selection
    ↓
Current Measurement
    ↓
Test Monitoring
    ↓
Trip Detection
    ↓
Automatic Shutdown
    ↓
Trip-Time Calculation
    ↓
Data Logging
    ↓
Graph Generation
    ↓
Report Generation
🧪 Proteus Simulation

A Proteus simulation is included to demonstrate and verify the circuit and control logic before/alongside hardware implementation.

The simulation section contains:

Proteus project
Circuit image
Simulation demonstration video
📁 Repository Structure
SIH2026_VOLTRA/
│
├── 📄 README.md
│
├── 📄 01_Problem_Statement.md
├── 📄 02_Solution.md
├── 📄 03_Architecture.md
├── 📄 04_Hardware_Design.md
├── 📄 05_Software_Design.md
├── 📄 06_Testing.md
├── 📄 07_Safety.md
├── 📄 08_Results.md
├── 📄 09_Future_Scope.md
│
├── 🔧 Arduino/
│   └── Arduino_Code.ino
│
├── 💻 Python/
│   ├── main.py
│   ├── data_logging.py
│   ├── graph.py
│   └── report_generation.py
│
├── 🧪 Simulation/
│   ├── Proteus_Project
│   ├── Circuit_Image
│   └── Simulation_Video
│
└── 🎤 Presentation/
    └── Project_Presentation.pptx
📊 Project Output

VOLTRA demonstrates an integrated automated testing workflow capable of:

              ┌────────────────────┐
              │ Automated Testing  │
              └─────────┬──────────┘
                        │
        ┌───────────────┼───────────────┐
        ▼               ▼               ▼
   Measurement      Trip Detection    Timing
        │               │               │
        └───────────────┼───────────────┘
                        ▼
                  Data Logging
                        │
                        ▼
                   Visualization
                        │
                        ▼
                 Report Generation
🌱 Future Scope

The prototype can be further enhanced with:

Advanced trip-characteristic analysis
Higher-current controlled test stages
Industrial-grade switching components
More accurate calibrated sensors
Database-based test-data management
Web-based monitoring
Remote monitoring
Automated multi-test sequences
Enhanced fault detection
Advanced report generation
Integration with laboratory test equipment
Compliance-oriented validation
📚 Reference
IEC 60898-1:2015

Electrical accessories – Circuit-breakers for overcurrent protection for household and similar installations.

The standard is used as a technical reference for understanding MCB testing concepts and requirements.

Important: VOLTRA is an educational prototype and does not constitute certified compliance testing.

👥 Team VOLTRA
Smart India Hackathon 2026

VOLTRA focuses on combining:

⚡ Electrical Engineering
        +
🔌 Embedded Systems
        +
📡 Sensor Technology
        +
🤖 Automation
        +
💻 Python Software
        +
📊 Data Visualization
        +
📄 Automated Reporting

to demonstrate a modern approach to automated electrical testing.

⭐ VOLTRA at a Glance
Category	Implementation
Controller	Arduino UNO
Current Sensor	ACS712
Voltage Measurement	Voltage Sensor
Switching	Relay Module
Test Resistance	82 Ω / 20 Ω
Monitoring	Python HMI
Visualization	Current Measurement Graphs
Data Handling	Automated Data Logging
Reporting	Automated Report Generation
Simulation	Proteus
Reference	IEC 60898-1:2015
Purpose	Educational Demonstrator
<p align="center">
⚡ VOLTRA
Measure. Monitor. Detect. Automate. Report.

SIH 2026 | Automated MCB Testing & Monitoring