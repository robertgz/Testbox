#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "Arduino.h"

class TemperatureSensor {
  public:
    TemperatureSensor(int pin_SCK, int pin_CS, int pin_SO);
    void readSensor(void);
    int getTemperatureF(void);

    void getFormatedOutput(char* charData);
    void getFormatedSerialOutput(char* charData);

  private:
    int _temperature_F;
    MAX6675 thermocouple;
};

#endif