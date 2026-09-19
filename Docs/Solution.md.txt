# 02 — Proposed Solution

## 🚀 VOLTORA MCB (MINIATURE CIRCUIT BREAKER) ANALYZER

**VOLTORA** is an integrated MCB testing platform that combines **sensing, control, automation, timing, data acquisition, monitoring, and reporting** into a single workflow.

The system is designed to demonstrate how an automated test platform can **execute → measure → detect → analyze → document** an MCB test.

---

## 🔄 Core Testing Workflow

```text
             ▶ START TEST
                  │
                  ▼
        ⚡ CONTROLLED TEST
                  │
                  ▼
        📊 CURRENT MEASUREMENT
                  │
                  ▼
          🔍 MCB MONITORING
                  │
                  ▼
           🚨 TRIP DETECTION
                  │
                  ▼
        🛑 AUTOMATIC SHUTDOWN
                  │
                  ▼
          ⏱️ TRIP-TIME
             CALCULATION
                  │
                  ▼
           💾 DATA LOGGING
                  │
                  ▼
          📑 TEST REPORT
```

---

## ✨ Key Features

| Feature                       | Implementation                       |
| ----------------------------- | ------------------------------------ |
| 🔌 **Controlled Test Source** | Low-voltage, current-limited supply  |
| 🎛️ **Automation**             | ESP32-based control system           |
| 📈 **Current Sensing**        | ACS712 current sensor                |
| 🔍 **Trip Detection**         | Automated MCB status monitoring      |
| ⏱️ **Timing**                 | Automatic trip-time calculation      |
| 🖥️ **User Interface**         | LCD + Python HMI                     |
| 💾 **Data Acquisition**       | Real-time measurement & logging      |
| 🚨 **Safety Control**         | Fault detection & automatic shutdown |

---

## 🧠 System Intelligence

VOLTORA transforms a conventional manual test into an **automated measurement pipeline**:

```text
     CONTROL
        ↓
     MEASURE
        ↓
     MONITOR
        ↓
     DETECT
        ↓
      TIME
        ↓
     RECORD
        ↓
     REPORT
```

This enables repeatable testing, centralized monitoring, and structured test-data management.

---

## 🛡️ Design Principle

> ### **“Demonstrate the intelligence of the test system — without reproducing the hazardous energy of a professional test system.”**

The prototype focuses on the **automation and measurement architecture** of an MCB testing system using a **low-voltage, current-limited demonstrator**.

**VOLTORA — Measure. Detect. Automate. Report.**
