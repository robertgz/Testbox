#include "Arduino.h"
#include "FlowSensor.h"

FlowSensor::FlowSensor(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
  _flowLastMeasuredTime = millis();
  _flow = 0.0f;

  attachInterrupt(digitalPinToInterrupt(_pin), FlowSensor::_pulseCounter, FALLING); // used
  // attachInterrupt(digitalPinToInterrupt(_pin), _pulseCounter, RISING); // not used
}

volatile unsigned long FlowSensor::_pulseCount = 0;
volatile unsigned long FlowSensor::_totalPulsesDetected = 0;

void FlowSensor::_pulseCounter() {
  FlowSensor::_pulseCount++;
  FlowSensor::_totalPulsesDetected++;
}

void FlowSensor::readSensor() {
  unsigned long flowMeasurementElapsedTime;
  unsigned long pulses;

  noInterrupts();
  pulses = FlowSensor::_pulseCount;
  FlowSensor::_pulseCount = 0;
  flowMeasurementElapsedTime = millis() - _flowLastMeasuredTime;
  _flowLastMeasuredTime = millis();
  interrupts();

  // Pulse constant:  0.46mL/Pulse = 0.00046L/Pulse
  // compute flow rate in gallons/minute
  float Liters = 0.00046 * pulses;
  float LitersPerMs = Liters / flowMeasurementElapsedTime;
  float LitersPerMinute = Liters / (flowMeasurementElapsedTime / 60000.0); 
  float GalllonsPerMinute = (Liters / 3.785412) / (flowMeasurementElapsedTime / 60000.0); 
  _flow = GalllonsPerMinute;
}

float FlowSensor::getFlowRate(){
  FlowSensor::readSensor();
  return _flow;
}

void FlowSensor::getFormatedOutput(char* charData) {

  char flowStr[15]; 
  dtostrf(_flow, 7, 2, flowStr); 
  sprintf(charData, "Flow: %-6d gal/min", flowStr);
}

void FlowSensor::getFormatedSerialOutput(char* charData) {

  FlowSensor::getFormatedOutput(charData);
  sprintf(charData, "%s, Total Pulses Detected: %d", charData, FlowSensor::_totalPulsesDetected);
}