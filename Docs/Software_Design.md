# ⚙️ Software Design

## Automated MCB Test System

> **Project:** Automated High-Current Short-Circuit Test System for IEC 60898-1:2015 MCB Compliance
> **Prototype:** Low-Voltage Functional Demonstrator
> **Software Layer:** Microcontroller Firmware + Python Supervisory Application

---

## 📌 1. Overview

The software forms the **control, monitoring, data acquisition, and reporting layer** of the Automated MCB Test System.

It connects the physical test hardware with a Python-based supervisory application. The software coordinates the test sequence, controls resistance selection, acquires electrical measurements, monitors the MCB state, records test data, and presents the results to the operator.

### Primary Software Functions

| Function               | Purpose                                         |
| ---------------------- | ----------------------------------------------- |
| 🎛️ Test Control       | Controls the automated test sequence            |
| 🔌 Relay Control       | Selects the required test resistance            |
| 📊 Current Measurement | Acquires current through ACS712                 |
| 📈 Voltage Measurement | Acquires voltage through LM10B                  |
| 🔍 MCB Monitoring      | Detects the MCB operating state                 |
| 🔄 Communication       | Exchanges commands and data with the controller |
| 💾 Data Logging        | Stores test measurements                        |
| 🧮 Data Processing     | Converts and processes raw measurements         |
| 📋 Result Evaluation   | Determines the defined test outcome             |
| 📄 Report Generation   | Creates a documented test report                |
| 🖥️ GUI                | Provides operator control and visualization     |
| ⚠️ Error Handling      | Detects and handles abnormal conditions         |

---

# 🏗️ 2. Software Architecture

The software is divided into two primary layers:

### Layer 1 — Microcontroller Firmware

The Arduino/ESP32 provides the **real-time hardware interface**.

It is responsible for:

* Relay control
* Resistance selection
* Sensor acquisition
* MCB status monitoring
* Hardware-level control
* Serial communication

### Layer 2 — Python Application

The Python application provides the **supervisory control and user interface**.

It is responsible for:

* Test configuration
* Test sequencing
* Real-time monitoring
* Data processing
* Data logging
* Result evaluation
* GUI operation
* Report generation

### High-Level Architecture

```text
                         ┌───────────────────────────┐
                         │       PYTHON GUI          │
                         │                           │
                         │  Test Configuration       │
                         │  Measurements             │
                         │  Status & Results         │
                         └─────────────┬─────────────┘
                                       │
                                       ▼
                         ┌───────────────────────────┐
                         │     TEST CONTROLLER       │
                         │                           │
                         │  Sequence Management      │
                         │  Test State Management    │
                         └─────────────┬─────────────┘
                                       │
                                       ▼
                         ┌───────────────────────────┐
                         │   SERIAL COMMUNICATION    │
                         └─────────────┬─────────────┘
                                       │
                                       ▼
                    ┌────────────────────────────────────┐
                    │          ARDUINO / ESP32            │
                    │                                    │
                    │  GPIO Control                       │
                    │  Sensor Acquisition                 │
                    │  Relay Control                      │
                    │  MCB Monitoring                     │
                    └──────────┬─────────────┬────────────┘
                               │             │
                    ┌──────────┘             └──────────┐
                    ▼                                   ▼
             ┌─────────────┐                    ┌─────────────┐
             │ RELAY BANK  │                    │   SENSORS   │
             │             │                    │             │
             │ 10 Ω        │                    │ ACS712      │
             │ 20 Ω        │                    │ LM10B       │
             │ 50 Ω        │                    │             │
             └──────┬──────┘                    └──────┬──────┘
                    │                                  │
                    └──────────────┬───────────────────┘
                                   ▼
                           ┌───────────────┐
                           │ MCB UNDER TEST│
                           └───────────────┘
```

---

# 🧩 3. Software Module Design

The software follows a **modular architecture**.

Each major function is implemented as an independent module.

