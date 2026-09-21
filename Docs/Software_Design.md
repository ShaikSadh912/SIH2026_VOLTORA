# Software Design

## 1. Introduction

The software is designed to control, monitor, and automate the low-voltage prototype of the Automated MCB Test System.

The software integrates a microcontroller-based hardware layer with a Python-based monitoring and control application.

The main purpose of the software is to demonstrate the following functions:

* Automated test control
* Resistance selection
* Current measurement
* Voltage measurement
* MCB status monitoring
* Test sequencing
* Data acquisition
* Data processing
* Result recording
* Report generation
* Error handling

The software is designed in a modular manner so that individual functions can be developed, tested, and modified independently.

---

# 2. Software Architecture

The complete software system consists of two major layers:

### 2.1 Microcontroller Firmware

The Arduino/ESP32 acts as the hardware controller.

It is responsible for:

* Controlling the relay module
* Selecting the required resistance
* Reading the ACS712 current sensor
* Reading the voltage sensor
* Monitoring the MCB status
* Sending measurement data to the PC
* Receiving commands from the Python application

### 2.2 Python Application

The Python application acts as the supervisory control and monitoring system.

It is responsible for:

* User interface
* Test configuration
* Test sequence control
* Communication with the microcontroller
* Measurement monitoring
* Data processing
* Data logging
* Result evaluation
* Report generation
* Error handling

### 2.3 Overall Architecture

```text
                  ┌──────────────────────────┐
                  │      Python GUI          │
                  │                          │
                  │  Test Control            │
                  │  Measurements            │
                  │  Status                  │
                  │  Test Results            │
                  └────────────┬─────────────┘
                               │
                               │ Serial Communication
                               │
                  ┌────────────▼─────────────┐
                  │     Arduino / ESP32      │
                  │                          │
                  │  Control Logic            │
                  │  Sensor Acquisition       │
                  │  Relay Control            │
                  │  MCB Monitoring           │
                  └───────┬─────────┬────────┘
                          │         │
                ┌─────────┘         └─────────┐
                ▼                             ▼
        ┌───────────────┐             ┌───────────────┐
        │ Relay Module  │             │    Sensors    │
        │               │             │               │
        │ 10 Ω          │             │ ACS712        │
        │ 20 Ω          │             │ LM10B         │
        │ 50 Ω          │             │               │
        └───────┬───────┘             └───────┬───────┘
                │                             │
                └─────────────┬───────────────┘
                              ▼
                       MCB Under Test
```

---

# 3. Software Modules

The software is divided into functional modules.

```text
Software
│
├── User Interface
├── Communication
├── Test Controller
├── Relay Control
├── Sensor Acquisition
├── MCB Monitoring
├── Data Processing
├── Data Logging
├── Result Evaluation
├── Report Generation
└── Error Handling
```

Each module performs a specific task.

This modular architecture makes the system easier to develop, debug, maintain, and expand.

---

# 4. User Interface Design

The Python application provides a graphical user interface for the operator.

The GUI provides access to the main test functions.

### Main GUI Functions

* Connect to controller
* Configure test parameters
* Select resistance
* Start test
* Stop test
* Display voltage
* Display current
* Display MCB status
* Display test status
* Display test log
* Display test result

A conceptual interface is shown below:

```text
┌─────────────────────────────────────────────┐
│          AUTOMATED MCB TEST SYSTEM          │
├─────────────────────────────────────────────┤
│                                             │
│ Controller: CONNECTED                       │
│                                             │
│ Resistance: [ 20 Ω ▼ ]                     │
│                                             │
│ Voltage:       12.10 V                      │
│ Current:        0.42 A                      │
│                                             │
│ MCB Status:    READY                        │
│ Test Status:   IDLE                         │
│                                             │
│ [ START TEST ]       [ STOP TEST ]          │
│                                             │
│ Test Log                                   │
│ ──────────────────────────────────────────  │
│ System Ready                                │
│ Resistance Selected                         │
│ Test Started                                │
│                                             │
└─────────────────────────────────────────────┘
```

The final GUI layout may be modified during implementation.

---

# 5. Communication Design

Communication between the Python application and the Arduino/ESP32 is performed using serial communication.

The communication layer provides two-way data exchange.

```text
Python Application
        │
        │ Commands
        ▼
     Serial
        │
        ▼
Arduino / ESP32
        │
        │ Measurements / Status
        ▼
     Serial
        │
        ▼
Python Application
```

## 5.1 Commands

The Python application can send commands such as:

```text
START
STOP
STATUS
RESET
SELECT:10
SELECT:20
SELECT:50
```

## 5.2 Responses

The microcontroller can return information such as:

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

