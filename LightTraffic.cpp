// LIGHT TRAFFIC
const int ledPin = 7;
// Define the pins for the traffic light LEDs
const int redPin = 1;
const int yellowPin = 2;  // Changed from blue to yellow
const int greenPin = 3;

void setup() {
  // Initialize the LED pins as outputs
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);  // Updated pin mode
  pinMode(greenPin, OUTPUT);
}

void loop() {
  // Control the LED on pin 7
  digitalWrite(ledPin, HIGH);  // Turn on control LED
  delay(3000);                  // Wait for 3 seconds
  digitalWrite(ledPin, LOW);   // Turn off control LED
  delay(1000);                  // Wait for 1 second

  // Red and Green light together
  digitalWrite(redPin, HIGH);
  delay(1000);                  // Red and Green for 3 seconds

  digitalWrite(yellowPin, HIGH);
  delay(3000);                  // Red and Green for 3 seconds

  // Turn off Red and Green
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  
  // Yellow light
  digitalWrite(greenPin, HIGH);
  delay(3000);                  // Yellow light for 3 seconds
  digitalWrite(greenPin, LOW);

  // Return to Red light after Yellow
  delay(1000);                  // Wait for 1 second before the next cycle
}