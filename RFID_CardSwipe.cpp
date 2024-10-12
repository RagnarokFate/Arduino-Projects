#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pin definitions
#define RST_PIN 9   // Reset pin for RFID
#define SS_PIN 10   // Slave select pin for RFID
#define SERVO_PIN 8 // Pin for the Micro servo

// Create instances for RFID, LCD, and Servo
MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust I2C address if needed
Servo myServo;

void setup() {
    Serial.begin(9600);   // Initialize Serial for debugging
    SPI.begin();          // Initialize SPI bus
    rfid.PCD_Init();      // Initialize RFID module
    lcd.init();           // Initialize LCD
    lcd.backlight();      // Turn on LCD backlight
    myServo.attach(SERVO_PIN); // Attach the servo to pin 8
    
    lcd.print("Scan your card"); // Display initial message
}

void loop() {
    myServo.write(0); // Ensure servo is in the closed position (0 degrees)

    // Look for a new RFID card
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        // Card detected and read successfully
        String uid = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
            uid += String(rfid.uid.uidByte[i], DEC); // Concatenate UID as a string
        }
        // Check if the detected UID matches the known card
        if (uid == "21229159172") { // Replace with your actual card UID
            lcd.clear();
            lcd.print("Access Granted");
            myServo.write(90); // Rotate servo to open position (90 degrees)
        } else {
            lcd.clear();
            lcd.print("Access Denied");
            myServo.write(0); // Keep servo in closed position (0 degrees)
        }

        delay(2000); // Hold the message and servo position for 5 seconds
        lcd.clear();
        lcd.print("Scan your card"); // Prompt user to scan again

        // Stop reading the card
        rfid.PICC_HaltA();
    }
}
