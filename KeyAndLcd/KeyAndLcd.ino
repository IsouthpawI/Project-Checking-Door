#include <Wire.h>
#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] = {4, 3, 2, A1};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup(){
      Serial.begin(9600);
      lcd.init();
      lcd.backlight();
}
void loop(){
      lcd.setCursor(0,0);
      lcd.print("Press any key!"); 
      char customKey = customKeypad.getKey();
      if (customKey){
            Serial.println(customKey);
            lcd.setCursor(0,1);
            lcd.print(customKey);
            Serial.print(customKey);
            lcd.setCursor(0,2);
            lcd.print(customKey);
            Serial.print(customKey);
            lcd.setCursor(0,3);
            lcd.print(customKey);
            Serial.print(customKey);
            lcd.setCursor(0,4);
            lcd.print(customKey);
      }
}
