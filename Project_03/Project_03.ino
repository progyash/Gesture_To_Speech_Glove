#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// DFPlayer Mini setup
SoftwareSerial mySerial(2, 3); // RX, TX for DFPlayer Mini
DFRobotDFPlayerMini myDFPlayer;

// Flex sensor pins and calibration
const int flexSensorPins[5] = {A0, A1, A2, A3, A4};
int baselineValues[5]; // Store baseline readings for each flex sensor
const int flexOffsets[5] = {10, 10, 10, 10, 10}; // Different offsets for each sensor
const int audioTracks[5] = {1, 2, 3, 4, 5}; // Audio tracks for flex sensors
bool sensorTriggered[5] = {false, false, false, false, false}; // Tracks if sensor was recently triggered

// Finger names corresponding to each flex sensor
const char* fingerNames[5] = {"Pinky", "Ring Finger", "Middle Finger", "Index Finger", "Thumb"};

bool isPlaying = false; // Track if audio is currently playing

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  // Initialize DFPlayer Mini
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer Mini not detected!");
    while (true); // Stop execution if DFPlayer Mini is not found
  }
  Serial.println("DFPlayer Mini initialized.");
  myDFPlayer.volume(30); // Set volume level (0-30)

  // Calibrate flex sensors
  calibrateFlexSensors();
}

void loop() {
  // Read flex sensor values and handle thresholds
  handleFlexSensors();

  delay(1000); // Add delay to make readings more readable on Serial Monitor
}

// Function to handle flex sensors
void handleFlexSensors() {
  Serial.println("\n-------------------------------------------------------");
  Serial.println("| Finger         | Flex | Reading | Lower | Upper     |");
  Serial.println("-------------------------------------------------------");

  for (int i = 0; i < 5; i++) {
    int flexValue = analogRead(flexSensorPins[i]); // Read flex sensor value
    int lowerThreshold = baselineValues[i] - flexOffsets[i];
    int upperThreshold = baselineValues[i] + flexOffsets[i];

    // Print flex sensor values and thresholds in table format
    Serial.print("| ");
    Serial.print(fingerNames[i]);
    int padding = 14 - strlen(fingerNames[i]); // Dynamic spacing for alignment
    for (int j = 0; j < padding; j++) Serial.print(" ");
    Serial.print(" |  ");
    Serial.print(i);
    Serial.print("   |   ");
    Serial.print(flexValue);
    Serial.print("   |  ");
    Serial.print(lowerThreshold);
    Serial.print("  |  ");
    Serial.print(upperThreshold);
    Serial.println("      |");
  }

  Serial.println("-------------------------------------------------------");

  for (int i = 0; i < 5; i++) {
    int flexValue = analogRead(flexSensorPins[i]);
    int lowerThreshold = baselineValues[i] - flexOffsets[i];
    int upperThreshold = baselineValues[i] + flexOffsets[i];

    // Check if flex sensor value crosses thresholds
    if (!isPlaying && !sensorTriggered[i]) {
      if (flexValue <= lowerThreshold || flexValue >= upperThreshold) {
        Serial.print("Threshold crossed for ");
        Serial.print(fingerNames[i]);
        Serial.print(" (Flex Sensor ");
        Serial.print(i);
        Serial.println("). Playing audio...");
        myDFPlayer.play(audioTracks[i]); // Play the corresponding audio track
        isPlaying = true;               // Block further inputs during playback
        sensorTriggered[i] = true;      // Mark sensor as triggered
      }
    } else if (sensorTriggered[i] && flexValue > lowerThreshold && flexValue < upperThreshold) {
      // Reset sensor trigger if value returns within range
      sensorTriggered[i] = false;
    }
  }

  // Check if audio has finished playing
  if (isPlaying && myDFPlayer.available()) {
    if (myDFPlayer.readType() == DFPlayerPlayFinished) {
      Serial.println("Audio finished playing.");
      isPlaying = false; // Reset playback flag
    }
  }
}

// Function to calibrate flex sensors
void calibrateFlexSensors() {
  Serial.println("Calibrating flex sensors...");
  const int numSamples = 10; // Number of samples for calibration
  int readings[5] = {0, 0, 0, 0, 0};

  // Take multiple readings to calculate baseline
  for (int i = 0; i < numSamples; i++) {
    for (int j = 0; j < 5; j++) {
      readings[j] += analogRead(flexSensorPins[j]);
    }
    delay(10); // Short delay between readings
  }

  // Calculate average baseline values
  for (int j = 0; j < 5; j++) {
    baselineValues[j] = readings[j] / numSamples;
    Serial.print(fingerNames[j]);
    Serial.print(" (Flex ");
    Serial.print(j);
    Serial.print(") Baseline: ");
    Serial.println(baselineValues[j]);
  }
}