```text
                    SOFTWARE SYSTEM
                          │
        ┌─────────────────┼─────────────────┐
        │                 │                 │
        ▼                 ▼                 ▼
       GUI          TEST CONTROLLER    COMMUNICATION
        │                 │                 │
        └─────────────────┼─────────────────┘
                          │
              ┌───────────┼───────────┐
              │           │           │
              ▼           ▼           ▼
          SENSOR       RELAY       MCB STATUS
        ACQUISITION    CONTROL      MONITOR
              │           │           │
              └───────────┼───────────┘
                          ▼
                  DATA PROCESSING
                          │
                          ▼
                  RESULT EVALUATION
                          │
                 ┌────────┴────────┐
                 ▼                 ▼
            DATA LOGGER       REPORT GENERATOR
```

### Module Responsibilities

| Module               | Responsibility                             |
| -------------------- | ------------------------------------------ |
| `GUI`                | User interaction and visualization         |
| `Test Controller`    | Controls the complete test sequence        |
| `Communication`      | PC ↔ Microcontroller communication         |
| `Sensor Acquisition` | Receives and processes sensor measurements |
| `Relay Control`      | Controls resistance selection              |
| `MCB Monitor`        | Monitors MCB operating state               |
| `Data Processing`    | Filters and validates measurements         |
| `Data Logger`        | Stores test data                           |
| `Result Evaluator`   | Evaluates defined test criteria            |
| `Report Generator`   | Creates test documentation                 |
| `Error Handler`      | Handles abnormal conditions                |

---

# 🔄 4. System Operating Flow

The software follows a controlled sequence from system initialization to report generation.

```text
                         ┌───────────┐
                         │   START   │
                         └─────┬─────┘
                               ▼
                    ┌────────────────────┐
                    │ Initialize System  │
                    └─────────┬──────────┘
                              ▼
                    ┌────────────────────┐
                    │ Connect Controller │
                    └─────────┬──────────┘
                              ▼
                    ┌────────────────────┐
                    │ Hardware Check     │
                    └─────────┬──────────┘
                              ▼
                    ┌────────────────────┐
                    │ Configure Test     │
                    │ Parameters         │
                    └─────────┬──────────┘
                              ▼
                    ┌────────────────────┐
                    │ Select Resistance  │
                    └─────────┬──────────┘
                              ▼
                    ┌────────────────────┐
                    │    START TEST      │
                    └─────────┬──────────┘
                              ▼
                    ┌────────────────────┐
                    │ Acquire Data       │
                    │ Voltage + Current  │
                    └─────────┬──────────┘
                              ▼
                    ┌────────────────────┐
                    │ Monitor MCB        │
                    └─────────┬──────────┘
                              ▼
                       ┌──────────────┐
                       │ MCB Tripped? │
                       └──────┬───────┘
                         NO   │   YES
                         │    │
                         ▼    ▼
                      Continue  Record Event
                         │        │
                         └────┬───┘
                              ▼
                       ┌────────────┐
                       │ Stop Test  │
                       └─────┬──────┘
                             ▼
                      ┌─────────────┐
                      │ Process Data│
                      └──────┬──────┘
                             ▼
                      ┌─────────────┐
                      │ Evaluate    │
                      │ Result      │
                      └──────┬──────┘
                             ▼
                      ┌─────────────┐
                      │ Save Data   │
                      └──────┬──────┘
                             ▼
                      ┌─────────────┐
                      │ Generate    │
                      │ Report      │
                      └──────┬──────┘
                             ▼
                         ┌───────┐
                         │  END  │
                         └───────┘
```

---

# 🎛️ 5. Test Control Logic

The **Test Controller** is the central software component.

It manages the current state of the test and ensures that operations occur in the correct sequence.

### Test States

```text
IDLE
  │
  ▼
CONNECTING
  │
  ▼
READY
  │
  ▼
CONFIGURING
  │
  ▼
RUNNING
  │
  ├──────────────► STOPPED
  │
  ├──────────────► TRIPPED
  │
  ├──────────────► ERROR
  │
  ▼
COMPLETED
  │
  ▼
IDLE
```

### State Descriptions

| State         | Description                          |
| ------------- | ------------------------------------ |
| `IDLE`        | System waiting for user action       |
| `CONNECTING`  | Establishing controller connection   |
| `READY`       | System ready for testing             |
| `CONFIGURING` | Test parameters are being configured |
| `RUNNING`     | Test is actively running             |
| `TRIPPED`     | MCB trip detected                    |
| `STOPPED`     | Test stopped by operator             |
| `ERROR`       | Abnormal condition detected          |
| `COMPLETED`   | Test sequence successfully completed |

