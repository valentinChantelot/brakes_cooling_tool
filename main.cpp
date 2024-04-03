#include <MAX6675.h>
#include <Thread.h>
/**
 * From library ArduinoThread by Ivan Seidel
 * To install it. Go here : https://github.com/ivanseidel/ArduinoThread/archive/master.zip
 * It will download a zip file
 * From Arduino IDE, Sketch > Include Library > Add .ZIP library
 * Select the downloaded zip file, then Sketch > Include Library > ArduinoThread to add it to the file
 * Remove StaticThreadController and ThreadController, we do not need these files
 */

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
int PIN_1 = 11;
int SO1_PIN = 22;
int CS1_PIN = 2;
int SCK1_PIN = 3;

// // pins for 2nd thermocouple
int PIN_2 = 10;
int SO2_PIN = 24;
int CS2_PIN = 4;
int SCK2_PIN = 5;

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

  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);

  // thread logic for 1rst thermocouple control
  thermocouple1Thread.onRun([]
    {
    float temp1 = thermocouple1.getTemperature();
    controlRelay(PIN_1, temp1); 
    });

  // thread logic for 2nd thermocouple control
  thermocouple2Thread.onRun([]
                            {
    float temp2 = thermocouple2.getTemperature();
    controlRelay(PIN_2, temp2); });

  // thread logic for 1rst thermocouple logs
  log_thermocouple1Thread.onRun([]
                                {
    float temp1 = thermocouple1.getTemperature();
    Serial.print("Temp_1 = ");
    Serial.print(temp1); });

  // thread logic for 2nd thermocouple logs
  log_thermocouple2Thread.onRun([]
                                {
    float temp2 = thermocouple2.getTemperature();
    Serial.print("Temp_2 = "); 
    Serial.print(temp2); });

  thermocouple1Thread.setInterval(LOOP_CONTROL_DELAY);
  thermocouple2Thread.setInterval(LOOP_CONTROL_DELAY);

  log_thermocouple1Thread.setInterval(LOOP_LOG_DELAY);
  log_thermocouple2Thread.setInterval(LOOP_LOG_DELAY);

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
  
  // brakes watering opened until next check
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
