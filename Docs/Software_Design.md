# ⚡ VOLTRA – Software Design

## 1. Overview

The VOLTRA software layer is responsible for processing recorded electrical test data, evaluating the measured parameters, identifying the trip condition, and presenting the results through numerical reports and graphical visualization.

The software is implemented using **Python** and **Matplotlib**.

---

## 2. Software Architecture

```text
             TEST DATA
                 │
                 ▼
        DATA INPUT & STORAGE
                 │
                 ▼
        DATA PROCESSING
                 │
        ┌────────┴────────┐
        ▼                 ▼
 CURRENT ANALYSIS    VOLTAGE ANALYSIS
        │                 │
        └────────┬────────┘
                 ▼
        THRESHOLD ANALYSIS
                 │
                 ▼
        TRIP STATUS
                 │
        ┌────────┴────────┐
        ▼                 ▼
     TRIPPED          NOT TRIPPED
        │                 │
        └────────┬────────┘
                 ▼
       REPORT & GRAPH
        GENERATION