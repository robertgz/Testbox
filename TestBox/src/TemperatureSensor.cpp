#include "Arduino.h"
#include <max6675.h>
#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(int pin_SCK, int pin_CS, int pin_SO)
  : thermocouple(pin_SCK, pin_CS, pin_SO) {
    _temperature_F = 0;
}

void TemperatureSensor::readSensor(void) {
  
 _temperature_F = thermocouple.readFahrenheit();

}

int TemperatureSensor::getTemperatureF(void) {
  TemperatureSensor::readSensor();
  return _temperature_F;

}

void TemperatureSensor::getFormatedOutput(char* charData) {

  sprintf(charData, "Temp: %d F    ", _temperature_F);

}

void TemperatureSensor::getFormatedSerialOutput(char* charData) {

  TemperatureSensor::getFormatedOutput(charData);

}