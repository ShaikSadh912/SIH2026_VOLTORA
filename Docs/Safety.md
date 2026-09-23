# Safety

## 🛡️ Safety First

Electrical testing requires careful control of **energy, switching, measurement, and fault conditions**.

**VOLTRA** is designed as a **low-voltage, current-limited educational demonstrator**, with safety incorporated into the test workflow and system architecture.

---

## 🔐 Built-In Safety Measures

| Safety Feature | Purpose |
|---|---|
| 🔒 **Low-Voltage Operation** | Limits electrical energy in the prototype |
| ⚡ **Current-Limited Source** | Restricts available test current |
| 🛡️ **Fuse Protection** | Provides overcurrent protection |
| 🎛️ **Controlled Switching** | Enables controlled energization of the test circuit |
| 🚨 **Emergency Stop** | Provides immediate test interruption |
| ⛔ **Automatic Shutdown** | Removes test power during abnormal conditions |
| 🔌 **Protected Inputs** | Protects Arduino UNO sensing and control interfaces |
| 📦 **Enclosed Connections** | Reduces exposure to energized wiring |
| 🔍 **Fault Monitoring** | Detects abnormal system conditions |

---

## 🚨 Automatic Safety Shutdown

The test is immediately terminated when **any critical stop condition** is detected.

```text
                  ┌─────────────┐
                  │  TEST RUN   │
                  └──────┬──────┘
                         │
          ┌──────────────┼──────────────┐
          │              │              │
          ▼              ▼              ▼
      🔴 Trip        🛑 STOP       🚨 E-STOP
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
                │      OFF       │
                └────────────────┘