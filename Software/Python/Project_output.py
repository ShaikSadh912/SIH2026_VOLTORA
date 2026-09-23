import matplotlib.pyplot as plt
from datetime import datetime

# ============================================================
# VOLTORA TEST DATA
# ============================================================

TRIP_THRESHOLD = 40.0  # mA

# ------------------------------------------------------------
# 82 OHM TEST - NOT TRIPPED
# ------------------------------------------------------------

load_82 = "82 Ω"

current_82 = [
    26.3, 20.1, 26.4, 26.8, 27.8,
    25.7, 33.9, 30.0, 24.4, 30.5,
    24.4, 28.4, 31.5, 26.6, 21.2,
    23.4, 27.1, 27.3, 22.0, 28.4
]

voltage_82 = [
    24.99, 24.71, 24.45, 24.03, 23.61,
    23.44, 23.53, 23.92, 24.65, 24.99,
    25.00, 24.87, 24.57, 24.24, 23.77,
    23.49, 23.44, 23.70, 24.30, 24.89
]


# ------------------------------------------------------------
# 20 OHM TEST - TRIPPED
# ------------------------------------------------------------

load_20 = "20 Ω"

current_20 = [
    11.2, 21.5, 20.4, 15.4, 26.5,
    24.4, 20.4, 30.5, 28.4, 42.9
]

voltage_20 = [
    23.67, 23.45, 23.48, 23.78, 24.47,
    24.94, 25.00, 24.95, 24.63, 24.38
]

trip_time_20 = 406  # ms


# ============================================================
# CALCULATIONS
# ============================================================

avg_current_82 = sum(current_82) / len(current_82)
min_current_82 = min(current_82)
max_current_82 = max(current_82)

avg_voltage_82 = sum(voltage_82) / len(voltage_82)
min_voltage_82 = min(voltage_82)
max_voltage_82 = max(voltage_82)

avg_current_20 = sum(current_20) / len(current_20)
min_current_20 = min(current_20)
max_current_20 = max(current_20)

avg_voltage_20 = sum(voltage_20) / len(voltage_20)
min_voltage_20 = min(voltage_20)
max_voltage_20 = max(voltage_20)

# Determine trip condition
tripped_82 = max_current_82 >= TRIP_THRESHOLD
tripped_20 = max_current_20 >= TRIP_THRESHOLD


# ============================================================
# TERMINAL REPORT
# ============================================================

print("\n")
print("=" * 60)
print("              VOLTORA TEST REPORT")
print("=" * 60)

print("\nTest Threshold : {:.1f} mA".format(TRIP_THRESHOLD))

print("\n" + "-" * 60)
print("                    82 Ω LOAD TEST")
print("-" * 60)

print("Number of Samples     :", len(current_82))
print("Average Current       : {:.2f} mA".format(avg_current_82))
print("Minimum Current       : {:.2f} mA".format(min_current_82))
print("Maximum Current       : {:.2f} mA".format(max_current_82))

print("\nAverage Voltage       : {:.2f} V".format(avg_voltage_82))
print("Minimum Voltage       : {:.2f} V".format(min_voltage_82))
print("Maximum Voltage       : {:.2f} V".format(max_voltage_82))

print("\nThreshold             : {:.2f} mA".format(TRIP_THRESHOLD))

if tripped_82:
    print("Status                : TRIPPED")
else:
    print("Status                : NOT TRIPPED")

print("\nObservation:")
print(
    "The maximum current of {:.2f} mA remained below the "
    "{:.2f} mA trip threshold.".format(
        max_current_82, TRIP_THRESHOLD
    )
)

print("\n" + "-" * 60)
print("                    20 Ω LOAD TEST")
print("-" * 60)

print("Number of Samples     :", len(current_20))
print("Average Current       : {:.2f} mA".format(avg_current_20))
print("Minimum Current       : {:.2f} mA".format(min_current_20))
print("Maximum Current       : {:.2f} mA".format(max_current_20))

print("\nAverage Voltage       : {:.2f} V".format(avg_voltage_20))
print("Minimum Voltage       : {:.2f} V".format(min_voltage_20))
print("Maximum Voltage       : {:.2f} V".format(max_voltage_20))

print("\nThreshold             : {:.2f} mA".format(TRIP_THRESHOLD))

if tripped_20:
    print("Status                : TRIPPED")
    print("Trip Current          : {:.2f} mA".format(max_current_20))
    print("Trip Voltage          : {:.2f} V".format(voltage_20[-1]))
    print("Trip Time             : {} ms".format(trip_time_20))
else:
    print("Status                : NOT TRIPPED")

print("\nObservation:")

if tripped_20:
    print(
        "The current reached {:.2f} mA, exceeding the "
        "{:.2f} mA trip threshold by {:.2f} mA.".format(
            max_current_20,
            TRIP_THRESHOLD,
            max_current_20 - TRIP_THRESHOLD
        )
    )

    print(
        "The recorded trip time was {} ms.".format(
            trip_time_20
        )
    )


# ============================================================
# FINAL COMPARISON REPORT
# ============================================================

print("\n")
print("=" * 60)
print("              FINAL COMPARISON REPORT")
print("=" * 60)

print("\n{:<12} {:<18} {:<18}".format(
    "Load", "Maximum Current", "Result"
))

print("-" * 60)

print("{:<12} {:<18} {:<18}".format(
    "82 Ω",
    "{:.2f} mA".format(max_current_82),
    "NOT TRIPPED"
))

