
#define CLK 9
#define DBIT 10 // so
#define CS 13

#include <SoftwareSerial.h>

int v = 0;
float Ctemp, Ftemp;

void setup()   {
  Serial.begin(9600);
  pinMode(CLK, OUTPUT);
  pinMode(DBIT, INPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  digitalWrite(CLK, LOW);
}

void loop()   {
  v = spiRead();
  if (v == -1)   {
    Serial.print("No sensor \n");
  }
  else   {
    Ctemp =  v * 0.25;
    Ftemp = (Ctemp * 9 / 5) + 32;
    Serial.println(Ftemp);
   // Serial.print("\n");
  }
  delay(100);
}

int spiRead()   {
  int value = 0;
  digitalWrite(CS,LOW);
  delay(2);
  digitalWrite(CS,HIGH);
  delay(220);

  /* Read the chip and return the raw temperature value */
  /* Bring CS pin low to allow us to read the data from
   the conversion process */

  digitalWrite(CS,LOW);
  /* Cycle the clock for dummy bit 15 */
  digitalWrite(CLK,HIGH);
  delay(1);
  digitalWrite(CLK,LOW);

  /*
   Read bits 14-3 from MAX6675 for the Temp. Loop for each bit reading
   the value and storing the final value in 'temp'
   */

  for (int i=14; i>=0; i--) {
    digitalWrite(CLK,HIGH);
    value += digitalRead(DBIT) << i;
    digitalWrite(CLK,LOW);
  }
  // check bit D2 if HIGH no sensor
  if ((value & 0x04) == 0x04) return -1;

  // shift right three places
  return value >> 3;
}

MAX6675 Thermal Couple amp with Type K sensor.