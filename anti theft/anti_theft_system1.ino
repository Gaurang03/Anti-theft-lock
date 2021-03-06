#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
Servo myservo;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
#define Password_Lenght 7 
int pos = 0;   
char Data[Password_Lenght];
char Master[Password_Lenght] = "B56743";//my password
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;
int del1=3000;
int del2=1000;
int del3=30;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
bool door = true;

byte rowPins[ROWS] = {1, 2, 3, 4}; 
byte colPins[COLS] = {5, 6, 7, 8}; 

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

void setup()
{
  myservo.attach(9);
  ServoClose();
  lcd.begin(16, 2);
  lcd.print("  Arduino Door ");
  lcd.setCursor(0, 1);
  lcd.print("--Gaurang lock--");
  delay(del1);
  lcd.clear();

}

void loop()
{
  if (door == 0)
  {
    customKey = customKeypad.getKey();

    if (customKey == '#')

    {
      lcd.clear();
      ServoClose();
      lcd.print("  Door is close");
      delay(del1);
      door = 1;
    }
  }

  else Open();
}

void clearData()
{
  while (data_count != 0)
  { 
    Data[data_count--] = 0; 
  }
  return;
}

void ServoOpen()
{
  for (pos = 180; pos >= 0; pos -= 5) { 
    // in steps of 1 degree
    myservo.write(pos);             
    delay(del3);                       
  }
}

void ServoClose()
{
  for (pos = 0; pos <= 180; pos += 5) { 
    myservo.write(pos);              
    delay(del3);                       
  }
}

void Open()
{
  lcd.setCursor(0, 0);
  lcd.print(" Enter Password ");
  
  customKey = customKeypad.getKey();
  if (customKey) 
  {
    Data[data_count] = customKey; 
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]); 
    data_count++; 
  }

  if (data_count == Password_Lenght - 1) 
  {
    if (!strcmp(Data, Master)) 
    {
      lcd.clear();
      ServoOpen();
      lcd.print("  Door is Open");
      door = 0;
    }
    else
    {
      lcd.clear();
      lcd.print(" Wrong Password ");
      delay(del2);
      door = 1;
    }
    clearData();
  }
}
