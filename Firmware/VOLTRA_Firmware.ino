// ============================================================
// ESP32 AUTOMATIC LOW-VOLTAGE MCB TEST SYSTEM
// ============================================================
//
// Automatic resistance sequence:
//
//       82 ohm
//          |
//          | 5 seconds
//          v
//       20 ohm
//          |
//          | current >= trip threshold
//          v
//       MCB TRIP
//
// 82 ohm at 3.3 V  ≈ 40 mA
// 20 ohm at 3.3 V  ≈ 165 mA
//
// ============================================================


// ---------------- PIN DEFINITIONS ----------------

const int ACS_PIN = 34;
const int VOLTAGE_PIN = 35;

const int START_BUTTON = 18;
const int STOP_BUTTON  = 19;

const int GREEN_LED  = 21;
const int YELLOW_LED = 22;
const int RED_LED    = 23;

const int RELAY_20OHM = 25;
const int RELAY_82OHM = 26;
const int MCB_RELAY   = 27;
const int MAIN_RELAY  = 32;


// ---------------- RELAY LOGIC ----------------

// Most relay modules are active LOW.

const int RELAY_ON  = LOW;
const int RELAY_OFF = HIGH;


// ---------------- ADC SETTINGS ----------------

const float ADC_REFERENCE = 3.3;
const int ADC_MAX = 4095;


// ---------------- ACS712 ----------------
//
// Change this depending on your ACS712.
//
// 5A  = 0.185 V/A
// 20A = 0.100 V/A
// 30A = 0.066 V/A
//
// This code assumes 5A version.

const float ACS_SENSITIVITY = 0.185;


// Because we are using a 10k / 20k divider:
//
// ACS712 OUT
//     |
//    10k
//     |
//     +---- ESP32 ADC
//     |
//    20k
//     |
//    GND
//
// ESP32 receives approximately 2/3 of ACS712 output.
//
// Therefore convert ESP32 ADC voltage back to actual
// ACS712 output voltage using this factor.

const float DIVIDER_FACTOR = 3.0 / 2.0;


// ---------------- TRIP SETTINGS ----------------

// Simulated trip threshold = 100 mA

const float TRIP_CURRENT = 0.100;


// Small current values below this are treated as zero.

const float NOISE_CUTOFF = 0.010;


// Number of consecutive high-current readings required
// before trip.

const int TRIP_CONFIRMATIONS = 5;


// ---------------- TEST TIMES ----------------

const unsigned long TEST_82_TIME = 5000;

const unsigned long RELAY_SETTLE_TIME = 500;


// ---------------- VARIABLES ----------------

float zeroCurrentVoltage = 2.5;

float currentValue = 0.0;

float voltageValue = 0.0;

int tripCounter = 0;

unsigned long testStartTime = 0;

unsigned long stageStartTime = 0;

unsigned long tripTime = 0;

bool testRunning = false;

bool tripped = false;


// ---------------- TEST STATES ----------------

enum TestStage
{
  IDLE,
  TEST_82,
  TEST_20
};

TestStage stage = IDLE;


// ============================================================
// SETUP
// ============================================================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  // Buttons

  pinMode(START_BUTTON, INPUT_PULLUP);
  pinMode(STOP_BUTTON, INPUT_PULLUP);


  // LEDs

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);


  // Relays

  pinMode(RELAY_20OHM, OUTPUT);
  pinMode(RELAY_82OHM, OUTPUT);
  pinMode(MCB_RELAY, OUTPUT);
  pinMode(MAIN_RELAY, OUTPUT);


  // Everything OFF

  allRelaysOff();


  // READY LED

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);


  Serial.println();
  Serial.println("====================================");
  Serial.println(" ESP32 AUTOMATIC MCB TEST SYSTEM");
  Serial.println("====================================");

  Serial.println();
  Serial.println("ACS712 calibration starting...");
  Serial.println("Make sure no current is flowing.");


  calibrateACS712();


  Serial.println("ACS712 calibration completed.");

  Serial.print("Zero point = ");
  Serial.print(zeroCurrentVoltage, 4);
  Serial.println(" V");


  Serial.println();
  Serial.println("SYSTEM READY");
  Serial.println("Press START.");
}


// ============================================================
// LOOP
// ============================================================

