#include "max6675.h"

// pins for first thermocouple
int so1Pin = 22;// SO1=Serial Out
int cs1Pin = 2;// CS1 = chip select CS pin
int sck1Pin = 3;// SCK1 = Serial Clock pin

// pins for 2nd thermocouple
int so2Pin = 24;// SO1=Serial Out
int cs2Pin = 4;// CS1 = chip select CS pin
int sck2Pin = 5;// SCK1 = Serial Clock pin

MAX6675 thermocouple1(sck1Pin, cs1Pin, so1Pin);// watch video for details
MAX6675 thermocouple2(sck2Pin, cs2Pin, so2Pin);// watch video for details

void setup() {
    Serial.begin(9600);
    // use Arduino pins
    pinMode(11, OUTPUT);// set pin 11 as output    
    pinMode(10, OUTPUT);// set pin 10 as output    

    delay(3000);// give time to read the display at the beginning
}

void loop() {
  // basic readout test, just print the current temp
  
   Serial.print("C_1 = "); 
   Serial.print (thermocouple1.readCelsius());
   Serial.print(" F_1 = ");
   Serial.println(thermocouple1.readFahrenheit());

   Serial.print("C_2 = "); 
   Serial.print (thermocouple2.readCelsius());
   Serial.print(" F_2 = ");
   Serial.println(thermocouple2.readFahrenheit());

// if temperature goes between 50.0C and 149.9C, turn the relay ON
   if(thermocouple1.readCelsius() > 50.00 && thermocouple1.readCelsius() < 149.90){
    digitalWrite(11, LOW);// set pin 11 LOW
   } else{
        digitalWrite(11, HIGH);// set pin 11 HIGH
        delay(50);
        digitalWrite(11, LOW);
        delay(50);
   }
   // if temperature goes between 150.0C and 200.0C, turn the relay ON
   if(thermocouple1.readCelsius() > 150.00 && thermocouple1.readCelsius() < 200.00){
        digitalWrite(11, LOW);// set pin 11 LOW
   } else{
        digitalWrite(11, HIGH);// set pin 11 HIGH
        delay(25);
        digitalWrite(11, LOW);
        delay(25);
   }
// if temperature goes between 50.0C and 149.90C, turn the relay ON
    if(thermocouple2.readCelsius() > 50.00 && thermocouple2.readCelsius() < 149.90){
        digitalWrite(10, LOW);// set pin 10 LOW
   } else{
        digitalWrite(10, HIGH);// set pin 10 HIGH
        delay(50);
        digitalWrite(10, LOW);
        delay(50);
   }           
   // if temperature goes between 150.0C and 200.0C, turn the relay ON
    if(thermocouple2.readCelsius() > 150.00 && thermocouple2.readCelsius() < 200.00){
        digitalWrite(10, LOW);// set pin 10 LOW
   } else{
        digitalWrite(10, HIGH);// set pin 10 HIGH
        delay(25);
        digitalWrite(10, LOW);
        delay(25);
   } 
             
   delay(1000);
}