---

# 🔌 6. Communication Design

Communication between the PC and microcontroller is performed using a serial interface.

```text
┌──────────────────┐
│ Python Application│
└────────┬─────────┘
         │
         │ Commands
         ▼
┌──────────────────┐
│ Serial Interface │
└────────┬─────────┘
         │
         ▼
┌──────────────────┐
│ Arduino / ESP32  │
└────────┬─────────┘
         │
         │ Status + Measurements
         ▼
┌──────────────────┐
│ Python Application│
└──────────────────┘
```

### Commands

The Python application can transmit commands such as:

```text
START
STOP
STATUS
RESET
SELECT:10
SELECT:20
SELECT:50
```

### Controller Responses

The microcontroller can return:

```text
READY
RUNNING
RESISTANCE:10
RESISTANCE:20
RESISTANCE:50
CURRENT:0.42
VOLTAGE:12.10
MCB:ON
MCB:TRIPPED
TEST_COMPLETE
ERROR
```

> **Implementation Note:** The final message format, baud rate, timing, and error codes will be finalized during software implementation.

---

# 🔧 7. Resistance Selection

The prototype uses a relay module to select the required resistance.

Available resistance values:

```text
┌──────────────┐
│ Resistance   │
├──────────────┤
│    10 Ω      │
│    20 Ω      │
│    50 Ω      │
└──────────────┘
```

The selection process is:

```text
User Selection
      │
      ▼
Python Application
      │
      │ SELECT:20
      ▼
Arduino / ESP32
      │
      ▼
Relay Control
      │
      ▼
20 Ω Selected
```

The software shall ensure that the appropriate relay state is generated according to the actual hardware wiring.

The relay module's active-HIGH or active-LOW behavior will be defined during hardware integration.

---

# 📊 8. Current Measurement

Current is measured using the **ACS712**.

### Measurement Chain

```text
Test Circuit
     │
     ▼
  ACS712
     │
     ▼
ADC Input
     │
     ▼
Microcontroller
     │
     ▼
Calibration
     │
     ▼
Current Value
     │
     ▼
Python Application
     │
 ┌───┴────┐
 ▼        ▼
GUI     Logger
```

### Processing

The software performs:

1. ADC acquisition
2. ADC conversion
3. Zero-current offset correction
4. Sensor sensitivity conversion
5. Optional filtering
6. Range validation
7. Data transmission

Calibration parameters will be obtained during actual hardware testing.

---

# 📈 9. Voltage Measurement

Voltage is measured using the **LM10B voltage-sensor module**.

### Measurement Chain

```text
Test Circuit
     │
     ▼
   LM10B
     │
     ▼
ADC Input
     │
     ▼
Microcontroller
     │
     ▼
Voltage Conversion
     │
     ▼
Python Application
     │
 ┌───┴────┐
 ▼        ▼
GUI     Logger
```

The software applies the appropriate scaling and calibration factor to obtain the measured voltage.

---

# 🔍 10. MCB Trip Detection

The software monitors the MCB throughout the test.

```text
             TEST RUNNING
                  │
                  ▼
            Monitor MCB
                  │
                  ▼
           ┌──────────────┐
           │ Trip Event?  │
           └──────┬───────┘
              NO  │  YES
               │  │
               │  ▼
               │ Record Event
               │  │
               │  ▼
               │ Stop Test
               │
               └──────► Continue Monitoring
```

When a trip is detected, the system records the event together with the relevant measurement data.

Recorded information may include:

* Trip status
* Trip timestamp
* Current
* Voltage
* Selected resistance
* Test state

---

# ⏱️ 11. Data Acquisition

During an active test, measurement data is acquired continuously or at the configured sampling interval.

### Recorded Parameters

| Parameter  | Unit   | Source              |
| ---------- | ------ | ------------------- |
| Timestamp  | ms / s | Software            |
| Voltage    | V      | LM10B               |
| Current    | A      | ACS712              |
| Resistance | Ω      | Relay configuration |
| MCB Status | —      | Controller          |
| Test State | —      | Test Controller     |

### Example Dataset