void loop()
{

  // ---------------- STOP ----------------

  if (digitalRead(STOP_BUTTON) == LOW)
  {
    stopTest();

    delay(300);
  }


  // ---------------- START ----------------

  if (digitalRead(START_BUTTON) == LOW && !testRunning)
  {
    startTest();

    delay(300);
  }


  // ---------------- TEST ----------------

  if (testRunning)
  {
    runTest();
  }
}


// ============================================================
// START TEST
// ============================================================

void startTest()
{
  Serial.println();
  Serial.println("====================================");
  Serial.println("        AUTOMATIC TEST START");
  Serial.println("====================================");


  testRunning = true;

  tripped = false;

  tripCounter = 0;


  // LEDs

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, LOW);


  // Make sure loads are OFF

  allRelaysOff();

  delay(500);


  // MAIN POWER ON

  digitalWrite(MAIN_RELAY, RELAY_ON);

  Serial.println("Main Power Relay = ON");

  delay(RELAY_SETTLE_TIME);


  // MCB RELAY ON

  digitalWrite(MCB_RELAY, RELAY_ON);

  Serial.println("MCB/Test Relay = ON");

  delay(RELAY_SETTLE_TIME);


  // Start with 82 ohm

  select82Ohm();


  stage = TEST_82;

  testStartTime = millis();

  stageStartTime = millis();


  Serial.println();
  Serial.println("STAGE 1: 82 OHM");

  Serial.println("Expected current ≈ 40 mA");

  Serial.println("Expected result = NO TRIP");
}


// ============================================================
// RUN TEST
// ============================================================

void runTest()
{

  // Read sensors

  currentValue = readCurrent();

  voltageValue = readVoltage();


  // Print readings

  Serial.print("Voltage = ");
  Serial.print(voltageValue, 2);

  Serial.print(" V | Current = ");
  Serial.print(currentValue * 1000.0, 1);

  Serial.print(" mA | ");


  if (stage == TEST_82)
  {
    Serial.println("82 OHM");
  }
  else if (stage == TEST_20)
  {
    Serial.println("20 OHM");
  }


  // ========================================================
  // 82 OHM STAGE
  // ========================================================

  if (stage == TEST_82)
  {

    // If unexpectedly high current occurs,
    // trip immediately.

    if (currentValue >= TRIP_CURRENT)
    {
      tripMCB();

      return;
    }


    // After 5 seconds automatically switch to 20 ohm

    if (millis() - stageStartTime >= TEST_82_TIME)
    {

      Serial.println();
      Serial.println("82 OHM TEST COMPLETE");

      switchTo20Ohm();

      stage = TEST_20;

      stageStartTime = millis();

      tripCounter = 0;


      Serial.println();
      Serial.println("STAGE 2: 20 OHM");

      Serial.println("Expected current ≈ 165 mA");

      Serial.println("Trip threshold = 100 mA");
    }
  }


  // ========================================================
  // 20 OHM STAGE
  // ========================================================

  else if (stage == TEST_20)
  {

    // Check trip threshold

    if (currentValue >= TRIP_CURRENT)
    {
      tripCounter++;

      Serial.print("Trip confirmation ");
      Serial.print(tripCounter);
      Serial.print("/");
      Serial.println(TRIP_CONFIRMATIONS);


      if (tripCounter >= TRIP_CONFIRMATIONS)
      {
        tripMCB();

        return;
      }
    }
    else
    {
      // If current falls below threshold,
      // reset confirmation counter.

      tripCounter = 0;
    }
  }


  delay(100);
}


// ============================================================
// SELECT 82 OHM
// ============================================================

void select82Ohm()
{

  digitalWrite(RELAY_20OHM, RELAY_OFF);

  digitalWrite(RELAY_82OHM, RELAY_OFF);

  delay(200);


  digitalWrite(RELAY_82OHM, RELAY_ON);

  Serial.println("82 OHM relay = ON");
}


// ============================================================
// SWITCH TO 20 OHM
// ============================================================

void switchTo20Ohm()
{

  Serial.println("Changing resistance...");


  // 82 ohm OFF

  digitalWrite(RELAY_82OHM, RELAY_OFF);

  delay(300);


  // 20 ohm ON

  digitalWrite(RELAY_20OHM, RELAY_ON);

  delay(RELAY_SETTLE_TIME);


  Serial.println("82 OHM relay = OFF");

  Serial.println("20 OHM relay = ON");
}


// ============================================================
// READ ACS712
// ============================================================

