// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

unsigned long lastUpdateTime = 0;
int lcdUpdateRate = 1000; // in milliseconds

int output_flow = 0;
int output_pressure = 0;
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

    lcd.setCursor( 0, 0 );            // go to the top left corner
    lcd.print("Test Box Sensor Data"); // write this string on the top row

    // output Flow rate
    lcd.setCursor( 0, 1 );            // go to the 2nd row
    lcd.print("Flow: ");
    lcd.print(output_flow);
    lcd.print(" gal/min    ");

    // output Pressure
    lcd.setCursor( 0, 2 );            // go to the third row
    lcd.print("Pres: ");
    lcd.print(output_pressure);
    lcd.print(" x/y    ");

    // output Temperature
    lcd.setCursor( 0, 3 );            // go to the fourth row
    lcd.print("Temp: ");
    lcd.print(output_temperature);
    lcd.print("\xDF""F    ");

    // For testing
    Serial.println("== Diaplay updated ==");
    Serial.print("Flow: ");     Serial.print(output_flow);     Serial.println(" gal/min");
    Serial.print("Pres: ");     Serial.print(output_pressure);     Serial.println(" x/y");
    Serial.print("Temp: ");     Serial.print(output_temperature);     Serial.println(" deg F");

    lastUpdateTime = millis();
  }


}
