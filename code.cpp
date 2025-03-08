#include <LiquidCrystal.h>

// Initialize the LCD with the pins we're using
// Parameters: (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin definitions
const int buttonPin = 7;      // Push button
const int redLedPin = 8;      // Red LED
const int greenLedPin = 9;    // Green LED
const int motorEnable = 6;    // Motor Enable
const int motorPin1 = 10;     // Motor direction control 1
const int motorPin2 = 13;     // Motor direction control 2

// Variables
int buttonState = 0;          // Current state of the button
int lastButtonState = 0;      // Previous state of the button
bool gateOpen = false;        // Current state of the gate

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);  // Set up the LCD's number of columns and rows
  
  // Initialize pins
  pinMode(buttonPin, INPUT_PULLUP);  // Button with internal pull-up
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(motorEnable, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  
  // Initial state: gate closed, red light on
  closeGate();
}

void loop() {
  // Read button state
  buttonState = digitalRead(buttonPin);
  
  // Check if button was pressed (transition from HIGH to LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50);  // Debounce
    
    // Toggle gate state
    if (gateOpen) {
      closeGate();
    } else {
      openGate();
    }
  }
  
  // Save current button state for next comparison
  lastButtonState = buttonState;
}

void openGate() {
  // Update display
  lcd.clear();
  lcd.print("GO");
  
  // Traffic light: red off, green on
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, HIGH);
  
  // Open the gate (run motor forward)
  analogWrite(motorEnable, 200);  // Motor speed
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  
  // Run motor for 2 seconds
  delay(2000);
  
  // Stop motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  
  // Update state
  gateOpen = true;
}

void closeGate() {
  // Update display
  lcd.clear();
  lcd.print("STOP");
  
  // Traffic light: red on, green off
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, LOW);
  
  // Close the gate (run motor in reverse)
  analogWrite(motorEnable, 200);  // Motor speed
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  
  // Run motor for 2 seconds
  delay(2000);
  
  // Stop motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  
  // Update state
  gateOpen = false;
}