```csv
Timestamp,Voltage,Current,Resistance,MCB_Status
0.0,12.10,0.12,50,ON
0.5,12.05,0.24,50,ON
1.0,12.02,0.25,50,ON
1.5,0.20,0.00,50,TRIPPED
```

---

# 🧮 12. Data Processing

Sensor data passes through a processing pipeline before being used for analysis.

```text
RAW SENSOR DATA
       │
       ▼
   Calibration
       │
       ▼
Offset Correction
       │
       ▼
Filtering / Averaging
       │
       ▼
 Range Validation
       │
       ▼
PROCESSED DATA
```

Possible processing operations include:

* Offset correction
* Scaling
* Averaging
* Noise reduction
* Range checking
* Invalid-data detection

The final processing parameters will be determined through experimental calibration.

---

# 📋 13. Result Evaluation

After the test is completed, the software evaluates the recorded information according to the defined test criteria.

```text
Test Completed
      │
      ▼
Measurement Validation
      │
      ▼
MCB Response Check
      │
      ▼
Test Criteria
      │
      ▼
Result Evaluation
      │
      ▼
Test Result
```

Possible system states include:

```text
✓ COMPLETED
✓ TRIP DETECTED
⚠ STOPPED BY USER
⚠ TEST TERMINATED
⚠ ERROR
```

Formal pass/fail criteria will be defined from the applicable test requirements and the specific prototype test procedure.

---

# 💾 14. Data Logging

Each test is assigned a unique identifier.

Example:

```text
MCB_TEST_001
MCB_TEST_002
MCB_TEST_003
```

The measurement data can be stored in CSV format.

```text
Data/
├── MCB_TEST_001.csv
├── MCB_TEST_002.csv
└── MCB_TEST_003.csv
```

The stored data can later be used for:

* Analysis
* Graph generation
* Test comparison
* Report generation
* Debugging

---

# 🖥️ 15. GUI Design

The GUI is designed to provide a simple operator workflow.

### Main Interface

```text
╔══════════════════════════════════════════════╗
║          AUTOMATED MCB TEST SYSTEM           ║
╠══════════════════════════════════════════════╣
║                                              ║
║  ● Controller: CONNECTED                     ║
║                                              ║
║  Resistance      [ 20 Ω ▼ ]                  ║
║                                              ║
║  ┌─────────────┐      ┌─────────────┐       ║
║  │ Voltage     │      │ Current     │       ║
║  │ 12.10 V     │      │ 0.42 A      │       ║
║  └─────────────┘      └─────────────┘       ║
║                                              ║
║  MCB Status:    READY                        ║
║  Test Status:   IDLE                         ║
║                                              ║
║       [ ▶ START TEST ]   [ ■ STOP ]          ║
║                                              ║
║  ─────────────── TEST LOG ───────────────    ║
║  System Ready                                ║
║  Resistance Selected                         ║
║  Test Started                                ║
║                                              ║
╚══════════════════════════════════════════════╝
```

The final interface will be implemented after the communication and controller functions have been verified.

---

# ⚠️ 16. Error Handling

The software continuously monitors for abnormal conditions.

### Possible Errors

* Controller disconnected
* Serial communication failure
* Communication timeout
* Invalid sensor data
* Sensor malfunction
* Relay selection error
* Invalid test parameters
* Unexpected MCB state
* Software exception

### Error Response

```text
ERROR DETECTED
      │
      ▼
STOP ACTIVE TEST
      │
      ▼
DISABLE TEST CONTROL
      │
      ▼
RECORD ERROR
      │
      ▼
DISPLAY ERROR
      │
      ▼
RETURN TO SAFE STATE
```

The error-handling system prevents the software from continuing a test when a critical condition is detected.

---

# 🛡️ 17. Safety Logic

Safety functions are incorporated into the software to ensure controlled test termination.

### Normal Stop

```text
User presses STOP
        │
        ▼
Stop Test Sequence
        │
        ▼
Deactivate Test Control
        │
        ▼
Disable Relay Selection
        │
        ▼
Stop Data Acquisition
        │
        ▼
Save Test State
        │
        ▼
Return to IDLE
```

### Critical Error

