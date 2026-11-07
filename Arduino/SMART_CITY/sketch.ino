#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG 5
#define ECHO 6
#define MQ2 A0
#define PIR 2

#define BUZZER 7
#define GREEN 8
#define YELLOW 9
#define RED 10

LiquidCrystal_I2C lcd(0x27, 16, 2);

long duration;
float distance;

int gasValue;
int motionDetected;

bool binFull;
bool gasWarning;

void setup()
{
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(MQ2, INPUT);
  pinMode(PIR, INPUT);

  pinMode(BUZZER, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("SMART CITY");
  lcd.setCursor(0, 1);
  lcd.print("MONITORING");
  delay(2000);
}

void loop()
{
  // Ultrasonic waste monitoring

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0)
  {
    distance = -1;
  }
  else
  {
    distance = duration * 0.0343 / 2;
  }

  // Gas monitoring

  gasValue = analogRead(MQ2);

  // Human movement detection

  motionDetected = digitalRead(PIR);

  // Conditions

  binFull = (distance >= 0 && distance < 10);
  gasWarning = (gasValue > 400);

  // Reset indicators

  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(BUZZER, LOW);

  // Alert system

  if (binFull || gasWarning)
  {
    digitalWrite(RED, HIGH);
    digitalWrite(BUZZER, HIGH);
  }
  else if (motionDetected == HIGH)
  {
    digitalWrite(YELLOW, HIGH);
  }
  else
  {
    digitalWrite(GREEN, HIGH);
  }

  // LCD Screen 1

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Bin:");

  if (distance < 0)
  {
    lcd.print("No Echo");
  }
  else
  {
    lcd.print(distance, 1);
    lcd.print("cm");
  }

  lcd.setCursor(0, 1);
  lcd.print("Gas:");
  lcd.print(gasValue);

  delay(1500);

  // LCD Screen 2

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Movement:");

  if (motionDetected == HIGH)
  {
    lcd.print("YES");
  }
  else
  {
    lcd.print("NO");
  }

  lcd.setCursor(0, 1);

  if (binFull)
  {
    lcd.print("BIN FULL");
  }
  else if (gasWarning)
  {
    lcd.print("GAS WARNING");
  }
  else if (motionDetected == HIGH)
  {
    lcd.print("PERSON DETECTED");
  }
  else
  {
    lcd.print("CITY NORMAL");
  }

  delay(1500);
}