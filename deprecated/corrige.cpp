#include "max6675.h"

// pins for first thermocouple
int so1Pin = 22;
int cs1Pin = 2;
int sck1Pin = 3;

// pins for 2nd thermocouple
int so2Pin = 24;
int cs2Pin = 4;
int sck2Pin = 5;

// init thermocouples
MAX6675 thermocouple1(sck1Pin, cs1Pin, so1Pin);
MAX6675 thermocouple2(sck2Pin, cs2Pin, so2Pin);

void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  delay(3000);
}

void loop() {
  // read temperatures
  float temp1 = thermocouple1.readCelsius();
  float temp2 = thermocouple2.readCelsius();

  // log temparatures
  Serial.print("C_1 = "); 
  Serial.print(temp1);
  Serial.print(" F_1 = ");
  Serial.println(thermocouple1.readFahrenheit());

  Serial.print("C_2 = "); 
  Serial.print(temp2);
  Serial.print(" F_2 = ");
  Serial.println(thermocouple2.readFahrenheit());

  // first thermocouple relay control
  controlRelay(11, temp1);

  // second thermocouple relay control
  controlRelay(10, temp2);

  delay(1000);
}

void controlRelay(int pin, float temperature) {
  if (temperature > 50.0 && temperature < 149.9) {
    digitalWrite(pin, LOW);
  } else if (temperature > 150.0 && temperature < 200.0) {
    digitalWrite(pin, LOW);
    delay(25);
    digitalWrite(pin, HIGH);
    delay(25);
  } else {
    digitalWrite(pin, HIGH);
    delay(50);
    digitalWrite(pin, LOW);
    delay(50);
  }
}
