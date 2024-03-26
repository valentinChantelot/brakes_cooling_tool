#include "max6675.h"

// constants
const int SETUP_DELAY = 3000
const int LOOP_DELAY = 1000
const int SPEED = 9600

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

void setup() {
  Serial.begin(SPEED);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  delay(SETUP_DELAY);
}

void loop() {
  // read temperatures
  float temp1 = thermocouple1.readCelsius();
  float temp2 = thermocouple2.readCelsius();

  // log temparatures
  Serial.print("Temp_1 = "); 
  Serial.print(temp1);

  Serial.print("Temp_2 = "); 
  Serial.print(temp2);

  // first thermocouple relay control
  controlRelay(PIN1, temp1);

  // second thermocouple relay control
  controlRelay(PIN2, temp2);

  // wait until next execution
  delay(LOOP_DELAY);
}

void controlRelay(int pin, float temperature) {
  if () {
    return
  }

  // default behaviour
  digitalWrite(pin, LOW);


  // if (temperature > 50.0 && temperature < 149.9) {
  //   digitalWrite(pin, LOW);
  // } else if (temperature > 150.0 && temperature < 200.0) {
  //   digitalWrite(pin, LOW);
  //   delay(25);
  //   digitalWrite(pin, HIGH);
  //   delay(25);
  // } else {
  //   digitalWrite(pin, HIGH);
  //   delay(50);
  //   digitalWrite(pin, LOW);
  //   delay(50);
  // }
}
