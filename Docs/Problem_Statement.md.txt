# 01 — Problem Statement

## ⚡ MCB (MINIATURE CIRCUIT BREAKER) ANALYZER

### *For IEC 60898-1:2015 MCB Compliance*

---

### 🔴 The Challenge

**Miniature Circuit Breakers (MCBs)** are critical safety devices designed to interrupt abnormal current conditions.

Reliable testing requires:

* ⚡ Controlled electrical test conditions
* 📊 Accurate current and voltage measurement
* 🔍 Automatic MCB trip detection
* ⏱️ Precise trip-time measurement
* 💾 Test-data logging
* 🖥️ Real-time monitoring
* 📑 Automated result reporting

Professional short-circuit laboratories can involve **very high fault currents and specialized safety infrastructure**, making direct replication impractical and unsafe for a college-level prototype.

---

### 🎯 Our Problem

The objective is to develop an **automated MCB testing architecture** that demonstrates the key principles of a professional test system:

> **Measure → Monitor → Detect → Time → Record → Report**

The system should provide a structured and repeatable testing workflow while maintaining a **safe, low-energy prototype environment**.

---

### 🟢 VOLTORA Prototype Approach

VOLTORA implements a **low-voltage, current-limited demonstrator** that focuses on the **automation, sensing, control, and data-acquisition architecture** of an MCB testing system.

```text
Test Source
     ↓
Controlled Load
     ↓
Current Measurement
     ↓
    MCB
     ↓
Trip Detection
     ↓
Timing & Data Logging
     ↓
Monitoring & Report
```

### 🛡️ Safety & Scope

The prototype **does not attempt to reproduce professional high-energy short-circuit conditions**.

**Reference:** IEC 60898-1:2015
**Prototype:** Educational demonstrator — **not an IEC compliance certification system**
