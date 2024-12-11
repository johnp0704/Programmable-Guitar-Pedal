/*
John Poirier and Grant Floyd
Programmable Guitar Pedal
Microcontrollers Lab X
Task: Audio Passthrough without ADC or DAC (Arduino and Op-Amp circuit only)
*/

const int inputPin = A0;  // Analog input from guitar
const int outputPin = 9; // PWM output to amp

void setup() {
    pinMode(outputPin, OUTPUT); 
    pinMode(inputPin, INPUT_PULLUP);
}

void loop() {
    int sensorValue = analogRead(inputPin); //Read signal from guitar
    int outputValue = map(sensorValue, 0, 1023, 0, 255); // Map to 8-bit PWM
    analogWrite(outputPin, outputValue); //Output to amp
}
