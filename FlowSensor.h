#ifndef FLOWSENSOR_H
#define FLOWSENSOR_H

#include "Arduino.h"

class FlowSensor {
  public:
    FlowSensor(int pin);
    float getFlowRate();
    void getFormatedOutput(char* charData, float flow);

  private:
    int _pin;
    unsigned long _flowLastMeasuredTime; // time of last measured flow

    static volatile unsigned long _pulseCount;
    static void _pulseCounter();
};

#endif