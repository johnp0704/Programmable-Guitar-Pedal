/*
John Poirier and Grant Floyd
Programmable Guitar Pedal
Microcontrollers Lab X
Task: Loop Pedal Concept Code (Untested, requires SD Card)
*/

#include <SD.h> // Library for SD Card
#include <SPI.h> // Library for SPI Communication

// Pin Definitions
const int recordButton = 2;   // Start/stop recording and playback
const int resetButton = 3;    // Reset recording
const int audioInputPin = A0; // Guitar audio input
const int audioOutputPin = 9; // Guitar audio output
const int chipSelect = 10;    // SD card select pin

// State Variables and Flags
bool isRecording = false;
bool isPlaying = false;
unsigned long startTime = 0;
unsigned long endTime = 0;
const unsigned long sampleRate = 44100; // Sampling rate for audio (Hz)
unsigned long lastSampleTime = 0;

File audioFile; //Audio File 

void setup() {
    // Set pin modes
    pinMode(recordButton, INPUT_PULLUP);
    pinMode(resetButton, INPUT_PULLUP);
    pinMode(audioInputPin, INPUT);
    pinMode(audioOutputPin, OUTPUT);

    // Initialize SD card
    if (!SD.begin(chipSelect)) {
        Serial.begin(9600);
        Serial.println("SD card initialization failed!");
        while (true); // Stop execution if SD card fails
    }
    Serial.println("SD card initialized.");
}

void loop() {
    // Record/Play Button Handling
    if (digitalRead(recordButton) == LOW) {
        delay(200); // Button debouncing
        if (!isRecording && !isPlaying) {
            startRecording(); //Begin recording
        } else if (isRecording) {
            endRecordingStartPlayback(); // Stop recording, play recorded audio
        } else if (isPlaying) {
            stopPlayback(); // Stop playback
        }
    }

    // Reset Button Handling
    if (digitalRead(resetButton) == LOW) {
        delay(200); // Debounce
        resetLoop(); // Reset functions
    }

    // Recoridng/Playback Handling
    if (isRecording) {
        recordAudio(); // Record
    }
    if (isPlaying) {
        playbackAudio(); // Playback
    }
}

// Start Recording
void startRecording() {
    Serial.println("Recording begin");
    // Set flags
    isRecording = true;
    isPlaying = false;
    audioFile = SD.open("audio.raw", FILE_WRITE); // Open file
    if (!audioFile) { // Error handling
        Serial.println("Error opening file for recording!");
        isRecording = false;
    }
    startTime = micros(); //Begin timing
}

// Stop Recording and Start Playback
void endRecordingStartPlayback() {
    Serial.println("Recording stopped. Starting playback.");
    //Set Flags
    isRecording = false;
    isPlaying = true;
    endTime = micros();// Stop timing
    if (audioFile) {
        audioFile.close(); // Close audio file
    }
    audioFile = SD.open("audio.raw", FILE_READ); //Open file to read
    if (!audioFile) { // Error handling
        Serial.println("Error opening file for playback!");
        isPlaying = false;
    }
}

// Stop Playback
void stopPlayback() {
    Serial.println("Playback stopped.");
    // Set Flags
    isPlaying = false;
    if (audioFile) { //Close file
        audioFile.close();
    }
}

// Reset
void resetLoop() { 
    Serial.println("Loop reset.");
    // Set Flags
    isRecording = false;
    isPlaying = false;
    if (audioFile) { // Close file
        audioFile.close();
    }
    SD.remove("audio.raw"); // Delete existing loop file
}

// Record Audio
void recordAudio() {
    unsigned long currentTime = micros();// Check start time
    if (currentTime - lastSampleTime >= (1000000 / sampleRate)) {
        lastSampleTime = currentTime; // set sample time
        int sample = analogRead(audioInputPin) >> 2; // 10-bit input to 8-bit output
        audioFile.write(sample); // Write to SD card file
    }
}

// Playback Audio
void playbackAudio() {
    if (audioFile.available()) { // If file available
        int sample = audioFile.read(); // Read audio file
        analogWrite(audioOutputPin, sample); // Write to output from audio file
    } else {
        Serial.println("End of loop reached. Restarting playback");
        audioFile.seek(0); // Restart playback
    }
}
