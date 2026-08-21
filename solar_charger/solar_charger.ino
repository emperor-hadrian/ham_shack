/* Maximum power point tracking boost converter for charging LifePO4 12.8V Battery with solar panels
Pins:
9. MOSFET for boost converter
A0. Battery voltage reading with voltage divider
SDA and SCL pins also used for INA219

PWM using analogWrite which proves to be about 500 Hz

More info in MD file*/

// Include INA219 library
#include <Adafruit_INA219.h>
// Create a current sensor object
Adafruit_INA219 ina219;

#define DEBUG_PERIOD_MS 1000
#define POT_PIN A1

// Ratio between current power and previous best power (or other way) that triggers re-calibration power sweep
#define POWER_ERROR_RATIO 1.2

// Power sweep settings, in microseconds
#define SWEEP_START 0
#define SWEEP_STEP 10
#define SWEEP_STEPS 19

// Boost converter settings
#define PERIOD_US 200// 5 KHz
#define MOSFET_PIN 9

// Interval for reading the INA219
// Used for both normal mode (checking if the power changes), and for sweep mode
#define POWER_SAMPLE_PERIOD_US 10000

// Duty cycle in ms
int duty_cycle_us;
// Best power from most recent calibration, if power goes too far from this then re-calibrate
float latest_sweep_best_power_mw;
// Array for storing corresponding power for duty cycle
float power_sweep_data[SWEEP_STEPS];
bool mosfet_is_on;
float current_power_mw;

// Timing flags
unsigned long current_micros;
unsigned long last_power_sample_micros;
unsigned long last_debug_millis;
unsigned long power_duration;

// Flags
bool flag_sweep_mode;
int sweep_current_step;// For indexing into `power_sweep_data`

void setup() {
  ina219.begin();
  ina219.setCalibration_16V_400mA();
  pinMode(MOSFET_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  mosfet_is_on = false;
  digitalWrite(MOSFET_PIN, mosfet_is_on);
  duty_cycle_us = 50;
  Serial.begin(9600);
  Serial.println("Start of program");
  last_debug_millis = millis();
}

void loop() {
  current_micros = micros();
  // Determine if the mosfet should be on or not
  int boost_cycle_remainder = current_micros % PERIOD_US;
  mosfet_is_on = boost_cycle_remainder < analogRead(POT_PIN)/4;//boost_cycle_remainder < duty_cycle_us;
  analogWrite(MOSFET_PIN, analogRead(POT_PIN)/4 - 70);//digitalWrite(MOSFET_PIN, mosfet_is_on);
  // Check last power sample
  if((current_micros - last_power_sample_micros) > POWER_SAMPLE_PERIOD_US) {
    last_power_sample_micros += POWER_SAMPLE_PERIOD_US;
    unsigned long power_start_us = micros();
    current_power_mw = ina219.getPower_mW();
    power_duration = micros() - power_start_us;
    // Sweep or normal mode
    if(flag_sweep_mode) {
      // Time to increase the duty cycle and record previous duty cycle avg power
      power_sweep_data[sweep_current_step] = current_power_mw;
      sweep_current_step++;
      duty_cycle_us = SWEEP_START + (SWEEP_STEP * sweep_current_step);
      // If end of sweep
      if(sweep_current_step == SWEEP_STEPS) {
        // Set flag
        flag_sweep_mode = false;
        // Find highest value and corresponding index in `power_sweep_data`
        int best_i = 0;
        latest_sweep_best_power_mw = 0;
        for(int i = 0; i < SWEEP_STEPS; i++) {
          if(power_sweep_data[i] > latest_sweep_best_power_mw) {
            best_i = i;
            latest_sweep_best_power_mw = power_sweep_data[i];
          }
        }
        // Find duty cycle from `best_i`
        duty_cycle_us = SWEEP_START + (SWEEP_STEP * best_i);
        Serial.println("Power sweep done, duty cycle: " + String(duty_cycle_us) + " us, Power: " + String(latest_sweep_best_power_mw) + " mW");
      }
    }
    // Monitor power
    else {
      // Tiny additions to prevent division by 0
      /*if((current_power_mw + 0.1) / (latest_sweep_best_power_mw + 0.1) > POWER_ERROR_RATIO || (latest_sweep_best_power_mw + 0.1) / (current_power_mw + 0.1) > POWER_ERROR_RATIO) {
        // Enter sweep mode, setup all the flags
        flag_sweep_mode = true;
        sweep_current_step = 0;
        duty_cycle_us = SWEEP_START;
      }*/
    }
  }
  if(millis() - last_debug_millis > DEBUG_PERIOD_MS) {
    float v = ina219.getBusVoltage_V();
    float i = ina219.getCurrent_mA();
    Serial.println("V: " + String(v) + ", I (mA): " + String(i) + ", Power measurement time (us): " + String(power_duration) + ", Pot: " + String(analogRead(POT_PIN)/4));
    last_debug_millis = millis();
  }
}
