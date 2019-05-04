#ifndef FLOWSENSOR_H
#define FLOWSENSOR_H

#include "Arduino.h"

class FlowSensor {
  public:
    FlowSensor(int pin);
    void readFlowRate();
    float getFlowRate();
    void getFormatedOutput(char* charData);
    void getFormatedSerialOutput(char* charData);

  private:
    int _pin;
    unsigned long _flowLastMeasuredTime; // time of last measured flow
    float _flow;

    static volatile unsigned long _pulseCount;
    static volatile unsigned long _totalPulsesDetected;
    static void _pulseCounter();
};

#endif