float readCurrent()
{

  const int samples = 200;

  long totalADC = 0;


  for (int i = 0; i < samples; i++)
  {
    totalADC += analogRead(ACS_PIN);

    delayMicroseconds(100);
  }


  float averageADC =
      totalADC / (float)samples;


  // ESP32 ADC voltage

  float espVoltage =
      averageADC * ADC_REFERENCE / ADC_MAX;


  // Reconstruct original ACS712 output voltage

  float sensorVoltage =
      espVoltage * DIVIDER_FACTOR;


  // Difference from zero-current point

  float voltageDifference =
      sensorVoltage - zeroCurrentVoltage;


  // Current

  float current =
      voltageDifference / ACS_SENSITIVITY;


  // Magnitude

  current = fabs(current);


  // Noise suppression

  if (current < NOISE_CUTOFF)
  {
    current = 0.0;
  }


  return current;
}


// ============================================================
// READ VOLTAGE SENSOR
// ============================================================

float readVoltage()
{

  const int samples = 50;

  long totalADC = 0;


  for (int i = 0; i < samples; i++)
  {
    totalADC += analogRead(VOLTAGE_PIN);

    delayMicroseconds(100);
  }


  float averageADC =
      totalADC / (float)samples;


  float sensorVoltage =
      averageADC * ADC_REFERENCE / ADC_MAX;


  // Typical 0-25V module has approximately 5:1 division.

  float actualVoltage =
      sensorVoltage * 5.0;


  return actualVoltage;
}


// ============================================================
// ACS712 CALIBRATION
// ============================================================

void calibrateACS712()
{

  const int samples = 1000;

  long totalADC = 0;


  // All relays OFF

  allRelaysOff();

  delay(1500);


  for (int i = 0; i < samples; i++)
  {
    totalADC += analogRead(ACS_PIN);

    delay(2);
  }


  float averageADC =
      totalADC / (float)samples;


  float espVoltage =
      averageADC * ADC_REFERENCE / ADC_MAX;


  // Convert ESP32 ADC voltage back to
  // actual ACS712 output voltage.

  zeroCurrentVoltage =
      espVoltage * DIVIDER_FACTOR;
}


// ============================================================
// MCB TRIP
// ============================================================

void tripMCB()
{

  testRunning = false;

  tripped = true;


  tripTime =
      millis() - testStartTime;


  Serial.println();
  Serial.println("====================================");
  Serial.println("            MCB TRIPPED");
  Serial.println("====================================");


  Serial.print("Current = ");

  Serial.print(currentValue * 1000.0, 1);

  Serial.println(" mA");


  Serial.print("Voltage = ");

  Serial.print(voltageValue, 2);

  Serial.println(" V");


  Serial.print("Trip time = ");

  Serial.print(tripTime);

  Serial.println(" ms");


  // MCB OPEN

  digitalWrite(MCB_RELAY, RELAY_OFF);


  // MAIN POWER OFF

  digitalWrite(MAIN_RELAY, RELAY_OFF);


  // LOADS OFF

  digitalWrite(RELAY_20OHM, RELAY_OFF);

  digitalWrite(RELAY_82OHM, RELAY_OFF);


  // LEDs

  digitalWrite(GREEN_LED, LOW);

  digitalWrite(YELLOW_LED, LOW);

  digitalWrite(RED_LED, HIGH);


  stage = IDLE;


  Serial.println("Main Power = OFF");

  Serial.println("MCB Relay = OFF");

  Serial.println("Load Relays = OFF");

  Serial.println("RED LED = TRIP");

  Serial.println("====================================");
}


// ============================================================
// STOP TEST
// ============================================================

void stopTest()
{

  testRunning = false;

  tripped = false;


  allRelaysOff();


  digitalWrite(GREEN_LED, HIGH);

  digitalWrite(YELLOW_LED, LOW);

  digitalWrite(RED_LED, LOW);


  stage = IDLE;


  Serial.println();
  Serial.println("====================================");

  Serial.println("TEST STOPPED");

  Serial.println("ALL RELAYS OFF");

  Serial.println("SYSTEM READY");

  Serial.println("====================================");
}


// ============================================================
// TURN ALL RELAYS OFF
// ============================================================

