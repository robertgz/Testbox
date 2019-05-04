#include "Arduino.h"
#include "FlowSensor.h"

FlowSensor::FlowSensor(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
  _flowLastMeasuredTime = millis(); 

  attachInterrupt(digitalPinToInterrupt(_pin), FlowSensor::_pulseCounter, FALLING); // used
  // attachInterrupt(digitalPinToInterrupt(_pin), _pulseCounter, RISING); // not used
}

volatile unsigned long FlowSensor::_pulseCount = 0;

void FlowSensor::_pulseCounter() {
  FlowSensor::_pulseCount++;
}

float FlowSensor::getFlowRate() {
  unsigned long flowMeasurementElapsedTime;
  unsigned long pulses;

  noInterrupts();
  pulses = FlowSensor::_pulseCount;
  FlowSensor::_pulseCount = 0;
  flowMeasurementElapsedTime = millis() - _flowLastMeasuredTime;
  _flowLastMeasuredTime = millis();
  interrupts();

  // Pulse constant:  0.46mL/Pulse = 0.00046L/Pulse
  // compute flow rate to gallons/minute
  float Liters = 0.00046 * pulses;
  float LitersPerMs = Liters / flowMeasurementElapsedTime;
  float LitersPerMinute = Liters / (flowMeasurementElapsedTime / 60000.0); 
  float GalllonsPerMinute = (Liters / 3.785412) / (flowMeasurementElapsedTime / 60000.0); 

  return GalllonsPerMinute;
}

void FlowSensor::getFormatedOutput(char* charData, float flow) {

  char flowStr[15]; 
  dtostrf(flow, 7, 2, flowStr); 
  sprintf(charData, "Flow: %-6d gal/min", flowStr);

  return;
}