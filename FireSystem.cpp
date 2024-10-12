#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
const int trigPin = 3;
const int echoPin = 2;
const int redLedPin = 4;
const int greenLedPin = 5;

// Keypad setup
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'D', 'C', 'B', 'A'},  // Adjusted row 1
  {'#', '9', '6', '3'},
  {'0', '8', '5', '2'},
  {'*', '7', '4', '1'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; 
byte colPins[COLS] = {10, 11, 12, 13}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust address as needed

const String password = "1234*";
String inputPassword = "";
bool alertActive = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  long duration, distance;
  
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2; // Distance in cm
  
  if (distance < 20) {
    alertActive = true;
    digitalWrite(redLedPin, HIGH);
    lcd.clear();
    lcd.print("ALERT: SYSTEM ON");
    
    // Wait for password input
    while (alertActive) {
      char key = keypad.getKey();
      if (key) {
        inputPassword += key;
        lcd.clear();
        lcd.print(inputPassword);
        
        // Check if the input password is complete
        if (inputPassword.length() == password.length()) {
          if (inputPassword == password) {
            lcd.clear();
            lcd.print("SYSTEM OFF");
            digitalWrite(redLedPin, LOW);
            digitalWrite(greenLedPin, HIGH);
            alertActive = false;
            inputPassword = ""; // Reset password input
            delay(2000);
            digitalWrite(greenLedPin, LOW);
            lcd.clear();
          } else {
            lcd.clear();
            lcd.print("Try Again");
            inputPassword = ""; // Reset password input
            delay(2000);
            lcd.clear();
          }
        }
      }
    }
  } else {
    // If the distance is safe, ensure the red LED is off
    digitalWrite(redLedPin, LOW);
  }
}