The exact communication format and baud rate will be finalized during implementation.

---

# 6. Resistance Selection Logic

The system uses a relay module to select the required resistance from the available resistor bank.

The current prototype contains:

* 10 Ω resistance
* 20 Ω resistance
* 50 Ω resistance

The Python application sends the required resistance to the microcontroller.

The microcontroller then activates the corresponding relay.

```text
Python
   │
   │ SELECT:20
   ▼
Arduino / ESP32
   │
   ▼
Relay Control
   │
   ▼
20 Ω Resistance Selected
```

The software ensures that the required resistance path is selected according to the hardware configuration.

The relay control logic shall account for the actual relay module configuration, including active-HIGH or active-LOW operation.

---

# 7. Current Measurement Design

Current measurement is performed using the ACS712 current sensor.

The measurement path is:

```text
Test Circuit
     ↓
   ACS712
     ↓
Microcontroller ADC
     ↓
Current Calculation
     ↓
Serial Communication
     ↓
Python Application
     ↓
GUI + Data Logger
```

The microcontroller obtains the sensor output through its analog input.

The software converts the sensor output into current using the appropriate sensor sensitivity and zero-current offset.

The measurement process consists of:

1. ADC reading
2. ADC-to-voltage conversion
3. Zero-current offset correction
4. Sensor sensitivity conversion
5. Optional filtering
6. Range validation
7. Transmission to Python

Calibration values will be determined during hardware testing.

---

# 8. Voltage Measurement Design

Voltage is measured using the LM10B voltage sensor.

The measurement path is:

```text
Test Circuit
     ↓
   LM10B
     ↓
Microcontroller ADC
     ↓
Voltage Conversion
     ↓
Serial Communication
     ↓
Python Application
     ↓
GUI + Data Logger
```

The software converts the sensor output into the corresponding voltage using the sensor scaling factor and calibration value.

The voltage measurement is used for:

* Real-time display
* Data logging
* Test monitoring
* Result analysis

---

# 9. MCB Monitoring

The software monitors the state of the MCB during the test.

The MCB status is obtained through the implemented hardware detection mechanism.

The basic logic is:

```text
Test Running
     ↓
Monitor MCB
     ↓
MCB Tripped?
   /       \
 NO        YES
 │          │
Continue   Record Trip
 │          │
 │          ▼
 │       Stop Test
 │          │
 └──────────┘
```

When a trip is detected, the software records the event and terminates the active test sequence.

The recorded information may include:

* Trip status
* Trip time
* Current at detection
* Voltage at detection
* Selected resistance

The exact trip detection method depends on the final hardware implementation.

---

# 10. Test Control Logic

The Python application acts as the main test controller.

The general sequence is:

```text
Initialize
    ↓
Connect to Controller
    ↓
Check Hardware
    ↓
Load Parameters
    ↓
Select Resistance
    ↓
Start Test
    ↓
Acquire Measurements
    ↓
Monitor MCB
    ↓
Trip / Completion Detected
    ↓
Stop Test
    ↓
Process Data
    ↓
Evaluate Result
    ↓
Save Data
    ↓
Generate Report
    ↓
Return to IDLE
```

The controller maintains the current state of the test.

Possible software states include:

```text
IDLE
CONNECTING
READY
CONFIGURING
RUNNING
TRIPPED
COMPLETED
ERROR
STOPPED
```

---

# 11. Data Acquisition

During the test, the software continuously receives measurement data from the microcontroller.

The main parameters are:

| Parameter   | Unit | Source          |
| ----------- | ---- | --------------- |
| Timestamp   | ms/s | Software        |
| Voltage     | V    | LM10B           |
| Current     | A    | ACS712          |
| Resistance  | Ω    | Relay selection |
| MCB Status  | —    | Microcontroller |
| Test Status | —    | Software        |

The collected information is stored for later processing and reporting.

Example:

```text
Timestamp,Voltage,Current,Resistance,MCB_Status
0.0,12.10,0.12,50,ON
0.5,12.05,0.24,50,ON
1.0,12.02,0.25,50,ON
1.5,0.20,0.00,50,TRIPPED
```

The actual data format may be modified during implementation.

---

# 12. Data Processing

Raw sensor measurements may contain offsets and measurement noise.

Therefore, the software processes the acquired data before final analysis.

```text
Raw Data
   ↓
Calibration
   ↓
Offset Correction
   ↓
Filtering / Averaging
   ↓
Validation
   ↓
Processed Data
```

Possible processing operations include:

* Offset correction
* Scaling
* Moving average
* Noise reduction
* Range checking
* Invalid-data detection

The processing parameters will be finalized based on actual sensor testing.

---

# 13. Result Evaluation

