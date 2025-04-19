#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <max6675.h>

/** Pin thermocouple 1 */
#define THERMOCOUPLE_1_SCK 5
#define THERMOCOUPLE_1_CS 6
#define THERMOCOUPLE_1_DO 7

/** Pin thermocouple 2 */
#define THERMOCOUPLE_2_SCK 2
#define THERMOCOUPLE_2_CS 3
#define THERMOCOUPLE_2_DO 4

/** Config Shield datalogger - NE PAS TOUCHER, c'est tout dans la doc */
#define SD_CHIP_SELECT 10
#define RTC_SDA A4
#define RTC_SCL A5

//test

/** PIN OUT pilotage électrovane - Signal pilotage */
#define RELAY1_PIN 8
#define RELAY2_PIN 9

/** Init thermocouple */
MAX6675 thermocouple1(THERMOCOUPLE_1_SCK, THERMOCOUPLE_1_CS, THERMOCOUPLE_1_DO);
MAX6675 thermocouple2(THERMOCOUPLE_2_SCK, THERMOCOUPLE_2_CS, THERMOCOUPLE_2_DO);

/** Init écriture du fichier */
File dataFile;
char logFileName[32]; 

bool initSD() {
  if (!SD.begin(10,11,12,13)) {
    Serial.println("Échec de l'initialisation de la carte !");
    return false;
  }
  Serial.println("Carte SD initialisée.");
  return true;
}

void createLogFileHeader() {
  dataFile = SD.open(logFileName, FILE_WRITE);
  if (dataFile) {
    dataFile.print("Temp1");
    dataFile.print(";");
    dataFile.println("Temp2");
    dataFile.close();
  } else {
    Serial.println("Impossible d'écrire les en-têtes dans le fichier !");
  }
}

void createLogFile() {
  int fileIndex = 1;

  // Cherche un nom de fichier disponible
  while (fileIndex < 100) { 
    snprintf(logFileName, sizeof(logFileName), "data%d.csv", fileIndex);
    if (!SD.exists(logFileName)) {
      break;
    }
    fileIndex++;
  }

  dataFile = SD.open(logFileName, FILE_WRITE);
  if (dataFile) {
    Serial.print("Fichier ");
    Serial.print(logFileName);
    Serial.println(" créé.");
    dataFile.close();
  } else {
    Serial.print("Erreur lors de la création du fichier : ");
    Serial.println(logFileName);
  }
}

void logData(float temp1, float temp2) {
  dataFile = SD.open(logFileName, FILE_WRITE);
  if (dataFile) {
    dataFile.print(temp1, 2);
    dataFile.print(";");
    dataFile.println(temp2, 2);
    dataFile.close();
  } else {
    Serial.print("Erreur d’ouverture du fichier : ");
    Serial.println(logFileName);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  Wire.begin();

  if (!initSD()) {
    Serial.println("Erreur SD, arrêt du setup.");
    return;
  }

  createLogFile(); 
  createLogFileHeader();

  Serial.println("Initialisation terminée. Système prêt.");
  delay(3000);
}

void loop() {
  float temp1 = thermocouple1.readCelsius();
  float temp2 = thermocouple2.readCelsius();

  // Contrôle du relais 1 en fonction de la température de la thermocouple 1
  if (temp1 > 350 && temp1 < 450) {
    digitalWrite(RELAY1_PIN, HIGH);
    delay(100);
    digitalWrite(RELAY1_PIN, LOW);
  } else if (temp1 > 450.01 && temp1 < 900.00) {
    digitalWrite(RELAY1_PIN, HIGH);
    delay(400);
    digitalWrite(RELAY1_PIN, LOW);
  }

  // Contrôle du relais 2 en fonction de la température de la thermocouple 2
  if (temp2 > 350 && temp2 < 450) {
    digitalWrite(RELAY2_PIN, HIGH);
    delay(100);
    digitalWrite(RELAY2_PIN, LOW);
  } else if (temp2 > 450.01 && temp2 < 900.00) {
    digitalWrite(RELAY2_PIN, HIGH);
    delay(400);
    digitalWrite(RELAY2_PIN, LOW);
  }


  Serial.print(temp1);
  Serial.print(" , ");
  Serial.println(temp2);

  if(temp1 > 80 || temp2 > 80) {
    logData(temp1, temp2);
  }

  delay(2000); 
}

