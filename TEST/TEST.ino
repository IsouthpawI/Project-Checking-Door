#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(10, 9);

char initial_password[4] = {'1', '2', '3', '4'};
String tagUID = "4A 52 4C B5";
char password[4];
boolean RFIDMode = true;
char key_pressed = 0;
uint8_t i = 0;

const byte rows = 4;
const byte columns = 4;

char hexaKeys[rows][columns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte row_pins[rows] = {8, 7, 6, 5};
byte column_pins[columns] = {4, 3, 2, A1};

Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);

void setup() {
  lcd.init();
  lcd.backlight();
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.clear();
}

void loop() {
  if (RFIDMode == true) {
    lcd.setCursor(0, 0);
    lcd.print("   Door Lock");
    lcd.setCursor(0, 1);
    lcd.print(" Scan Your Card ");

    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
 
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }

    String tag = "";
    for (byte j = 0; j < mfrc522.uid.size; j++)
    {
      tag.concat(String(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " "));
      tag.concat(String(mfrc522.uid.uidByte[j], HEX));
    }
    tag.toUpperCase();

    if (tag.substring(1) == tagUID)
    {
      lcd.clear();
      lcd.print("Card Matched!");
      delay(3000);
      lcd.clear();
      lcd.print("Enter Password:");
      lcd.setCursor(0, 1);
      RFIDMode = false;
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Wrong Card Shown!");
      lcd.setCursor(0, 1);
      lcd.print("Access Denied!");
      delay(3000);
      lcd.clear();
    }
  }
  
  if (RFIDMode == false) {
    key_pressed = keypad_key.getKey();
    if (key_pressed)
    {
      password[i++] = key_pressed;
      lcd.print("*");
    }
    if (i == 4)
    {
      delay(200);
      if (!(strncmp(password, initial_password, 4)))
      {
        lcd.clear();
        lcd.print("Pass Accepted!");
        lcd.setCursor(0, 1);
        lcd.print("Door is open!");
        delay(3000);
        lcd.clear();
        i = 0;
        RFIDMode = true;
      }
      else
      {
        lcd.clear();
        lcd.print("Wrong Password!");
        delay(3000);
        lcd.clear();
        i = 0;
        RFIDMode = true;
      }
    }
  }
}
