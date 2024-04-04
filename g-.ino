
#include <Stepper.h>

#define trigPin 12  // Trig pin of the sensor
#define echoPin 13  // Echo pin of the sensor

const int stepsPerRevolution = 200;  // Number of steps per revolution for your stepper motor
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);  // Initialize the stepper motor

const int motorEnablePin = 4;  // Pin connected to the enable/disable function of the motor driver

bool personDetected = false;  // Flag to track if a person is detected
unsigned long personDetectTime = 0;  // Time when the person was first detected
unsigned long confirmationTime = 0;  // Time for confirmation message
unsigned long noDetectionTime = 0;  // Time of no detection
bool motorRunning = false;  // Flag to track if the motor is running

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myStepper.setSpeed(60);  // Set the stepper motor speed (adjust as needed)
  pinMode(motorEnablePin, OUTPUT);  // Set the motor enable pin as an output
  digitalWrite(motorEnablePin, LOW);  // Enable the stepper motor driver
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the distance from the sensor
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration / 58.2;  // Convert the time to distance in centimeters

  // Check if a person is detected (within 30 cm range)
  if (distance < 4) {
    if (!personDetected) {
      personDetected = true;
      personDetectTime = millis();  // Record the time of initial detection
      confirmationTime = millis();  // Start the confirmation timer
      noDetectionTime = 0;  // Reset the no detection timer
      Serial.println("Person detected!");
    }
    if (millis() - personDetectTime >= 5000) {
      if (millis() - confirmationTime >= 5000) {
        Serial.println("Person is still there (Confirmation Message).");
        confirmationTime = millis();  // Reset the confirmation timer
      }
      noDetectionTime = 0;  // Reset the no detection timer
    }
  } else {
    if (personDetected) {
      if (millis() - personDetectTime >= 5000) {
        if (noDetectionTime == 0) {
          noDetectionTime = millis();  // Start the no detection timer
        }
        if (millis() - noDetectionTime >= 5000) {
          Serial.println("Person left the range.");
          personDetected = false;  // Reset the detection flag
          noDetectionTime = 0;  // Reset the no detection timer
          confirmationTime = 0;  // Reset the confirmation timer
          
          // Operate the stepper motor clockwise for 5 seconds
          myStepper.step(stepsPerRevolution);
          delay(5000);
          // Operate the stepper motor anticlockwise for 5 seconds
          myStepper.step(-stepsPerRevolution);
          delay(5000);
          // Disable the stepper motor driver
          digitalWrite(motorEnablePin, HIGH);
        }
      }
    } else {
      noDetectionTime = 0;  // Reset the no detection timer
    }
  }
}
