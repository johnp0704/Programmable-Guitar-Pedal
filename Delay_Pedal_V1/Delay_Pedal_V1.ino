/*
Grant Floyd and John Poirier
Programmable Guitar Pedal
Microcontrollers Lab X
Task: Delay Pedal
*/

#include <Wire.h> // Library for I2C Communication
#include <Adafruit_ADS1X15.h>  // Library for ADS1115 ADC
#include <Adafruit_MCP4725.h>  // Library for MCP4725 DAC

// Initialize ADC and DAC
Adafruit_ADS1115 adc;
Adafruit_MCP4725 dac;

const int bufferSize = 512; // Buffer size
int16_t delayBuffer[bufferSize];
int bufferIndex = 0;
int delayTime = 125; // Adjusted delay time in milliseconds

const int sampleRate = 4000; // Define sampling rate (Hz)

void setup() {
    Wire.begin();
    
    // Initialize the ADC (ADS1115)
    adc.begin();
    adc.setGain(GAIN_ONE); // Set the gain to match expected input signal range
    
    // Initialize the DAC (MCP4725)
    dac.begin(0x60);  // I2C address for MCP4725
    
    Wire.setClock(400000); // Set I2C clock speed
    
    // Initialize delay buffer with zeros
    for (int i = 0; i < bufferSize; i++) {
        delayBuffer[i] = 0;
    }
}

void loop() {
    int16_t adcValue = adc.readADC_SingleEnded(0); // Read input from ADC
    delayBuffer[bufferIndex] = adcValue; // Store in Buffer
    
    // Calculate delayed output signal
    int delayedIndex = (bufferIndex + bufferSize - (delayTime * sampleRate / 1000)) % bufferSize;
    int16_t delayedValue = delayBuffer[delayedIndex];
    
    uint16_t dacValue = map(delayedValue, -32768, 32767, 0, 4095); // Map from ADC to DAC values
    dacValue = constrain(dacValue, 0, 4095); // Ensure safe output
    dac.setVoltage(dacValue, false); // Output to DAC
    
    bufferIndex = (bufferIndex + 1) % bufferSize; // Increment buffer index
    delayMicroseconds(1000000 / sampleRate); // Delay to match sampling rate
}