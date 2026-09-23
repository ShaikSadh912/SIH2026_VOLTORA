# ⚡ VOLTRA – Firmware Module

> **Sense • Process • Decide • Control**

## 🧠 Firmware Overview

The **VOLTRA Firmware Module** acts as the control layer of the protection testing platform.

Developed for the **Arduino UNO**, the firmware acquires electrical measurements from the sensing modules, processes the measured values, controls the switching elements, monitors the test condition, and identifies the occurrence of a trip condition.

The firmware provides the link between the **physical hardware** and the **monitoring software**, enabling automated measurement, decision-making, and status indication.

---

## 🔄 Firmware Operation

```text
              ⚡ HARDWARE INPUT
                     │
                     ▼
          📡 SENSOR DATA ACQUISITION
                     │
                     ▼
            🧮 DATA PROCESSING
                     │
                     ▼
          📊 CURRENT / VOLTAGE
              MONITORING
                     │
                     ▼
          🎯 THRESHOLD CHECK
                     │
              ┌──────┴──────┐
              │             │
          Below Limit    Above Limit
              │             │
              ▼             ▼
         NORMAL STATE    TRIP DETECTED
              │             │
              └──────┬──────┘
                     ▼
             🔀 OUTPUT CONTROL
                     │
                     ▼
              💡 STATUS UPDATE