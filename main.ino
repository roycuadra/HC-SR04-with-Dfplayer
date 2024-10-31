#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// Pin definitions
const int trigPin = D5;            // Adjust based on your board
const int echoPin = D6;            // Adjust based on your board
const int distanceThreshold = 45;  // Set intruder detection distance to 45 cm
const int minDistance = 5;        // Minimum distance for reliable detection

// DFPlayer Mini setup
SoftwareSerial mp3Serial(D7, D8); // RX, TX - Adjust based on your board
DFRobotDFPlayerMini dfplayer;
bool isMp3Connected = false;
unsigned long lastDetectionTime = 0; // Time of last detection
const unsigned long debounceDelay = 5000; // 5 seconds debounce delay

void setup() {
  // Initialize serial ports
  Serial.begin(9600);           // For Serial monitor
  mp3Serial.begin(9600);        // For DFPlayer Mini

  // Ultrasonic sensor pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Continuously check if the DFPlayer module is connected
  if (!isMp3Connected) {
    isMp3Connected = dfplayer.begin(mp3Serial);  // Try to initialize DFPlayer
    if (isMp3Connected) {
      Serial.println("DFPlayer Mini connected successfully.");
      dfplayer.volume(100);  // Set volume to maximum (30)
    } else {
      Serial.println("Error: DFPlayer Mini module not connected!");
      delay(1000);  // Delay to avoid flooding the serial monitor
      return;       // Skip the rest of the loop if not connected
    }
  }

  // Intruder detection logic if DFPlayer is connected
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if the detected distance is below the threshold and greater than minDistance
  if (distance < distanceThreshold && distance > minDistance) {
    unsigned long currentTime = millis();
    // Trigger alarm if sufficient time has passed since last detection
    if (currentTime - lastDetectionTime > debounceDelay) {
      Serial.println("Intruder detected!");
      dfplayer.play(1); // Play the first track
      lastDetectionTime = currentTime; // Update last detection time
    }
  }

  delay(200); // Short delay for loop stability
}

long getDistance() {
  // Send a 10µs pulse to the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse width on the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  long distance = duration * 0.034 / 2;
  return distance;
}
