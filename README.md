⚡ SIH2026_VOLTRA

Automated High-Current Short-Circuit Test System for IEC 60898-1:2015 MCB Compliance

VOLTRA — Measure. Detect. Automate. Report.

🏆 Project Overview

VOLTRA is an automated MCB testing and analysis platform designed around the testing concepts associated with IEC 60898-1:2015.

The project focuses on combining:

⚡ Controlled Testing → 📊 Measurement → 🔍 Trip Detection → ⏱️ Timing → 💾 Data Logging → 📑 Reporting

The college prototype uses a low-voltage, current-limited test environment to demonstrate the automation, sensing, control, and data-acquisition architecture of a professional MCB testing system.

🔴 Problem Statement

Testing Miniature Circuit Breakers (MCBs) requires controlled electrical conditions, accurate measurement, reliable trip detection, precise timing, and proper recording of test results.

Professional short-circuit testing can involve very high fault currents and specialized laboratory infrastructure, making direct replication unsuitable for a college prototype.

The Challenge

Develop an automated testing architecture capable of demonstrating:

⚡ Controlled test conditions

📊 Electrical measurement

🔍 MCB trip detection

⏱️ Trip-time measurement

💾 Data logging

🖥️ Real-time monitoring

📑 Automated reporting

💡 Proposed Solution

VOLTORA integrates sensing, control, automation, timing, data acquisition, monitoring, and reporting into one system.

Core Workflow

              ▶ START
                 ↓
          ⚡ CONTROLLED TEST
                 ↓
          📊 MEASURE CURRENT
                 ↓
           🔍 MONITOR MCB
                 ↓
            🚨 TRIP DETECT
                 ↓
          🛑 AUTO SHUTDOWN
                 ↓
          ⏱️ CALCULATE TIME
                 ↓
            💾 LOG DATA
                 ↓
            📑 GENERATE REPORT

Design Principle

Demonstrate the intelligence of the test system without reproducing the hazardous energy of a professional test system.

🏗️ System Architecture

                    ┌──────────────────────┐
                    │      🖥️ PYTHON HMI    │
                    │ Monitoring • Data    │
                    │ Graphs • Reports     │
                    └──────────┬───────────┘
                               │
                          USB / Serial
                               │
                               ▼
                    ┌──────────────────────┐
                    │ 🎛️ Arduino Uno       │
                    │   Main Controller    │
                    └──────────┬───────────┘
                               │
             ┌─────────────────┼─────────────────┐
             │                 │                 │
             ▼                 ▼                 ▼
        ┌──────────┐      ┌──────────┐     ┌──────────┐
        │  RELAYS  │      │ SENSORS  │     │ MCB      │
        │ Switching│      │ ACS712   │     │ STATUS   │
        └────┬─────┘      └────┬─────┘     └────┬─────┘
             │                 │                 │
             └─────────────────┼─────────────────┘
                               ▼
                    ┌──────────────────────┐
                    │     ⚡ TEST CIRCUIT   │
                    │                      │
                    │ Controlled Load      │
                    │        ↓             │
                    │      ACS712          │
                    │        ↓             │
                    │      1 A MCB         │
                    └──────────────────────┘

⚡ Prototype Test Power Path

12 V DC
   ↓
 Fuse
   ↓
Main Relay
   ↓
Controlled Load
   ↓
 ACS712
   ↓
 1 A MCB
   ↓
Return

The prototype is designed as a low-voltage and current-limited demonstrator rather than a professional high-energy short-circuit test system.

🔧 Hardware

Component

Purpose

🎛️ ESP32

Main controller

📊 ACS712

Current measurement

🔴 1 A MCB

Device Under Test

🔌 12 V DC Supply

Controlled test source

⚡ Relay Module

Load/test switching

💡 LCD

Local system display

🖥️ Python HMI

Monitoring & visualization

🔘 Control Buttons

Start / Stop / Reset

🚨 Emergency Stop

Safety shutdown

🛡️ Fuse

Overcurrent protection

🔧 Controlled Load

Test-current generation

💻 Software Architecture

┌─────────────────────┐
│      ESP32          │
│                     │
│ Control + Sensing   │
│ Timing + Safety     │
└──────────┬──────────┘
           │
       USB / Serial
           │
           ▼
┌─────────────────────┐
│     Python HMI      │
│                     │
│ Live Data           │
│ Graphs              │
│ Logging             │
│ Analysis            │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│   Test Report       │
│                     │
│ Measurements        │
│ Trip Time           │
│ Test Result         │
└─────────────────────┘

🔄 Test Sequence

IDLE
  ↓
READY
  ↓
TESTING
  ↓
TRIP DETECTED
  ↓
AUTOMATIC SHUTDOWN
  ↓
DATA LOGGING
  ↓
RESULT / REPORT

Test Stop Conditions

The test is automatically stopped when:

MCB Trip
   OR
STOP Pressed
   OR
Emergency Stop
   OR