void allRelaysOff()
{

  digitalWrite(RELAY_20OHM, RELAY_OFF);

  digitalWrite(RELAY_82OHM, RELAY_OFF);

  digitalWrite(MCB_RELAY, RELAY_OFF);

  digitalWrite(MAIN_RELAY, RELAY_OFF);
}// ============================================================
// ESP32 AUTOMATIC LOW-VOLTAGE MCB TEST SYSTEM
// ============================================================
//
// Automatic resistance sequence:
//
//       82 ohm
//          |
//          | 5 seconds
//          v
//       20 ohm
//          |
//          | current >= trip threshold
//          v
//       MCB TRIP
//
// 82 ohm at 3.3 V  ≈ 40 mA
// 20 ohm at 3.3 V  ≈ 165 mA
//
// ============================================================


// ---------------- PIN DEFINITIONS ----------------

const int ACS_PIN = 34;
const int VOLTAGE_PIN = 35;

const int START_BUTTON = 18;
const int STOP_BUTTON  = 19;

const int GREEN_LED  = 21;
const int YELLOW_LED = 22;
const int RED_LED    = 23;

const int RELAY_20OHM = 25;
const int RELAY_82OHM = 26;
const int MCB_RELAY   = 27;
const int MAIN_RELAY  = 32;


// ---------------- RELAY LOGIC ----------------

// Most relay modules are active LOW.

const int RELAY_ON  = LOW;
const int RELAY_OFF = HIGH;


// ---------------- ADC SETTINGS ----------------

const float ADC_REFERENCE = 3.3;
const int ADC_MAX = 4095;


// ---------------- ACS712 ----------------
//
// Change this depending on your ACS712.
//
// 5A  = 0.185 V/A
// 20A = 0.100 V/A
// 30A = 0.066 V/A
//
// This code assumes 5A version.

const float ACS_SENSITIVITY = 0.185;


// Because we are using a 10k / 20k divider:
//
// ACS712 OUT
//     |
//    10k
//     |
//     +---- ESP32 ADC
//     |
//    20k
//     |
//    GND
//
// ESP32 receives approximately 2/3 of ACS712 output.
//
// Therefore convert ESP32 ADC voltage back to actual
// ACS712 output voltage using this factor.

const float DIVIDER_FACTOR = 3.0 / 2.0;


// ---------------- TRIP SETTINGS ----------------

// Simulated trip threshold = 100 mA

const float TRIP_CURRENT = 0.100;


// Small current values below this are treated as zero.

const float NOISE_CUTOFF = 0.010;


// Number of consecutive high-current readings required
// before trip.

const int TRIP_CONFIRMATIONS = 5;


// ---------------- TEST TIMES ----------------

const unsigned long TEST_82_TIME = 5000;

const unsigned long RELAY_SETTLE_TIME = 500;


// ---------------- VARIABLES ----------------

float zeroCurrentVoltage = 2.5;

float currentValue = 0.0;

float voltageValue = 0.0;

int tripCounter = 0;

unsigned long testStartTime = 0;

unsigned long stageStartTime = 0;

unsigned long tripTime = 0;

bool testRunning = false;

bool tripped = false;


// ---------------- TEST STATES ----------------

enum TestStage
{
  IDLE,
  TEST_82,
  TEST_20
};

TestStage stage = IDLE;


// ============================================================
// SETUP
// ============================================================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  // Buttons

  pinMode(START_BUTTON, INPUT_PULLUP);
  pinMode(STOP_BUTTON, INPUT_PULLUP);


  // LEDs

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);


  // Relays

  pinMode(RELAY_20OHM, OUTPUT);
  pinMode(RELAY_82OHM, OUTPUT);
  pinMode(MCB_RELAY, OUTPUT);
  pinMode(MAIN_RELAY, OUTPUT);


  // Everything OFF

  allRelaysOff();


  // READY LED

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);


  Serial.println();
  Serial.println("====================================");
  Serial.println(" ESP32 AUTOMATIC MCB TEST SYSTEM");
  Serial.println("====================================");

  Serial.println();
  Serial.println("ACS712 calibration starting...");
  Serial.println("Make sure no current is flowing.");


  calibrateACS712();


  Serial.println("ACS712 calibration completed.");

  Serial.print("Zero point = ");
  Serial.print(zeroCurrentVoltage, 4);
  Serial.println(" V");


  Serial.println();
  Serial.println("SYSTEM READY");
  Serial.println("Press START.");
}


// ============================================================
// LOOP
// ============================================================