print("{:<12} {:<18} {:<18}".format(
    "20 Ω",
    "{:.2f} mA".format(max_current_20),
    "TRIPPED"
))

print("-" * 60)

print("\nThreshold : {:.2f} mA".format(TRIP_THRESHOLD))

print("\nFINAL OBSERVATION")

print(
    "\n82 Ω Load:"
    "\n  Maximum current = {:.2f} mA"
    "\n  Current remained below the {:.2f} mA threshold."
    "\n  Result = NOT TRIPPED".format(
        max_current_82,
        TRIP_THRESHOLD
    )
)

print(
    "\n20 Ω Load:"
    "\n  Maximum current = {:.2f} mA"
    "\n  Current exceeded the {:.2f} mA threshold."
    "\n  Trip current = {:.2f} mA"
    "\n  Trip time = {} ms"
    "\n  Result = TRIPPED".format(
        max_current_20,
        TRIP_THRESHOLD,
        max_current_20,
        trip_time_20
    )
)

print("\n" + "=" * 60)
print("              END OF TEST REPORT")
print("=" * 60)


# ============================================================
# GRAPH 1 - 82 OHM CURRENT
# ============================================================

samples_82 = list(range(1, len(current_82) + 1))

plt.figure(figsize=(10, 5))

plt.plot(
    samples_82,
    current_82,
    marker="o",
    linewidth=2,
    label="Current"
)

plt.axhline(
    y=TRIP_THRESHOLD,
    linestyle="--",
    linewidth=2,
    label="Trip Threshold = 40 mA"
)

plt.title("82 Ω Load - Current Measurement")
plt.xlabel("Sample Number")
plt.ylabel("Current (mA)")
plt.grid(True, alpha=0.3)
plt.legend()

plt.tight_layout()


# ============================================================
# GRAPH 2 - 82 OHM VOLTAGE
# ============================================================

plt.figure(figsize=(10, 5))

plt.plot(
    samples_82,
    voltage_82,
    marker="o",
    linewidth=2,
    label="Voltage"
)

plt.title("82 Ω Load - Voltage Measurement")
plt.xlabel("Sample Number")
plt.ylabel("Voltage (V)")
plt.grid(True, alpha=0.3)
plt.legend()

plt.tight_layout()


# ============================================================
# GRAPH 3 - 20 OHM CURRENT
# ============================================================

samples_20 = list(range(1, len(current_20) + 1))

plt.figure(figsize=(10, 5))

plt.plot(
    samples_20,
    current_20,
    marker="o",
    linewidth=2,
    label="Current"
)

plt.axhline(
    y=TRIP_THRESHOLD,
    linestyle="--",
    linewidth=2,
    label="Trip Threshold = 40 mA"
)

# Highlight trip point
trip_index = current_20.index(max(current_20)) + 1

plt.scatter(
    trip_index,
    max_current_20,
    s=100,
    zorder=5,
    label="Trip Point = 42.9 mA"
)

plt.annotate(
    "TRIP\n42.9 mA",
    xy=(trip_index, max_current_20),
    xytext=(trip_index - 2, max_current_20 + 5),
    arrowprops=dict(arrowstyle="->"),
    fontsize=11
)

plt.title("20 Ω Load - Current Measurement")
plt.xlabel("Sample Number")
plt.ylabel("Current (mA)")
plt.grid(True, alpha=0.3)
plt.legend()

plt.tight_layout()


# ============================================================
# GRAPH 4 - 20 OHM VOLTAGE
# ============================================================

plt.figure(figsize=(10, 5))

plt.plot(
    samples_20,
    voltage_20,
    marker="o",
    linewidth=2,
    label="Voltage"
)

plt.scatter(
    len(voltage_20),
    voltage_20[-1],
    s=100,
    zorder=5,
    label="Trip Voltage = {:.2f} V".format(voltage_20[-1])
)

plt.annotate(
    "{:.2f} V".format(voltage_20[-1]),
    xy=(len(voltage_20), voltage_20[-1]),
    xytext=(len(voltage_20) - 2, voltage_20[-1] - 1),
    arrowprops=dict(arrowstyle="->"),
    fontsize=11
)

plt.title("20 Ω Load - Voltage Measurement")
plt.xlabel("Sample Number")
plt.ylabel("Voltage (V)")
plt.grid(True, alpha=0.3)
plt.legend()

plt.tight_layout()


# ============================================================
# GRAPH 5 - FINAL COMPARISON
# ============================================================

loads = ["82 Ω", "20 Ω"]
maximum_currents = [max_current_82, max_current_20]

plt.figure(figsize=(9, 5))

bars = plt.bar(
    loads,
    maximum_currents,
    width=0.5
)

plt.axhline(
    y=TRIP_THRESHOLD,
    linestyle="--",
    linewidth=2,
    label="Trip Threshold = 40 mA"
)

plt.title("Final Comparison - Maximum Current")
plt.xlabel("Load Resistance")
plt.ylabel("Maximum Current (mA)")

for bar, value in zip(bars, maximum_currents):
    plt.text(
        bar.get_x() + bar.get_width() / 2,
        value + 1,
        "{:.1f} mA".format(value),
        ha="center",
        fontsize=11
    )

plt.grid(axis="y", alpha=0.3)
plt.legend()

plt.tight_layout()


# ============================================================
# DISPLAY ALL GRAPHS
# ============================================================

plt.show()