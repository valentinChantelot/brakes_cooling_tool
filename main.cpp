#include <ArduinoThread.h>
#include "max6675.h"

// constants
const int SPEED = 9600

const int SETUP_DELAY = 3000
const int LOOP_DELAY = 0
const int CONTROL_RELAY_NO_ACTION_DELAY = 1000
const int CONTROL_RELAY_QUICK_DELAY = 50
const int CONTROL_RELAY_SLOW_DELAY = 100

const float MINIMUM_TRIGGER_TEMP = 50.0
const float MAXIMUM_TRIGGER_TEMP = 100.0

// pins for first thermocouple
const int PIN1 = 11
int so1Pin = 22;
int cs1Pin = 2;
int sck1Pin = 3;

// pins for 2nd thermocouple
const int PIN2 = 10
int so2Pin = 24;
int cs2Pin = 4;
int sck2Pin = 5;

// init thermocouples
MAX6675 thermocouple1(sck1Pin, cs1Pin, so1Pin);
MAX6675 thermocouple2(sck2Pin, cs2Pin, so2Pin);

// init thermocouples thread (so the code for both is executed in parallel)
Thread thermocouple1Thread;
Thread thermocouple2Thread;

void setup() {
  Serial.begin(SPEED);

  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);

  thermocouple1Thread.onRun([] {
    // read temperatures
    float temp1 = thermocouple1.readCelsius();

    // log temparatures
    Serial.print("Temp_1 = "); 
    Serial.print(temp1);

    // actual relay control
    controlRelay(PIN1, thermocouple1.readCelsius());
  });

  thermocouple2Thread.onRun([] {
    // read temperatures
    float temp2 = thermocouple2.readCelsius();
    
    // log temparatures
    Serial.print("Temp_2 = "); 
    Serial.print(temp2);

    // actual relay control
    controlRelay(PIN2, thermocouple2.readCelsius());
  });

  thermocouple1Thread.setInterval(LOOP_DELAY);
  thermocouple2Thread.setInterval(LOOP_DELAY);

  thermocouple1Thread.setNow();
  thermocouple2Thread.setNow();

  delay(SETUP_DELAY);
}

void loop() {
  myThread1.run();
  myThread2.run();
}

void controlRelay(int pin, float temperature, ) {
  if (temperature >= MINIMUM_TRIGGER_TEMP && temperature <= (MAXIMUM_TRIGGER_TEMP - 0.1)) {
    digitalWrite(pin, HIGH);
    delay(CONTROL_RELAY_QUICK_DELAY);

    digitalWrite(pin, LOW);
    delay(CONTROL_RELAY_SLOW_DELAY);
    return
  }

  if (temperature >= MAXIMUM_TRIGGER_TEMP) {
    digitalWrite(pin, HIGH);
    delay(CONTROL_RELAY_QUICK_DELAY);

    digitalWrite(pin, LOW);
    delay(CONTROL_RELAY_QUICK_DELAY);
    return
  }

  // default behaviour - No piloting
  digitalWrite(pin, LOW);
  delay(CONTROL_RELAY_NO_ACTION_DELAY);
  return
}
