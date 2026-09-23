# ⚡ VOLTRA – Results

## 1. Overview

The VOLTRA prototype was evaluated using two resistive load conditions to demonstrate different current responses.

A **40 mA trip threshold** was used for evaluating the test conditions.

---

## 2. Experimental Results

| Parameter | 82 Ω | 20 Ω |
|---|---:|---:|
| Maximum Current | 33.9 mA | 42.9 mA |
| Trip Threshold | 40 mA | 40 mA |
| Result | NOT TRIPPED | TRIPPED |
| Trip Voltage | — | 24.38 V |
| Trip Time | — | 406 ms |

---

## 3. 82 Ω Result

The 82 Ω load produced a maximum measured current of **33.9 mA**.

Since this value remained below the **40 mA threshold**, the system remained in the non-trip condition.

**Final Result: NOT TRIPPED**

---

## 4. 20 Ω Result

The 20 Ω load produced a maximum measured current of **42.9 mA**.

The measured current exceeded the **40 mA threshold**, resulting in a trip condition.

Recorded parameters:

- **Trip Current:** 42.9 mA
- **Trip Voltage:** 24.38 V
- **Trip Time:** 406 ms

**Final Result: TRIPPED**

---

## 5. Comparative Analysis

The results demonstrate the change in system response with different load conditions.

```text
82 Ω
33.9 mA
   │
   │  Below 40 mA
   ▼
NOT TRIPPED


20 Ω
42.9 mA
   │
   │  Above 40 mA
   ▼
TRIPPED