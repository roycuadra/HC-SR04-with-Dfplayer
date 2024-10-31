#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>


const int trigPin = D5;            
const int echoPin = D6;            
const int distanceThreshold = 45;  
const int minDistance = 5;        


SoftwareSerial mp3Serial(D7, D8); 
DFRobotDFPlayerMini dfplayer;
bool isMp3Connected = false;
unsigned long lastDetectionTime = 0; 
const unsigned long debounceDelay = 5000; 

void setup() {
 
  Serial.begin(9600);           
  mp3Serial.begin(9600);      

 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
 
  if (!isMp3Connected) {
    isMp3Connected = dfplayer.begin(mp3Serial);  
    if (isMp3Connected) {
      Serial.println("DFPlayer Mini connected successfully.");
      dfplayer.volume(100); 
    } else {
      Serial.println("Error: DFPlayer Mini module not connected!");
      delay(1000);  
      return;       
    }
  }

  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < distanceThreshold && distance > minDistance) {
    unsigned long currentTime = millis();
    if (currentTime - lastDetectionTime > debounceDelay) {
      Serial.println("Intruder detected!");
      dfplayer.play(1);
      lastDetectionTime = currentTime; 
    }
  }

  delay(200); 
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  long distance = duration * 0.034 / 2;
  return distance;
}
