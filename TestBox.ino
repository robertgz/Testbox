// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "FlowSensor.h"
#include "PressureSensor.h"

// int lcd_pin_sda = A4;
// int lcd_pin_scl = A5;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
// LiquidCrystal_I2C lcd(0x27, 2, 1, 0,
//                       4, 5, 6, 7, 
//                       3, POSITIVE);

unsigned long previousUpdateTime;
const unsigned long updateRate = 1000; // in milliseconds

const int flowSensorPin = 2;
const int pressureSensorPin = A0;

FlowSensor flowSensor(flowSensorPin);
PressureSensor pressureSensor(pressureSensorPin);

int output_temperature = 0;

void setup() {  
  Serial.begin(9600);
  Serial.println("Starting program!");

  lcd.begin(20,4);               // initialize the lcd  

  previousUpdateTime = millis();
}

void loop() {
  unsigned long elapsedTime = millis() - previousUpdateTime;
  elapsedTime = abs(elapsedTime);

  float output_flow = 0.0f;

  // update every updateRate milliseconds
  if (elapsedTime >= updateRate) {

    flowSensor.readFlowRate();
    pressureSensor.readPressure();
    // output_temperature = getTemperature();

    updateLCD(output_temperature);

    // For testing
    outputToSerial(output_temperature);

    previousUpdateTime = millis();
  }
}

void updateLCD(int temperature) {
    lcd.setCursor( 0, 0 );            // go to the first row
    lcd.print("Test Box Sensor Data");

    // output Flow rate
    // needs testing
    char flowOutput[41];
    flowSensor.getFormatedOutput(flowOutput);
    lcd.setCursor( 0, 1 );            // go to the second row
    lcd.print(flowOutput);
    // needs testing

    // output Pressure
    char pressureOutput[41];
    pressureSensor.getFormatedOutput(pressureOutput);
    lcd.setCursor( 0, 2 );            // go to the third row
    lcd.println(pressureOutput);

    // output Temperature
    lcd.setCursor( 0, 3 );            // go to the fourth row
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print("\xDF""F    ");
}

void outputToSerial(int temperature){
    Serial.println("== Diaplay updated ==");

    char flowOutput[41]; // needs testing
    flowSensor.getFormatedSerialOutput(flowOutput); // new
    Serial.println(flowOutput);
    
    // output Pressure
    char pressureOutput[41];
    pressureSensor.getFormatedSerialOutput(pressureOutput);
    Serial.println(pressureOutput);
    
    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.println(" deg F");
}