Sensor Fault
   OR
System Fault

Any critical fault → Stop the test → Remove test power → Enter safe state

📊 Measurements & Data

The system is designed to capture and process:

📈 Test current

⚡ Test voltage where applicable

⏱️ Trip time

🔍 MCB status

🕐 Test timestamps

🚨 Fault conditions

📋 Test results

Trip-Time Concept

Trip Time = Trip Detection Time − Test Start Time

Measured data can be transferred to the Python HMI for visualization, logging, and report generation.

🛡️ Safety

Electrical testing can involve serious hazards.

VOLTORA therefore uses a low-voltage, current-limited prototype architecture.

Safety Features

🔒 Low-voltage operation

⚡ Current-limited source

🛡️ Fuse protection

🎛️ Controlled switching

🚨 Emergency stop

⛔ Automatic shutdown

🔌 Protected controller inputs

📦 Enclosed electrical connections

🔍 Fault monitoring

High-Energy Testing

The prototype does not reproduce professional high-current short-circuit conditions.

Professional high-energy testing requires appropriately engineered laboratory infrastructure, protection systems, switching equipment, measurement systems, enclosures, and qualified procedures.

📁 Repository Structure

SIH2026_VOLTORA/
│
├── 📄 README.md
├── 📄 LICENSE
├── 📄 .gitignore
│
├── 📁 docs/
│   ├── 01_Problem_Statement.md
│   ├── 02_Solution.md
│   ├── 03_Architecture.md
│   ├── 04_Hardware_Design.md
│   ├── 05_Software_Design.md
│   ├── 06_Testing.md
│   ├── 07_Safety.md
│   ├── 08_Results.md
│   └── 09_Future_Scope.md
│
├── 📁 hardware/
│   └── Hardware files
│
├── 📁 software/
│   └── Firmware and Python HMI
│
└── 📁 simulation/
    └── Simulation models and results

🧪 Development & Testing

The system follows a staged development approach:

Component Testing
       ↓
Module Testing
       ↓
Sensor Validation
       ↓
Relay & Control Testing
       ↓
MCB Monitoring
       ↓
Software Integration
       ↓
Complete System Demonstration

No test values are assumed or fabricated. Actual measurements and results will be added after hardware validation.

🚀 Future Scope

The VOLTORA architecture can be expanded toward a professional testing platform.

Industrial Control

ESP32 → PLC → Industrial I/O → Industrial HMI

Advanced Measurement

High-Speed DAQ → Waveform Capture → Transient Analysis

Automation

Automatic DUT Fixture → Multi-Channel Testing → DUT Identification

Data Management

Database → Test History → QR/Barcode Tracking → Automated PDF Reports

Advanced Software

Graphs → Statistical Analysis → Comparison → Remote Monitoring

Industrial Safety

Safety Interlocks → Guard Monitoring → Contactor Feedback → Industrial E-Stop

Long-Term Vision

MCB / DUT
    ↓
Professional Test Infrastructure
    ↓
Measurement & DAQ
    ↓
Automation Controller
    ↓
HMI
    ↓
Database
    ↓
Automated Report

📌 Project Status

Module

Status

Project Architecture

🟢 Defined

Hardware Selection

🟢 In Progress

ESP32 Control

🟡 Development

Current Measurement

🟡 Development

MCB Monitoring

🟡 Development

Python HMI

🟡 Development

Data Logging

🟡 Development

Simulation

🟡 Planned

Hardware Integration

🟡 Planned

Final Demonstration

⚪ Pending

🎯 Expected Outcome

VOLTORA aims to demonstrate a structured, automated, and data-driven approach to MCB testing.

The prototype will demonstrate:

CONTROL → MEASURE → DETECT → TIME → RECORD → REPORT

while maintaining a safe, low-voltage, current-limited test environment.

🌐 Project Vision

       ⚡ VOLTRA
           │
           ▼
      SMART TESTING
           │
     ┌─────┼─────┐
     ▼     ▼     ▼
  MEASURE DETECT AUTOMATE
     │     │     │
     └─────┼─────┘
           ▼
       ANALYZE
           │
           ▼
        REPORT

“Automate the test. Capture the data. Understand the result.”

📚 References

IEC 60898-1:2015 — Electrical accessories — Circuit-breakers for overcurrent protection for household and similar installations

ESP32 Documentation — Espressif Systems

ACS712 Current Sensor — Allegro MicroSystems

⚠️ Disclaimer

This repository documents an educational prototype and research demonstrator.

The prototype is intentionally designed for low-voltage, current-limited operation and does not reproduce professional high-current short-circuit testing.

The system should not be interpreted as an IEC 60898-1 compliance certification system or as a substitute for accredited laboratory testing.

👥 Team VOLTRA

SIH 2026

Project: Automated High-Current Short-Circuit Test System for IEC 60898-1:2015 MCB Compliance

Team: VOLTRA

⚡ VOLTRA — Measure. Detect. Automate. Report.