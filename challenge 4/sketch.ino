#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Keypad.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}   };


byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 1, 0};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Servo lockServo;
const int servoPin = 11;

const char correctPIN[] = "11223344";
char enteredPIN[9];
byte pinIndex = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();
  lockServo.attach(servoPin);
  lockServo.write(0);
  lcd.print("PIN:");
}

void loop() {
  char key = keypad.getKey();
  
  if (key != '\0') {
    if (key != 'A' && pinIndex < 8) {
      lcd.print('*');
      enteredPIN[pinIndex] = key;
      pinIndex++;
    }
  }

  if (key == 'A') {
    enteredPIN[pinIndex] = '\0';
    bool correct = true;
    for (byte i = 0; i < 8; i++) {
      if (enteredPIN[i] != correctPIN[i]) {
        correct = false;
        break;
      }
    }
    if (correct) {
      lcd.clear();
      lcd.print("door open");
      lockServo.write(90);
      delay(5000);
      lockServo.write(0);
      delay(1000);
      lcd.clear();
      lcd.print("door locked");
    } else {
      lcd.clear();
      lcd.print("wrong pin");
      delay(1000);
      lcd.clear();
      lcd.print("PIN:");
    }
    for (byte i = 0; i < 9; i++) {
      enteredPIN[i] = '\0';
    }
    pinIndex = 0;
  }
}
