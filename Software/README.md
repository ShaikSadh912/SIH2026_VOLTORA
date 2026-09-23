# ⚡ VOLTRA – Software Module

## 🚀 Overview

The **VOLTRA Software Module** is designed to analyze recorded electrical test data and determine the response of the protection system under different load conditions.

The Python-based software processes **current and voltage measurements**, compares the measured current with a predefined **40 mA trip threshold**, identifies the test condition as **TRIPPED** or **NOT TRIPPED**, and provides graphical visualization of the results.

---

## 🔄 Software Workflow

```text
        Recorded Test Data
                │
                ▼
       Python Data Processing
                │
                ▼
      Current & Voltage Analysis
                │
                ▼
      Trip Threshold Comparison
                │
                ▼
       ┌───────────────────┐
       │  TRIPPED /        │
       │  NOT TRIPPED      │
       └───────────────────┘
                │
                ▼
       Graphical Visualization
                │
                ▼
        Final Test Comparison