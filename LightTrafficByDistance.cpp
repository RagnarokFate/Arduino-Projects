// Define the pin for the control LED
const int ledPin = 7;
// Define the pins for the traffic light LEDs
const int redPin = 8;
const int yellowPin = 2;  // Changed from blue to yellow
const int greenPin = 3;
// Define pins for the ultrasonic sensor
const int trigPin = 4;
const int echoPin = 5;

void setup() {
  // Initialize the LED pins as outputs
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  // Initialize the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);  // Start serial communication for debugging
}

void loop() {
  // Measure distance using ultrasonic sensor
  long duration, distance;
  
  // Clear the TRIG pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Light Traffic determined by distance
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the ECHO pin, which returns the time it took for the echo to return
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance (in cm)
  distance = duration * 0.034 / 2;

  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // Control traffic light based on distance
  if (distance < 50) {
    digitalWrite(redPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
  } else if (distance >= 50 && distance <= 100) {
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(greenPin, LOW);
  } else {
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, HIGH);
  }

  // Optional delay for smoother readings
  delay(500); // Adjust as necessary for your application
}
