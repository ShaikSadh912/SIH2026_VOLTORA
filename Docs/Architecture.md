# 03 — System Architecture

## 🏗️ VOLTORA System Architecture

The VOLTORA platform is organized into four major layers:

> **User Interface → Control → Measurement → Test Power**

This separation makes the system easier to develop, troubleshoot, operate, and expand.

---

## 🔷 High-Level Architecture

```text
                         ┌─────────────────────────┐
                         │      🖥️ PYTHON HMI      │
                         │  Monitoring • Data • UI │
                         └────────────┬────────────┘
                                      │
                              USB / Serial
                                      │
                                      ▼
                         ┌─────────────────────────┐
                         │       🎛️ ESP32          │
                         │   Main Controller       │
                         └────────────┬────────────┘
                                      │
                 ┌────────────────────┼────────────────────┐
                 │                    │                    │
                 ▼                    ▼                    ▼
          ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
          │ ⚡ RELAYS   │      │ 📊 SENSORS  │      │ 🔍 MCB      │
          │ Switching   │      │ ACS712      │      │   STATUS    │
          │ & Control   │      │ Voltage*    │      │  Detection  │
          └──────┬──────┘      └──────┬──────┘      └──────┬──────┘
                 │                    │                    │
                 └────────────────────┼────────────────────┘
                                      │
                                      ▼
                         ┌─────────────────────────┐
                         │     ⚡ TEST CIRCUIT     │
                         │                         │
                         │ Controlled Load         │
                         │          ↓              │
                         │        ACS712            │
                         │          ↓              │
                         │       1 A MCB            │
                         └─────────────────────────┘
```

> ***Voltage sensing is included only when applicable to the selected test-source configuration.**

---

## ⚡ Test Power Path

The controlled test-current path is:

```text
┌─────────┐
│ 12 V DC │
└────┬────┘
     │
     ▼
┌─────────┐
│ 🔒 Fuse │
└────┬────┘
     │
     ▼
┌─────────────┐
│⚡ Main Relay │
└─────┬───────┘
      │
      ▼
┌─────────────────┐
│  🎚️ Controlled   │
│      Load       │
└───────┬─────────┘
        │
        ▼
┌─────────────────┐
│ 📊 ACS712       │
│ Current Sensor  │
└───────┬─────────┘
        │
        ▼
┌─────────────────┐
│ 🔴 1 A MCB      │
│   Under Test    │
└───────┬─────────┘
        │
        ▼
     RETURN
```

---

## 🎛️ Control & Measurement Layers

### Control Layer

**ESP32** acts as the central controller responsible for:

* Relay control
* Test sequencing
* Start/Stop/Reset handling
* Safety logic
* Trip detection
* Timing

### Measurement Layer

The measurement system provides:

* 📈 Current measurement through **ACS712**
* 🔍 MCB state monitoring
* ⏱️ Trip-time calculation
* 📊 Data acquisition for analysis

### Interface Layer

The **Python HMI** provides:

* 🖥️ Real-time monitoring
* 📈 Measurement visualization
* ⏱️ Trip-time display
* 💾 Data logging
* 📑 Test-result reporting

---

## 🔄 System Control States

```text
                 ┌───────────┐
                 │   IDLE    │
                 └─────┬─────┘
                       │ START
                       ▼
                 ┌───────────┐
                 │   READY   │
                 └─────┬─────┘
                       │ TEST
                       ▼
                ┌────────────┐
                │  TESTING   │
                └─────┬──────┘
                      │
             ┌────────┼─────────┐
             │        │         │
             ▼        ▼         ▼
          ┌──────┐ ┌───────┐ ┌─────────┐
          │ TRIP │ │ FAULT │ │ STOPPED │
          └──────┘ └───────┘ └─────────┘
```

---

## 🧩 Architecture Philosophy

The system intentionally separates:

| Layer                  | Purpose                     |
| ---------------------- | --------------------------- |
| 🖥️ **User Interface**  | Monitoring & reporting      |
| 🎛️ **Controller**      | Automation & decision logic |
| 📊 **Measurement**     | Electrical data acquisition |
| ⚡ **Test Power**      | Controlled MCB test circuit |
| 🛡️ **Safety**          | Fault handling & shutdown   |

This modular architecture allows individual sections to be developed and tested independently before **full system integration**.

### 🚀 Future Expansion

The architecture can later support:

**Advanced DAQ → Industrial PLC → Automated Test Sequences → Database → Remote Monitoring → Professional Test Infrastructure**
