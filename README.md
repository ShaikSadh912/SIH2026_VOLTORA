# ⚡ SIH2026 – VOLTRA
### Automated High-Current Short-Circuit Test System for MCB Testing

**VOLTRA – Automated MCB Testing Platform**
An automated prototype for current measurement, trip detection, timing, data logging, and report generation.

---

## 📌 Project Overview

VOLTRA is an automated prototype developed to demonstrate the testing and monitoring of Miniature Circuit Breakers (MCBs) under controlled electrical conditions.

The system combines Arduino UNO, current and voltage sensing, relay-based load selection, automatic trip detection, timing, data acquisition, and a Python-based interface to simplify the testing process.

The project is developed as an educational and engineering demonstrator based on the concepts of **IEC 60898-1:2015**.

> ⚠️ **Note:** This prototype is intended for educational and demonstration purposes only. It is **not** a certified MCB compliance-testing system.

---

## 🎯 Problem Statement

Conventional MCB testing can involve manual setup, current measurement, observation of breaker operation, and recording of trip time.

This can make testing:

- Manual
- Time-consuming
- Difficult to monitor continuously
- Prone to human recording errors
- Less convenient for repeated testing

VOLTRA aims to demonstrate how these operations can be automated and digitally monitored.

---

## 💡 Proposed Solution

VOLTRA provides an automated testing workflow that:

1. Selects a predefined test condition
2. Applies the controlled electrical load
3. Measures the current through the circuit
4. Monitors the MCB/test status
5. Detects the trip condition
6. Automatically stops the test when required
7. Calculates the trip time
8. Records the measured data
9. Displays the test information
10. Generates a test report

---

## 🔄 System Workflow

```
        START
          │
          ▼
   Select Test Condition
          │
          ▼
   Controlled Load Applied
          │
          ▼
     Current Measurement
          │
          ▼
      MCB Monitoring
          │
          ▼
      Trip Detection
          │
     ┌────┴────┐
     │         │
   NO TRIP    TRIP
     │         │
     │         ▼
     │    Automatic Shutdown
     │         │
     └─────────┤
               ▼
        Trip-Time Calculation
               │
               ▼
          Data Logging
               │
               ▼
        Report Generation
```

---

## ✨ Key Features

- ⚡ **Automated Test Sequence**
- 🔌 **Arduino UNO-Based Control**
- 📊 **Real-Time Current Measurement**
- 📈 **Voltage Monitoring**
- 🔄 **Relay-Based Load Selection**
- ⏱️ **Automatic Trip-Time Calculation**
- 🚨 **Automatic Shutdown Logic**
- 💾 **Test Data Logging**
- 🖥️ **Python-Based Monitoring & Visualization**
- 📄 **Automated Report Generation**
- 🛡️ **Safety-Oriented Control Logic**
- 📋 **Structured Testing & Result Documentation**

---

## 🏗️ System Architecture

```
                 AC / Controlled Supply
                         │
                         ▼
                ┌─────────────────┐
                │  Main Power     │
                │     Relay       │
                └────────┬────────┘
                         │
                         ▼
                ┌─────────────────┐
                │ Relay-Controlled│
                │    Load Bank    │
                └────────┬────────┘
                         │
                         ▼
                ┌─────────────────┐
                │  ACS712 Current │
                │     Sensor      │
                └────────┬────────┘
                         │
                         ▼
                ┌─────────────────┐
                │   MCB / Test    │
                │      Path       │
                └────────┬────────┘
                         │
                         ▼
                ┌─────────────────┐
                │   Arduino UNO   │
                │ Control & Logic │
                └──────┬─────┬────┘
                       │     │
              ┌────────┘     └────────┐
              ▼                       ▼
       ┌─────────────┐        ┌─────────────┐
       │ Relay Control│       │ Status LEDs │
       └─────────────┘        └─────────────┘
                       │
                       ▼
                ┌─────────────────┐
                │Python Software  │
                │Visualization &  │
                │Report Generation│
                └─────────────────┘
```

---

## 🔧 Hardware Components

| Component | Purpose |
|---|---|
| **Arduino UNO** | Main controller |
| **ACS712 Current Sensor** | Current measurement |
| **Voltage Sensor** | Voltage monitoring |
| **Relay Module** | Load selection and switching |
| **20Ω Resistor Path** | Higher-current test condition |
| **82Ω Resistor Path** | Lower-current test condition |
| **Main Power Relay** | Overall power control |
| **MCB / Test Switching Path** | Trip monitoring demonstration |
| **LEDs** | Status indication |
| **Push Buttons** | User control |
| **12-0-12 V Transformer** | Low-voltage AC supply for prototype |
| **Breadboard & Wires** | Circuit connections |

---

## 💻 Software Architecture

### 🔹 Arduino UNO

The Arduino UNO handles the main hardware control and measurement tasks:

