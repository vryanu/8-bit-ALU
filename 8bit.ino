#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void setup() 
{  
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  lcd.begin(16, 2);
}

void loop() 
{
  lcd.setCursor(0,0);
  for (int i=7;i>=0;i--)
  {
    if (digitalRead(i) == HIGH)
      lcd.print("1");
    else
      lcd.print("0");
  }

  delay(100);
}
