# ⚡ VOLTRA – Testing

## 1. Testing Overview

Testing was performed to verify the response of the VOLTRA system under different resistive load conditions.

The primary objective was to determine whether the measured current remained below or exceeded the defined **40 mA trip threshold**.

Two load conditions were tested:

- **82 Ω**
- **20 Ω**

---

## 2. Test Procedure

The following procedure was followed:

1. Power the testing circuit.
2. Select the required resistive load.
3. Measure the current and voltage values.
4. Monitor the measured current continuously.
5. Compare the current with the **40 mA threshold**.
6. Detect the trip condition when the threshold is reached or exceeded.
7. Record the trip current, voltage, and response time.
8. Compare the results for different load conditions.

---

## 3. Test Conditions

| Parameter | Value |
|---|---:|
| Trip Threshold | 40 mA |
| Load 1 | 82 Ω |
| Load 2 | 20 Ω |

---

## 4. Test Cases

### Test Case 1 – 82 Ω

**Expected Condition:** No trip

The measured current remained below the 40 mA threshold.

- Maximum Current: **33.9 mA**
- Result: **NOT TRIPPED**

### Test Case 2 – 20 Ω

**Expected Condition:** Trip

The measured current exceeded the 40 mA threshold.

- Maximum Current: **42.9 mA**
- Trip Voltage: **24.38 V**
- Trip Time: **406 ms**
- Result: **TRIPPED**

---

## 5. Test Results

| Test Case | Load | Maximum Current | Threshold | Result |
|---|---:|---:|---:|---|
| TC01 | 82 Ω | 33.9 mA | 40 mA | NOT TRIPPED |
| TC02 | 20 Ω | 42.9 mA | 40 mA | TRIPPED |

---

## 6. Verification

The test results demonstrate that the system correctly distinguishes between the two tested load conditions.

The 82 Ω condition remained below the defined threshold, while the 20 Ω condition exceeded the threshold and produced a trip indication.

---

## 7. Testing Evidence

The project repository contains:

- Hardware circuit photographs
- Test output photographs
- Firmware output screenshots
- Software-generated graphs
- Hardware demonstration video
- Overall project explanation video

---

## 8. Testing Summary

The testing successfully demonstrated the intended threshold-based detection behavior of the VOLTRA prototype under the selected test conditions.