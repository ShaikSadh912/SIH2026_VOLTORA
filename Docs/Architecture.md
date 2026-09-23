# System Architecture

## ⚡ VOLTRA System Architecture

The **VOLTRA Automated High-Current Protection Testing Platform** is designed as a modular system that integrates **controlled power delivery, switching, electrical sensing, embedded control, protection detection, timing, and software-based data analysis**.

The architecture is divided into independent functional layers so that each section performs a specific task while communicating with the main controller.

> **Power → Switching → Measurement → Control → Decision → Analysis**

---

## 🏗️ High-Level Architecture

```text
                         ┌─────────────────────────────┐
                         │        🖥️ PYTHON HMI        │
                         │                             │
                         │ • Data Visualization        │
                         │ • Graph Generation          │
                         │ • Result Analysis           │
                         │ • Test Report Information   │
                         └──────────────┬──────────────┘
                                        │
                                  USB / Serial
                                        │
                                        ▼
                         ┌─────────────────────────────┐
                         │       🎛️ ARDUINO UNO        │
                         │        MAIN CONTROLLER      │
                         │                             │
                         │ • Sensor Acquisition        │
                         │ • Threshold Monitoring      │
                         │ • Relay Control             │
                         │ • Trip Detection            │
                         │ • Trip-Time Calculation     │
                         │ • Status Control            │
                         └───────┬─────────────┬───────┘
                                 │             │
                           Control Signals   Sensor Data
                                 │             │
                    ┌────────────▼───┐   ┌─────▼────────────┐
                    │ 🔌 RELAY       │   │ 📊 MEASUREMENT   │
                    │    MODULE      │   │     SYSTEM       │
                    │                │   │                  │
                    │ • Power ON/OFF │   │ • ACS712         │
                    │ • Load Select  │   │ • Voltage Sensor │
                    │ • Shutdown     │   │ • Trip Timing    │
                    └────────┬───────┘   └────────┬─────────┘
                             │                    │
                             └──────────┬─────────┘
                                        │
                                        ▼
                         ┌─────────────────────────────┐
                         │       ⚡ TEST POWER PATH    │
                         │                             │
                         │  12-0-12 V Transformer      │
                         │            ↓                │
                         │       Protection            │
                         │            ↓                │
                         │       Main Relay            │
                         │            ↓                │
                         │    Selected Resistive Load  │
                         │       82Ω / 20Ω             │
                         │            ↓                │
                         │        ACS712               │
                         │            ↓                │
                         │    Protection / Return      │
                         └─────────────────────────────┘