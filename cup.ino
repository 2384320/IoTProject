#include <LiquidCrystal_I2C.h>

#define trigPin 13
#define echoPin 12
#include <Wire.h>

#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494
#define C5 523
#define D5 587
#define E5 659
#define F5 698

int buzzer = 9;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void one() // five
{
  tone(buzzer, F4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, A4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, B4);
  delay(400);
  tone(buzzer, F4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, A4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, B4);
  delay(400);
  noTone(buzzer);
}

void two() // six
{
  tone(buzzer, F4);
  delay(200);
  tone(buzzer, A4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, B4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, E5);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, D5);
  delay(400);
  tone(buzzer, B4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, C5);
  delay(50);
  noTone(buzzer);
  delay(150);
}

void three()
{
  tone(buzzer, B4);
  delay(200);
  tone(buzzer, G4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, E4);
  delay(800);
  noTone(buzzer);
  delay(200);
}

void four()
{
  tone(buzzer, D4);
  delay(200);
  tone(buzzer, E4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, G4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, E4);
  delay(1200);
  noTone(buzzer);
}

void seven()
{
  tone(buzzer, E5);
  delay(200);
  tone(buzzer, B4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, G4);
  delay(800);
  noTone(buzzer);
  delay(200);
}

void eight()
{
  tone(buzzer, B4);
  delay(200);
  tone(buzzer, G4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, D4);
  delay(50);
  noTone(buzzer);
  delay(150);
  tone(buzzer, E4);
  delay(1200);
  noTone(buzzer);
}

void nine() // eleven thirteen
{
  tone(buzzer, D4);
  delay(200);
  tone(buzzer, E4);
  delay(200);
  tone(buzzer, F4);
  delay(400);
  tone(buzzer, G4);
  delay(200);
  tone(buzzer, A4);
  delay(200);
  tone(buzzer, B4);
  delay(400);
  noTone(buzzer);
}

void ten() // fourteen
{
  tone(buzzer, C5);
  delay(200);
  tone(buzzer, B4);
  delay(200);
  tone(buzzer, E4);
  delay(1200);
  noTone(buzzer);
}

void twelve()
{
  tone(buzzer, C5);
  delay(200);
  tone(buzzer, D5);
  delay(200);
  tone(buzzer, E5);
  delay(1200);
  noTone(buzzer);
}

void fifteen()
{
  tone(buzzer, F4);
  delay(200);
  tone(buzzer, E4);
  delay(200);
  tone(buzzer, A4);
  delay(200);
  tone(buzzer, G4);
  delay(200);
  tone(buzzer, B4);
  delay(200);
  tone(buzzer, A4);
  delay(200);
  tone(buzzer, C5);
  delay(200);
  tone(buzzer, B4);
  delay(200);
  noTone(buzzer);
}

void sixteen()
{
  tone(buzzer, D5);
  delay(200);
  tone(buzzer, C5);
  delay(200);
  tone(buzzer, E5);
  delay(200);
  tone(buzzer, D5);
  delay(200);
  tone(buzzer, F5);
  delay(200);
  tone(buzzer, E5);
  delay(150);
  noTone(buzzer);
  delay(50);
  tone(buzzer, E5);
  delay(100);
  tone(buzzer, F5);
  delay(100);
  noTone(buzzer);
  delay(100);
}

void seventeen()
{
  tone(buzzer, D5);
  delay(100);
  tone(buzzer, E5);
  delay(1600);
  noTone(buzzer);
}

void eighteen()
{
  noTone(buzzer);
  delay(200);
  tone(buzzer, E5);
  delay(150);
  noTone(buzzer);
  delay(50);
  tone(buzzer, E5);
  delay(150);
  noTone(buzzer);
  delay(50);
  tone(buzzer, E5);
  delay(150);
  noTone(buzzer);
  delay(50);
  tone(buzzer, E5);
  delay(150);
  noTone(buzzer);
  delay(850);
  

  
}

long microsecondsToCentimeters(long microseconds)
{
    return microseconds / 29 / 2;
}

long ultra()
{
  long duration, result;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
    
  result = microsecondsToCentimeters(duration);
  return result;
}

void lcdprint()
{
  lcd.clear();
  lcd.print("I have a cup");
  lcd.setCursor(0, 1);
  lcd.print("-_-");
}

void setup()
{
  lcd.begin();
  lcdprint();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT); 
}

void loop() 
{
  long cm;
    cm = ultra();
    while (cm >= 10) {
      lcd.clear();
      lcd.print("GIVE ME A CUP!");
      lcd.setCursor(0, 1);
      lcd.print("O_O");
      
      one();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      two();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      three();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      four();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      one();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      two();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      seven();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      eight();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      nine();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      ten();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      nine();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      twelve();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      nine();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      ten();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      fifteen();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      sixteen();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      seventeen();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }

      eighteen();
      cm = ultra();
      if ( cm < 10) {
        lcdprint();
        break;
      }
    }
}