After the test is completed, the software evaluates the collected information according to the defined test criteria.

The evaluation process is:

```text
Test Completed
      ↓
Check Measurements
      ↓
Check MCB Response
      ↓
Check Test Conditions
      ↓
Evaluate Defined Criteria
      ↓
Generate Test Result
```

The result may include:

* Test completed
* MCB trip detected
* MCB trip not detected
* Test stopped by user
* Test terminated due to error

Any formal pass/fail decision shall use the applicable test requirements and the defined prototype test conditions.

---

# 14. Data Logging

The software stores test information for future analysis.

Each test can be assigned a unique test ID.

Example:

```text
Test ID: MCB_TEST_001
Date: YYYY-MM-DD
Time: HH:MM:SS
Resistance: 20 Ω
```

Measurement data can be stored in CSV format.

Example:

```text
Data/
├── MCB_TEST_001.csv
├── MCB_TEST_002.csv
└── MCB_TEST_003.csv
```

The log can contain:

* Timestamp
* Voltage
* Current
* Resistance
* MCB status
* Test state
* Error information

---

# 15. Report Generation

After test completion, the software can generate a test report.

The report may contain:

### Test Information

* Test ID
* Date
* Time
* Operator
* MCB identification

### Test Parameters

* Selected resistance
* Test voltage
* Test duration

### Measurements

* Current
* Voltage
* MCB status
* Trip time

### Result

* Test status
* Trip status
* Relevant measurement values

### Graphical Data

The report may contain:

* Current versus time
* Voltage versus time

The report can be generated in PDF format for documentation.

---

# 16. Error Handling

The software continuously checks for abnormal conditions.

Possible errors include:

* Microcontroller disconnected
* Serial communication failure
* Communication timeout
* Invalid sensor values
* Sensor failure
* Invalid resistance selection
* Relay control error
* Unexpected MCB status
* Software exception

The general error-handling process is:

```text
Error Detected
      ↓
Stop Active Test
      ↓
Disable Test Output
      ↓
Record Error
      ↓
Display Error Message
      ↓
Return to Safe State
```

Errors should be logged to assist with debugging and maintenance.

---

# 17. Safety Logic

Safety is an important part of the software design.

The software provides a controlled method for terminating the test.

When the user presses the STOP button or a critical error occurs:

```text
STOP / CRITICAL ERROR
          ↓
      Stop Test
          ↓
Deactivate Test Control
          ↓
Disable Relay Selection
          ↓
Stop Data Acquisition
          ↓
Record Test Termination
          ↓
Return to IDLE
```

The software should not rely on software alone for electrical safety. Appropriate hardware protection, isolation, current limiting, fusing, and emergency-disconnection mechanisms must be provided according to the actual hardware design.

The present project is a low-voltage functional demonstrator and does not attempt to reproduce full-scale high-current short-circuit test conditions.

---

# 18. Software Development Approach

The software will be developed incrementally.

### Stage 1 – Microcontroller Firmware

Implement and verify:

* GPIO configuration
* Relay control
* Resistance selection
* ACS712 reading
* Voltage sensor reading
* MCB monitoring
* Serial communication

### Stage 2 – Communication

Verify reliable communication between:

```text
Python ↔ Arduino/ESP32
```

### Stage 3 – Python Modules

Implement:

* Communication module
* Sensor processing
* Relay control
* Test controller
* Data logger

### Stage 4 – GUI

Implement:

* Connection status
* Test controls
* Measurement display
* MCB status
* Test log
* Result display

### Stage 5 – Data Processing and Reporting

Implement:

* Data processing
* Result evaluation
* CSV data storage
* Graph generation
* PDF report generation

### Stage 6 – System Integration

Integrate all modules and verify the complete automated workflow.

---

# 19. Software Design Summary

The software provides the control and monitoring layer of the Automated MCB Test System.

The complete software workflow can be summarized as:

```text
User
 │
 ▼
Python GUI
 │
 ▼
Test Controller
 │
 ├───────────────┐
 ▼               ▼
Communication   Data Processing
 │               │
 ▼               ▼
Arduino/ESP32   Result Evaluation
 │               │
 ├───────┬───────┘
 │       │
 ▼       ▼
Relay   Sensors
 │       │
 │       ├── ACS712 → Current
 │       │
 │       └── LM10B → Voltage
 │
 ▼
Resistance Selection
 │
 ▼
MCB Under Test
 │
 ▼
MCB Status
 │
 └──────────────► Python
                    │
                    ▼
                Data Logging
                    │
                    ▼
              Report Generation
```

The final software implementation will follow this architecture while allowing individual parameters and implementation details to be refined during hardware integration and testing.