void loop()
{

  // ---------------- STOP ----------------

  if (digitalRead(STOP_BUTTON) == LOW)
  {
    stopTest();

    delay(300);
  }


  // ---------------- START ----------------

  if (digitalRead(START_BUTTON) == LOW && !testRunning)
  {
    startTest();

    delay(300);
  }


  // ---------------- TEST ----------------

  if (testRunning)
  {
    runTest();
  }
}


// ============================================================
// START TEST
// ============================================================

void startTest()
{
  Serial.println();
  Serial.println("====================================");
  Serial.println("        AUTOMATIC TEST START");
  Serial.println("====================================");


  testRunning = true;

  tripped = false;

  tripCounter = 0;


  // LEDs

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, LOW);


  // Make sure loads are OFF

  allRelaysOff();

  delay(500);


  // MAIN POWER ON

  digitalWrite(MAIN_RELAY, RELAY_ON);

  Serial.println("Main Power Relay = ON");

  delay(RELAY_SETTLE_TIME);


  // MCB RELAY ON

  digitalWrite(MCB_RELAY, RELAY_ON);

  Serial.println("MCB/Test Relay = ON");

  delay(RELAY_SETTLE_TIME);


  // Start with 82 ohm

  select82Ohm();


  stage = TEST_82;

  testStartTime = millis();

  stageStartTime = millis();


  Serial.println();
  Serial.println("STAGE 1: 82 OHM");

  Serial.println("Expected current ≈ 40 mA");

  Serial.println("Expected result = NO TRIP");
}


// ============================================================
// RUN TEST
// ============================================================

void runTest()
{

  // Read sensors

  currentValue = readCurrent();

  voltageValue = readVoltage();


  // Print readings

  Serial.print("Voltage = ");
  Serial.print(voltageValue, 2);

  Serial.print(" V | Current = ");
  Serial.print(currentValue * 1000.0, 1);

  Serial.print(" mA | ");


  if (stage == TEST_82)
  {
    Serial.println("82 OHM");
  }
  else if (stage == TEST_20)
  {
    Serial.println("20 OHM");
  }


  // ========================================================
  // 82 OHM STAGE
  // ========================================================

  if (stage == TEST_82)
  {

    // If unexpectedly high current occurs,
    // trip immediately.

    if (currentValue >= TRIP_CURRENT)
    {
      tripMCB();

      return;
    }


    // After 5 seconds automatically switch to 20 ohm

    if (millis() - stageStartTime >= TEST_82_TIME)
    {

      Serial.println();
      Serial.println("82 OHM TEST COMPLETE");

      switchTo20Ohm();

      stage = TEST_20;

      stageStartTime = millis();

      tripCounter = 0;


      Serial.println();
      Serial.println("STAGE 2: 20 OHM");

      Serial.println("Expected current ≈ 165 mA");

      Serial.println("Trip threshold = 100 mA");
    }
  }


  // ========================================================
  // 20 OHM STAGE
  // ========================================================

  else if (stage == TEST_20)
  {

    // Check trip threshold

    if (currentValue >= TRIP_CURRENT)
    {
      tripCounter++;

      Serial.print("Trip confirmation ");
      Serial.print(tripCounter);
      Serial.print("/");
      Serial.println(TRIP_CONFIRMATIONS);


      if (tripCounter >= TRIP_CONFIRMATIONS)
      {
        tripMCB();

        return;
      }
    }
    else
    {
      // If current falls below threshold,
      // reset confirmation counter.

      tripCounter = 0;
    }
  }


  delay(100);
}


// ============================================================
// SELECT 82 OHM
// ============================================================

void select82Ohm()
{

  digitalWrite(RELAY_20OHM, RELAY_OFF);

  digitalWrite(RELAY_82OHM, RELAY_OFF);

  delay(200);


  digitalWrite(RELAY_82OHM, RELAY_ON);

  Serial.println("82 OHM relay = ON");
}


// ============================================================
// SWITCH TO 20 OHM
// ============================================================

void switchTo20Ohm()
{

  Serial.println("Changing resistance...");


  // 82 ohm OFF

  digitalWrite(RELAY_82OHM, RELAY_OFF);

  delay(300);


  // 20 ohm ON

  digitalWrite(RELAY_20OHM, RELAY_ON);

  delay(RELAY_SETTLE_TIME);


  Serial.println("82 OHM relay = OFF");

  Serial.println("20 OHM relay = ON");
}


// ============================================================
// READ ACS712
// ============================================================