- Reads the ACS712 current sensor
- Reads voltage sensor values
- Controls relay outputs
- Selects the required load path
- Monitors test conditions
- Detects trip/status conditions
- Controls status LEDs
- Measures test duration
- Sends data to the Python application

### 🔹 Python Application

The Python software handles:

- Serial communication
- Data acquisition
- Real-time monitoring
- Current measurement graphs
- Trip-time display
- Data logging
- Result processing
- Automated report generation

---

## 📊 Measurement & Monitoring

### 🔹 Current Measurement

The **ACS712 current sensor** measures the current flowing through the selected test path.

The measured data is used for:

- Current monitoring
- Test-condition verification
- Trip detection support
- Graph generation
- Data logging

### 🔹 Voltage Measurement

The voltage sensor provides voltage information for monitoring the test supply.

### 🔹 Trip-Time Measurement

The system records the time between the start of the test and detection of the trip condition.

```
Test Start
    ↓
Load Applied
    ↓
Current Measurement
    ↓
Trip Condition Detected
    ↓
Automatic Shutdown
    ↓
Trip Time Calculated
```

---

## 🔄 Automatic Load Selection

The prototype uses relay-controlled load paths to demonstrate different test conditions.

```
                    Relay
                      │
             ┌────────┴────────┐
             │                 │
             ▼                 ▼
          82Ω Path           20Ω Path
             │                 │
             ▼                 ▼
       Lower Current       Higher Current
             │                 │
             ▼                 ▼
       Normal Condition    Trip Indication
```

---

## 🚨 Safety & Protection

Safety is an important part of the VOLTRA prototype.

The system is designed to provide automatic shutdown when an abnormal or unsafe condition is detected.

### Automatic Shutdown Conditions

```
MCB Trip
   OR
STOP Command
   OR
Emergency Stop
   OR
Sensor Fault
   OR
System Fault
        │
        ▼
Automatic Power Shutdown
```

---

## 🧪 Testing Process

### 1. Sensor Testing

- Verify voltage sensor readings
- Verify ACS712 current readings
- Check measurement stability

### 2. Relay Testing

- Verify relay operation
- Check load-path selection
- Verify main power switching

### 3. Functional Testing

- Start the test
- Select the required load
- Apply the test condition
- Monitor current
- Detect trip/status condition
- Stop the test automatically

### 4. Data Testing

- Record current values
- Generate current graphs
- Calculate trip time
- Store test results

### 5. Report Testing

- Process measured data
- Generate result summary
- Generate automated test report

---

## 📈 Results

The prototype demonstrates an automated workflow for:

- ⚡ **Controlled test initiation**
- 🔄 **Load selection**
- 📊 **Current sensing**
- 📈 **Voltage monitoring**
- 🚨 **Trip/status detection**
- 🛑 **Automatic shutdown**
- ⏱️ **Trip-time measurement**
- 💾 **Data logging**
- 📊 **Graph visualization**
- 📄 **Automated report generation**

The project demonstrates how **embedded control, sensing, timing, data acquisition, visualization, and automated reporting** can be integrated into a single testing platform.

---

## 📁 Repository Structure

```
SIH2026_VOLTRA/
│
├── README.md
│
├── 01_Problem_Statement.md
├── 02_Solution.md
├── 03_Architecture.md
├── 04_Hardware_Design.md
├── 05_Software_Design.md
├── 06_Testing.md
├── 07_Safety.md
├── 08_Results.md
├── 09_Future_Scope.md
│
├── Arduino/
│   └── VOLTRA_Arduino_Code.ino
│
├── Python/
│   ├── main.py
│   ├── data_logger.py
│   ├── visualization.py
│   └── report_generator.py
│
├── Simulation/
│   ├── Proteus_Circuit_Simulation
│   ├── Simulation_Video
│   └── Circuit_Photos
│
└── Presentation/
    └── VOLTRA_Presentation
```

---

## 🔮 Future Scope

The VOLTRA platform can be further enhanced with:

- 🔹 **Advanced automated test sequences**
- 🔹 **Multiple MCB test profiles**
- 🔹 **Improved current measurement accuracy**
- 🔹 **Real-time dashboard**
- 🔹 **Cloud-based data storage**
- 🔹 **Remote monitoring**
- 🔹 **Automated test comparison**
- 🔹 **Advanced data analytics**
- 🔹 **Enhanced protection mechanisms**
- 🔹 **Professional test-report formats**

---

## 📚 Reference

The project is developed with reference to:

**IEC 60898-1:2015**
*Electrical accessories – Circuit-breakers for overcurrent protection for household and similar installations.*

The standard is used as a **technical reference for understanding MCB testing concepts**.

---

## 👥 Team

### Team VOLTRA
**Smart India Hackathon 2026**

---

<p align="center"><b>Automate. Measure. Detect. Analyze. Report.</b></p>