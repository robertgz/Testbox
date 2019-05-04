#include "Arduino.h"
#include "PressureSensor.h"

PressureSensor::PressureSensor(int pin) {
  _pin = pin;
  _pressure_in_PSI = 0;
  _pressure_sensor_in_MV = 0;
  _pressure_sensor_reading = 0;
}

void PressureSensor::readPressure(void) {
  // 300 PSI sensor outputs range from .5 Volts to 4.5 Volts
  //   .5 V =   0 PSI
  //  4.5 V = 300 PSI
  _pressure_sensor_reading = analogRead(_pin); // show about 100 at baseline

  // Keep the sensor reading as an int and retain precision
  _pressure_sensor_in_MV = map(_pressure_sensor_reading, 0, 1023, 0, 5000); 
  //   500 mV =   0 PSI
  //  4500 mV = 300 PSI  
  _pressure_in_PSI = map(_pressure_sensor_in_MV, 500, 4500, 0, 300);
  
}

int PressureSensor::getPressure(void) {
  PressureSensor::readPressure();
  return _pressure_in_PSI;
}

void PressureSensor::getFormatedOutput(char* charData) {

  sprintf(charData, "Pres: %d PSI    ", _pressure_in_PSI);

}

void PressureSensor::getFormatedSerialOutput(char* charData) {

  PressureSensor::getFormatedOutput(charData);
  sprintf(charData, "%s, Raw sensor reading: %d, in MV: %d", charData, _pressure_sensor_reading, _pressure_sensor_in_MV);

}