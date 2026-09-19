# 07 — Safety

## 🛡️ Safety First

Electrical testing requires careful control of **energy, switching, measurement, and fault conditions**.

VOLTORA is therefore designed as a **low-voltage, current-limited educational demonstrator**, with safety built into the test workflow rather than treated as an afterthought.

---

## 🔐 Built-In Safety Measures

| Safety Feature               | Purpose                                             |
| ---------------------------- | --------------------------------------------------- |
| 🔒 **Low-Voltage Operation** | Limits electrical energy in the prototype           |
| ⚡ **Current-Limited Source** | Restricts available test current                    |
| 🛡️ **Fuse Protection**      | Provides overcurrent protection                     |
| 🎛️ **Controlled Switching** | Enables controlled energization of the test circuit |
| 🚨 **Emergency Stop**        | Provides immediate test interruption                |
| ⛔ **Automatic Shutdown**     | Removes test power during abnormal conditions       |
| 🔌 **Protected Inputs**      | Protects ESP32 sensing and control interfaces       |
| 📦 **Enclosed Connections**  | Reduces exposure to energized wiring                |
| 🔍 **Fault Monitoring**      | Detects abnormal system conditions                  |

---

## 🚨 Automatic Safety Shutdown

The test is immediately terminated when **any critical stop condition** is detected:

```text
                  ┌─────────────┐
                  │  TEST RUN   │
                  └──────┬──────┘
                         │
          ┌──────────────┼──────────────┐
          │              │              │
          ▼              ▼              ▼
      🔴 MCB Trip    🛑 STOP       🚨 E-STOP
          │              │              │
          └──────────────┼──────────────┘
                         │
                         ▼
                 🔍 Sensor Fault
                         │
                         ▼
                  ⚠️ System Fault
                         │
                         ▼
                ┌────────────────┐
                │ 🛑 TEST POWER  │
                │    OFF         │
                └────────────────┘
```

### Safety Logic

> **Any critical fault → Stop the test → Remove test power → Enter safe state**

The system should never continue a test when its operating condition cannot be reliably determined.

---

## ⚠️ High-Energy Testing

The VOLTORA prototype **does not reproduce professional high-current short-circuit testing**.

Professional high-energy testing requires appropriately engineered:

* ⚡ High-current test infrastructure
* 🔌 Specialized switching equipment
* 📊 High-speed measurement systems
* 🛡️ Protection and interlocking systems
* 📦 Suitable test enclosures
* 👷 Qualified operating procedures

Such infrastructure is outside the scope of the educational prototype.

---

## 🧠 Safety Philosophy

```text
       NORMAL CONDITION
              ↓
         TEST ENABLED
              ↓
       CONTINUOUS MONITORING
              ↓
    ┌─────────┴─────────┐
    │                   │
    ▼                   ▼
 SAFE CONDITION      UNCERTAIN /
    │                FAULT CONDITION
    │                   │
    ▼                   ▼
 CONTINUE TEST       STOP TEST
                        ↓
                  POWER OFF
                        ↓
                   SAFE STATE
```

### 🔑 Core Principle

> ## **“When the system enters an uncertain condition, stop the test.”**

Safety is a fundamental part of the **VOLTORA system architecture**, not simply an additional feature.
