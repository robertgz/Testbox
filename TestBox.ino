// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

unsigned long lastUpdateTime = 0;
int lcdUpdateRate = 1000; // in milliseconds

int output_flow = 0;

int pressure_sensor_pin = A0;
int output_pressure = 0;
int pressure_sensor_reading = 0;

int output_temperature = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting program!");
  
  lcd.begin(20,4);               // initialize the lcd  
}

void loop() {
  unsigned long offsetTime = millis() - lastUpdateTime;
  offsetTime = abs(offsetTime);

  // update display only every lcdUpdateRate milliseconds
  if (offsetTime > lcdUpdateRate) { 

    lcd.setCursor( 0, 0 );            // go to the first row
    lcd.print("Test Box Sensor Data");

    // output Flow rate
    lcd.setCursor( 0, 1 );            // go to the second row
    lcd.print("Flow: ");
    lcd.print(output_flow);
    lcd.print(" gal/min    ");

    // output Pressure
    output_pressure = getPressure();
    lcd.setCursor( 0, 2 );            // go to the third row
    lcd.print("Pres: ");
    lcd.print(output_pressure);
    lcd.print(" PSI    ");

    // output Temperature
    lcd.setCursor( 0, 3 );            // go to the fourth row
    lcd.print("Temp: ");
    lcd.print(output_temperature);
    lcd.print("\xDF""F    ");

    // For testing
    outputToSerial();

    lastUpdateTime = millis();
  }
}

int getPressure(void) {  
  // 300 PSI sensor outputs range from .5 Volts to 4.5 Volts
  //   .5 V =   0 PSI
  //  4.5 V = 300 PSI
  pressure_sensor_reading = analogRead(pressure_sensor_pin); // show about 100 at baseline

  // Keep the sensor reading as an int and retain precision
  int sensor_reading_mV = map(pressure_sensor_reading, 0, 1023, 0, 5000); 
  //   500 mV =   0 PSI
  //  4500 mV = 300 PSI  
  int pressure_PSI = map(sensor_reading_mV, 500, 4500, 0, 300);

  return pressure_PSI;    
}

void outputToSerial(void){
    Serial.println("== Diaplay updated ==");
    Serial.print("Flow: ");
    Serial.print(output_flow);
    Serial.println(" gal/min");
    
    Serial.print("Pres: ");     
    Serial.print(output_pressure);     
    Serial.print(" PSI"); 
    Serial.print(", Raw sensor reading: ");
    Serial.println(pressure_sensor_reading);
    
    Serial.print("Temp: ");
    Serial.print(output_temperature);
    Serial.println(" deg F");
}