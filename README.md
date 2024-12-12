# Programmable Guitar Pedal
John Poirier and Grant Floyd\
CMPE 3815, Microcrontroller Systems\
Final Project

## Overview
This project creates a guitar pedal using an Arduino UNO that can be programmed to give effects, such as delay, distortion, loop, etc. This project uses an Arduino UNO, a two-stage Op-Amp circuit to modify the signal from the guitar and to the amp, and
an ADC and DAC. This project posed significant challenges, as the output was unable to match the frequency of the input, causing significant unwanted distortion in the output.

## Components
1x Arduino Uno\
1x ADS1115 ADC\
1x MCP4725 DAC\
2x 1uF Capacitor\
Various Resistors\
5x AD741 Operational Amplifier\
2x 9V Batery\
2x Zener Diode\
1x Guitar\
1x Guitar Amp

## Contents
### ADC_DAC_Test
Code to test the functionality and communication of the ADC and DAC with the Arduino

### Audio_Passthrough_V1
Code to directly passthrough audio from the guitar through the arduino and to the amp without affecting the signal. Does not utilize the ADC and DAC. Used for testing the processing circuit before implementing the ADC and DAC.

### Audio_Passthrough_V2
Code to directly passthrough audio from the guitar through the arduino and to the amp without affecting the signal. Utilizes the ADC and DAC.

### Delay_Pedal_V1
Code to cause a delay of the input signal from the guitar to the output signal to the amp.

### Distortion_Pedal_V1
Code that causes clipping of the input signal from the guitar to cause a distortion effect at the output to the amp.

### Loop_Pedal_V1
Code that records the input from the guitar, and stores that recording on an SD card. The stored audio file can then be played back in a loop. 

### Input_Output_Processing_Circuits_LTSpice
LTspice file containing the schematics of the input and output processing circuits used for this project. 



