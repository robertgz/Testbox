// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "FlowSensor.h"

// int lcd_pin_sda = A4;
// int lcd_pin_scl = A5;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
// LiquidCrystal_I2C lcd(0x27, 2, 1, 0,
//                       4, 5, 6, 7, 
//                       3, POSITIVE);

unsigned long previousUpdateTime;
const unsigned long updateRate = 1000; // in milliseconds

const int flowSensorPin = 2;
FlowSensor flowSensor(flowSensorPin);

const int pressureSensorPin = A0;
int output_pressure = 0;
int pressure_sensor_reading = 0;

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

    output_flow = flowSensor.getFlowRate(); // new

    output_pressure = getPressure();
    // output_temperature = getTemperature();

    updateLCD(output_flow, output_pressure, output_temperature);

    // For testing
    outputToSerial(output_flow, output_pressure, pressure_sensor_reading, output_temperature);

    previousUpdateTime = millis();
  }
}

int getPressure(void) {  
  // 300 PSI sensor outputs range from .5 Volts to 4.5 Volts
  //   .5 V =   0 PSI
  //  4.5 V = 300 PSI
  pressure_sensor_reading = analogRead(pressureSensorPin); // show about 100 at baseline

  // Keep the sensor reading as an int and retain precision
  int sensor_reading_mV = map(pressure_sensor_reading, 0, 1023, 0, 5000); 
  //   500 mV =   0 PSI
  //  4500 mV = 300 PSI  
  int pressure_PSI = map(sensor_reading_mV, 500, 4500, 0, 300);

  return pressure_PSI;    
}

void updateLCD(float flow, int pressure, int temperature) {
    lcd.setCursor( 0, 0 );            // go to the first row
    lcd.print("Test Box Sensor Data");

    // output Flow rate
    // needs testing
    char flowOutput[41];
    flowSensor.getFormatedOutput(flowOutput, flow);
    lcd.setCursor( 0, 1 );            // go to the second row
    lcd.print(flowOutput);
     // needs testing

    // output Pressure
    lcd.setCursor( 0, 2 );            // go to the third row
    lcd.print("Pres: ");
    lcd.print(pressure);
    lcd.print(" PSI    ");

    // output Temperature
    lcd.setCursor( 0, 3 );            // go to the fourth row
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print("\xDF""F    ");
}

void outputToSerial(float flow, int pressure, int pressure_sensor, int temperature){
    Serial.println("== Diaplay updated ==");

    char flowOutput[41]; // needs testing
    flowSensor.getFormatedOutput(flowOutput, flow); // new
    Serial.print(flowOutput);
    
    Serial.print("Pres: ");     
    Serial.print(pressure);     
    Serial.print(" PSI"); 
    Serial.print(", Raw sensor reading: ");
    Serial.println(pressure_sensor);
    
    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.println(" deg F");
}