float readCurrent()
{

  const int samples = 200;

  long totalADC = 0;


  for (int i = 0; i < samples; i++)
  {
    totalADC += analogRead(ACS_PIN);

    delayMicroseconds(100);
  }


  float averageADC =
      totalADC / (float)samples;


  // ESP32 ADC voltage

  float espVoltage =
      averageADC * ADC_REFERENCE / ADC_MAX;


  // Reconstruct original ACS712 output voltage

  float sensorVoltage =
      espVoltage * DIVIDER_FACTOR;


  // Difference from zero-current point

  float voltageDifference =
      sensorVoltage - zeroCurrentVoltage;


  // Current

  float current =
      voltageDifference / ACS_SENSITIVITY;


  // Magnitude

  current = fabs(current);


  // Noise suppression

  if (current < NOISE_CUTOFF)
  {
    current = 0.0;
  }


  return current;
}


// ============================================================
// READ VOLTAGE SENSOR
// ============================================================

float readVoltage()
{

  const int samples = 50;

  long totalADC = 0;


  for (int i = 0; i < samples; i++)
  {
    totalADC += analogRead(VOLTAGE_PIN);

    delayMicroseconds(100);
  }


  float averageADC =
      totalADC / (float)samples;


  float sensorVoltage =
      averageADC * ADC_REFERENCE / ADC_MAX;


  // Typical 0-25V module has approximately 5:1 division.

  float actualVoltage =
      sensorVoltage * 5.0;


  return actualVoltage;
}


// ============================================================
// ACS712 CALIBRATION
// ============================================================

void calibrateACS712()
{

  const int samples = 1000;

  long totalADC = 0;


  // All relays OFF

  allRelaysOff();

  delay(1500);


  for (int i = 0; i < samples; i++)
  {
    totalADC += analogRead(ACS_PIN);

    delay(2);
  }


  float averageADC =
      totalADC / (float)samples;


  float espVoltage =
      averageADC * ADC_REFERENCE / ADC_MAX;


  // Convert ESP32 ADC voltage back to
  // actual ACS712 output voltage.

  zeroCurrentVoltage =
      espVoltage * DIVIDER_FACTOR;
}


// ============================================================
// MCB TRIP
// ============================================================

void tripMCB()
{

  testRunning = false;

  tripped = true;


  tripTime =
      millis() - testStartTime;


  Serial.println();
  Serial.println("====================================");
  Serial.println("            MCB TRIPPED");
  Serial.println("====================================");


  Serial.print("Current = ");

  Serial.print(currentValue * 1000.0, 1);

  Serial.println(" mA");


  Serial.print("Voltage = ");

  Serial.print(voltageValue, 2);

  Serial.println(" V");


  Serial.print("Trip time = ");

  Serial.print(tripTime);

  Serial.println(" ms");


  // MCB OPEN

  digitalWrite(MCB_RELAY, RELAY_OFF);


  // MAIN POWER OFF

  digitalWrite(MAIN_RELAY, RELAY_OFF);


  // LOADS OFF

  digitalWrite(RELAY_20OHM, RELAY_OFF);

  digitalWrite(RELAY_82OHM, RELAY_OFF);


  // LEDs

  digitalWrite(GREEN_LED, LOW);

  digitalWrite(YELLOW_LED, LOW);

  digitalWrite(RED_LED, HIGH);


  stage = IDLE;


  Serial.println("Main Power = OFF");

  Serial.println("MCB Relay = OFF");

  Serial.println("Load Relays = OFF");

  Serial.println("RED LED = TRIP");

  Serial.println("====================================");
}


// ============================================================
// STOP TEST
// ============================================================

void stopTest()
{

  testRunning = false;

  tripped = false;


  allRelaysOff();


  digitalWrite(GREEN_LED, HIGH);

  digitalWrite(YELLOW_LED, LOW);

  digitalWrite(RED_LED, LOW);


  stage = IDLE;


  Serial.println();
  Serial.println("====================================");

  Serial.println("TEST STOPPED");

  Serial.println("ALL RELAYS OFF");

  Serial.println("SYSTEM READY");

  Serial.println("====================================");
}


// ============================================================
// TURN ALL RELAYS OFF
// ============================================================

void allRelaysOff()
{

  digitalWrite(RELAY_20OHM, RELAY_OFF);

  digitalWrite(RELAY_82OHM, RELAY_OFF);

  digitalWrite(MCB_RELAY, RELAY_OFF);

  digitalWrite(MAIN_RELAY, RELAY_OFF);
}