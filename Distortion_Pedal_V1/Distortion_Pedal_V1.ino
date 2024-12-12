/*
John Poirier and Grant Floyd
Programmable Guitar Pedal
Microcontrollers Lab X
Task: Distortion Pedal
*/

#include <Wire.h> // Library for I2C Communication
#include <Adafruit_ADS1X15.h>  // Library for ADS1115 ADC
#include <Adafruit_MCP4725.h>  // Library for MCP4725 DAC

// Initialize ADC and DAC
Adafruit_ADS1115 adc;
Adafruit_MCP4725 dac;

const int constraint_value = 2500;
void setup() {
    Wire.begin();
    
    // Initialize the ADC
    adc.begin();
    
    // Initialize the DAC
    dac.begin(0x60);  // I2C Address for DAC
    
    // Set the ADC gain to match the expected input signal range
    // GAIN_ONE = +/- 4.096V input range (This is the expected input range after the first stage of Op-Amp Circuit)
    adc.setGain(GAIN_ONE);
    Wire.setClock(400000);
}

void loop() {
    int16_t adcValue = adc.readADC_SingleEnded(0); // Read guitar input from ADC
    uint16_t dacValue = map(adcValue, 0, 32767, 0, 4095); // Map from ADC ranges to DAC ranges
    dacValue = constrain(dacValue, 0, constraint_value); // Limit outuput significantly to get clipping
    dac.setVoltage(dacValue, false); // Set output
}