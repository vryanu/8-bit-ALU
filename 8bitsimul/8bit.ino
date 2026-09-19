#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int jump_delay = 500;
int c = 0;

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

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);

  lcd.begin(16, 2);
}

void loop() 
{
  analogWrite(A2, 255);
  if (c == 0)
    analogWrite(A2, 0);
  else if (c >= jump_delay)
    analogWrite(A1, 255);
  analogWrite(A0, 255);
  delay(jump_delay);
  analogWrite(A0, 0);
  c += jump_delay;
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
