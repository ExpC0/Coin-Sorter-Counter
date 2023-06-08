#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
Servo servo1;
Servo servo2;

const int switchPin = 2;
const int servoPin1 = 9;
const int servoPin2 = 4;
const int buzzerPin = 3;  // Pin connected to the buzzer
int switchState = 0;
int previousSwitchState = 0;
int servoAngle1 = 165;
int servoAngle2 = 100;

int x1 = 0;
int input1 = A1;
int state1 = 1;

int x2 = 0;
int input2 = A2;
int state2 = 1;

int x3 = 0;
int input3 = A3;
int state3 = 1;

int total = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initialize the LCD object

void setup() {
  pinMode(switchPin, INPUT_PULLUP);  // Set the switch pin as input with internal pull-up resistor
  servo1.attach(servoPin1);  // Attach servo1 to servoPin1
  servo2.attach(servoPin2);  // Attach servo2 to servoPin2

  pinMode(buzzerPin, OUTPUT);  // Set the buzzer pin as output

  lcd.init();  // Initialize the LCD
  lcd.backlight();  // Turn on the LCD backlight

  lcd.setCursor(0, 0);  // Set the cursor to the first column of the first row
  lcd.print("Coin Sorter &");  // Print the first line of the welcome message
  lcd.setCursor(0, 1);  // Set the cursor to the first column of the second row
  lcd.print("Counter...");  // Print the second line of the welcome message

  delay(3000);  // Delay for 3 seconds to display the welcome message
  lcd.clear();  // Clear the LCD display

  lcd.setCursor(0, 0);
  lcd.print("1TK");  // Print the label for 1TK
  lcd.setCursor(4, 0);
  lcd.print("2TK");  // Print the label for 2TK
  lcd.setCursor(8, 0);
  lcd.print("5TK");  // Print the label for 5TK
  lcd.setCursor(0, 1);
  lcd.print(x1);  // Print the count of 1TK
  lcd.setCursor(4, 1);
  lcd.print(x2);  // Print the count of 2TK
  lcd.setCursor(8, 1);
  lcd.print(x3);  // Print the count of 5TK

  // Activate buzzer sound during setup
  tone(buzzerPin, 1000, 500);  // Play a tone on the buzzer for 500 milliseconds
  delay(500);
}

void loop() {
  switchState = digitalRead(switchPin);  // Read the state of the switch

  if (switchState != previousSwitchState && switchState == LOW) {
    // Toggle servo angles when the switch is pressed
    servoAngle1 = (servoAngle1 == 165) ? 70 : 165;
    servoAngle2 = (servoAngle2 == 100) ? 180 : 100;
    servo1.write(servoAngle1);  // Set the angle of servo1
    servo2.write(servoAngle2);  // Set the angle of servo2
    tone(buzzerPin, 1000, 200);  // Play a tone on the buzzer for 200 milliseconds
    delay(500);
  }

  previousSwitchState = switchState;  // Update the previous switch state

  int counter1 = digitalRead(A1);  // Read the state of counter 1
  int counter2 = digitalRead(A2);  // Read the state of counter 2
  int counter3 = digitalRead(A3);  // Read the state of counter 3

  if (state1 == 0) {
    switch (counter1) {
      case 1:
        state1 = 1;
        lcd.setCursor(0, 1);  // Set the cursor to the first column of the second row
        x1 = x1 + 1;  // Increment the count of 1TK
        total = total + 1;  // Increment the total amount
        lcd.print(x1);  // Print the updated count of 1TK
        tone(buzzerPin, 1000, 100);  // Play a tone on the buzzer for 100 milliseconds
        delay(200);
        break;
      case 0:
        state1 = 0;
        break;
    }
  }

  if (counter1 == LOW) {
    state1 = 0;
  }

  if (state2 == 0) {
    switch (counter2) {
      case 1:
        state2 = 1;
        lcd.setCursor(4, 1);  // Set the cursor to the fifth column of the second row
        x2 = x2 + 1;  // Increment the count of 2TK
        total = total + 2;  // Increment the total amount
        lcd.print(x2);  // Print the updated count of 2TK
        tone(buzzerPin, 1000, 100);  // Play a tone on the buzzer for 100 milliseconds
        delay(200);
        break;
      case 0:
        state2 = 0;
        break;
    }
  }

  if (counter2 == LOW) {
    state2 = 0;
  }

if (state3 == 0) {
    switch (counter3) {
      case 1:
        state3 = 1;
        lcd.setCursor(8, 1);  // Set the cursor to the ninth column of the second row
        x3 = x3 + 1;  // Increment the count of 5TK
        total = total + 5;  // Increment the total amount
        lcd.print(x3);  // Print the updated count of 5TK
        tone(buzzerPin, 1000, 100);  // Play a tone on the buzzer for 100 milliseconds
        delay(200);
        break;
      case 0:
        state3 = 0;
        break;
    }
  }

  if (counter3 == LOW) {
    state3 = 0;
  }

  // Display total amount when servo1 is at 165 degrees and micro switch is pressed
  if (servoAngle1 == 165 && switchState == LOW && total > 0) {
    lcd.clear();  // Clear the LCD display
    lcd.setCursor(0, 0);
    lcd.print("Total Amount:");
    lcd.setCursor(0, 1);
    lcd.print(total);
    lcd.setCursor(4, 1);
    lcd.print("TK");
  }
}