```text
Critical Error
      │
      ▼
Terminate Test
      │
      ▼
Disable Test Output
      │
      ▼
Deactivate Relay Control
      │
      ▼
Record Error
      │
      ▼
Safe / IDLE State
```

> **Important:** Software safety functions are supplementary. Electrical protection must also be provided through the hardware design. The prototype is a **low-voltage functional demonstrator** and does not reproduce full-scale high-current short-circuit test conditions.

---

# 🧠 18. Design Principles

The software follows the following design principles:

### Modularity

Each function is separated into an independent software module.

### Reliability

Communication and measurement errors are detected and handled.

### Maintainability

The software structure allows individual modules to be modified without redesigning the entire application.

### Scalability

The architecture allows additional sensors, resistance values, test procedures, and reporting functions to be added later.

### Traceability

Test measurements and system events are recorded so that the test process can be reviewed.

### Safety

The software provides controlled test termination and prevents continued operation under critical error conditions.

---

# 🚀 19. Development Strategy

The software will be developed progressively rather than as one large application.

```text
             SOFTWARE DEVELOPMENT
                     │
                     ▼
        ┌────────────────────────┐
        │ 1. Microcontroller I/O │
        └────────────┬───────────┘
                     ▼
        ┌────────────────────────┐
        │ 2. Sensor Acquisition  │
        └────────────┬───────────┘
                     ▼
        ┌────────────────────────┐
        │ 3. Relay Control       │
        └────────────┬───────────┘
                     ▼
        ┌────────────────────────┐
        │ 4. Serial Communication│
        └────────────┬───────────┘
                     ▼
        ┌────────────────────────┐
        │ 5. Python Controller    │
        └────────────┬───────────┘
                     ▼
        ┌────────────────────────┐
        │ 6. Data Acquisition    │
        └────────────┬───────────┘
                     ▼
        ┌────────────────────────┐
        │ 7. GUI Implementation  │
        └────────────┬───────────┘
                     ▼
        ┌────────────────────────┐
        │ 8. Data Processing     │
        └────────────┬───────────┘
                     ▼
        ┌────────────────────────┐
        │ 9. Report Generation   │
        └────────────┬───────────┘
                     ▼
        ┌────────────────────────┐
        │ 10. System Integration │
        └────────────────────────┘
```

This approach allows each subsystem to be verified before moving to the next stage.

---

# 🔗 20. Complete Software Data Flow

The complete information flow through the system is:

```text
                  USER
                   │
                   ▼
             ┌───────────┐
             │    GUI    │
             └─────┬─────┘
                   │
                   ▼
           ┌───────────────┐
           │ Test Control │
           └───────┬───────┘
                   │
                   ▼
          ┌─────────────────┐
          │ Communication   │
          └────────┬────────┘
                   │
                   ▼
          ┌─────────────────┐
          │ Arduino / ESP32 │
          └───────┬─────────┘
                  │
        ┌─────────┼─────────┐
        │         │         │
        ▼         ▼         ▼
      Relay     ACS712    LM10B
        │         │         │
        │         ▼         ▼
        │      Current    Voltage
        │         │         │
        └─────────┼─────────┘
                  ▼
            MCB Under Test
                  │
                  ▼
            MCB Status
                  │
                  ▼
          Python Application
                  │
          ┌───────┼────────┐
          ▼       ▼        ▼
       Display  Logging  Processing
                          │
                          ▼
                    Result Evaluation
                          │
                          ▼
                    Report Generation
```

---

# 📌 21. Software Design Summary

The software provides a complete supervisory framework for the automated MCB test prototype.

Its architecture separates:

```text
HARDWARE CONTROL
       ↓
COMMUNICATION
       ↓
TEST CONTROL
       ↓
DATA ACQUISITION
       ↓
DATA PROCESSING
       ↓
RESULT EVALUATION
       ↓
DATA LOGGING
       ↓
REPORT GENERATION
```

This modular architecture provides a structured foundation for implementing the actual Arduino/ESP32 firmware and Python application.

The implementation will be developed progressively, with hardware interfaces and communication verified before integrating the complete graphical application.

---

> **Development Status:** Software architecture and design defined.
> **Implementation Status:** Under development.
> **Prototype Scope:** Low-voltage functional demonstrator.
