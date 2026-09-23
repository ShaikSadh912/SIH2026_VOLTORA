# ⚡ VOLTRA – Hardware Design

## 1. Overview

The VOLTRA hardware is designed as a controlled electrical testing platform for evaluating system response under different load conditions.

The hardware integrates a power source, selectable resistive loads, current and voltage sensing, relay-based switching, controller, status indicators, and protection elements.

The design enables controlled application of different load conditions and measurement of the resulting electrical parameters.

---

## 2. Hardware Architecture

```text
                POWER SOURCE
                     │
                     ▼
              MAIN POWER RELAY
                     │
                     ▼
              LOAD SELECTION
                     │
              ┌──────┴──────┐
              │             │
            82 Ω           20 Ω
              │             │
              └──────┬──────┘
                     ▼
              CURRENT SENSOR
                     │
                     ▼
             PROTECTION PATH
                     │
                     ▼
                 LOAD PATH
                     
        ┌─────────────────────────┐
        │       Arduino UNO       │
        │                         │
        │  Sensor Processing      │
        │  Relay Control          │
        │  Trip Detection         │
        │  Status Indication      │
        └─────────────────────────┘