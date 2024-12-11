/* John Poirier and Grant Floyd
Programmable Guitar Pedal
Microcontrollers Lab X
Task: ADC and DAC test
*/

#include <Wire.h> // Library for I2C Communication
#include <Adafruit_ADS1X15.h> // Library for ADS1115 ADC
#include <Adafruit_MCP4725.h> // Library for MCP4725 DAC

Adafruit_ADS1115 adc;
Adafruit_MCP4725 dac;

void setup() {
  Wire.begin();
  
  // Initialize ADC
  adc.begin();
  adc.setGain(GAIN_ONE); // Set gain value
  
  // Initialize DAC
  dac.begin(0x60); // I2C address for MCP4725
  
  // Test Output
  dac.setVoltage(2048, false); 
  delay(500);
}

void loop() {
  int16_t adcValue = adc.readADC_SingleEnded(0);  // Read from ADC

  uint16_t dacValue = map(adcValue, -32768, 32767, 0, 4095);  // Map ADC range to DAC range

  dac.setVoltage(dacValue, false); // Read and output to DAC
  
  delay(100);
}
