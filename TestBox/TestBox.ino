// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <max6675.h>

#include "src\FlowSensor.h"
#include "src\PressureSensor.h"
#include "src\TemperatureSensor.h"

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

unsigned long previousUpdateTime;
const unsigned long updateRate = 1000; // in milliseconds

const int flowSensorPin = 2;
const int pressureSensorPin = A0;
const int tempSensorPinSCK = 9;
const int tempSensorPinCS = 13;
const int tempSensorPinSO = 10;

FlowSensor flowSensor(flowSensorPin);
PressureSensor pressureSensor(pressureSensorPin);
TemperatureSensor temperatureSensor(tempSensorPinSCK, tempSensorPinCS, tempSensorPinSO);

void setup() {  
  Serial.begin(9600);
  Serial.println("Starting program!");

  lcd.begin(20,4);               // initialize the lcd  

  previousUpdateTime = millis();
}

void loop() {
  unsigned long elapsedTime = millis() - previousUpdateTime;
  elapsedTime = abs(elapsedTime);

  // read sensors and display output every updateRate milliseconds
  if (elapsedTime >= updateRate) {

    flowSensor.readSensor();
    pressureSensor.readSensor();
    temperatureSensor.readSensor();

    updateLCD();
    outputToSerial(); // For debugging

    previousUpdateTime = millis();
  }
}

void updateLCD() {
    lcd.setCursor( 0, 0 );            // go to the first row
    lcd.print("Test Box Sensor Data");

    char flowOutput[41];
    flowSensor.getFormatedOutput(flowOutput);
    lcd.setCursor( 0, 1 );            // go to the second row
    lcd.print(flowOutput);

    char pressureOutput[41];
    pressureSensor.getFormatedOutput(pressureOutput);
    lcd.setCursor( 0, 2 );            // go to the third row
    lcd.print(pressureOutput);

    char temperatureOutput[41];
    temperatureSensor.getFormatedOutput(temperatureOutput);
    lcd.setCursor( 0, 3 );            // go to the fourth row
    lcd.print(temperatureOutput);
}

void outputToSerial(){
    Serial.println("== Display updated ==");

    char flowOutput[41];
    flowSensor.getFormatedSerialOutput(flowOutput);
    Serial.println(flowOutput);
    
    char pressureOutput[41];
    pressureSensor.getFormatedSerialOutput(pressureOutput);
    Serial.println(pressureOutput);
    
    char temperatureOutput[41];
    temperatureSensor.getFormatedSerialOutput(temperatureOutput);
    Serial.println(temperatureOutput);

    temperatureSensor.readSensor(); // not sure why this is needed
}