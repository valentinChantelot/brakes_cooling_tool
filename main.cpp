#include <ArduinoThread.h>
#include "max6675.h"

// constants
const int SPEED = 9600;

const int SETUP_DELAY = 3000;
const int LOOP_CONTROL_DELAY = 0; // How many time (in ms) between each controlRelay execution ?
const int LOOP_LOG_DELAY = 1000;  // How many time (in ms) between each log ?

const int CONTROL_RELAY_NO_ACTION_DELAY = 1000;
const int CONTROL_RELAY_QUICK_DELAY = 50;
const int CONTROL_RELAY_SLOW_DELAY = 100;

const float MINIMUM_TRIGGER_TEMP = 50.0;
const float MAXIMUM_TRIGGER_TEMP = 100.0;

// pins for first thermocouple
const int PIN1 = 11;
const int SO1_PIN = 22;
const int CS1_PIN = 2;
const int SCK1_PIN = 3;

// pins for 2nd thermocouple
const int PIN2 = 10;
const int SO2_PIN = 24;
const int CS2_PIN = 4;
const int SCK2_PIN = 5;

// init thermocouples
MAX6675 thermocouple1(SCK1_PIN, CS1_PIN, SO1_PIN);
MAX6675 thermocouple2(SCK2_PIN, CS2_PIN, SO2_PIN);

// init thermocouples thread (so the code for both is executed in parallel)
Thread thermocouple1Thread;
Thread thermocouple2Thread;

// init logs thread (so the code for both is executed in parallel)
Thread log_thermocouple1Thread;
Thread log_thermocouple2Thread;

void setup()
{
  Serial.begin(SPEED);

  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);

  thermocouple1Thread.onRun([]
                            {
    // read temperatures
    float temp1 = thermocouple1.readCelsius();
    // actual relay control
    controlRelay(PIN1, temp1); });

  thermocouple2Thread.onRun([]
                            {
    // read temperatures
    float temp2 = thermocouple2.readCelsius();

    // actual relay control
    controlRelay(PIN2, temp2); });

  log_thermocouple1Thread.onRun([]
                                {
    // read temperatures
    float temp1 = thermocouple1.readCelsius();

    // log temperatures
    Serial.print("Temp_1 = ");
    Serial.print(temp1); });

  log_thermocouple2Thread.onRun([]
                                {
    // read temperatures
    float temp2 = thermocouple2.readCelsius();
    
    // log temperatures
    Serial.print("Temp_2 = "); 
    Serial.print(temp2); });

  thermocouple1Thread.setInterval(LOOP_CONTROL_DELAY);
  thermocouple2Thread.setInterval(LOOP_CONTROL_DELAY);

  log_thermocouple1Thread.setInterval(LOOP_LOG_DELAY);
  log_thermocouple2Thread.setInterval(LOOP_LOG_DELAY);

  thermocouple1Thread.setNow();
  thermocouple2Thread.setNow();

  log_thermocouple1Thread.setNow();
  log_thermocouple2Thread.setNow();

  delay(SETUP_DELAY);
}

void loop()
{
  thermocouple1Thread.run();
  thermocouple2Thread.run();

  log_thermocouple1Thread.run();
  log_thermocouple2Thread.run();
}

void controlRelay(int pin, float temperature)
{
  // need a bit of piloting
  if (temperature >= MINIMUM_TRIGGER_TEMP && temperature <= (MAXIMUM_TRIGGER_TEMP - 0.1))
  {
    digitalWrite(pin, HIGH);
    delay(CONTROL_RELAY_QUICK_DELAY);

    digitalWrite(pin, LOW);
    delay(CONTROL_RELAY_SLOW_DELAY);
    return;
  }

  // need a lot of piloting
  if (temperature >= MAXIMUM_TRIGGER_TEMP)
  {
    digitalWrite(pin, HIGH);
    delay(CONTROL_RELAY_QUICK_DELAY);

    digitalWrite(pin, LOW);
    delay(CONTROL_RELAY_QUICK_DELAY);
    return;
  }

  // default behaviour - No piloting
  digitalWrite(pin, LOW);
  delay(CONTROL_RELAY_NO_ACTION_DELAY);
  return;
}
