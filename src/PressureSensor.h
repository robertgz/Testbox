#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#include "Arduino.h"

class PressureSensor {
  public:
    PressureSensor(int pin);
    void readSensor(void);
    int getPressure(void);

    void getFormatedOutput(char* charData);
    void getFormatedSerialOutput(char* charData);

  private:
    int _pin;
    int _pressure_sensor_reading;
    int _pressure_sensor_in_MV;
    int _pressure_in_PSI;
};

#endif