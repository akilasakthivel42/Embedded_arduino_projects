#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define HR_PIN A0
#define SPO2_PIN A1
#define SLEEP_PIN A2

#define GREEN 8
#define YELLOW 9
#define RED 10
#define BUZZER 6

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int heartRate;
int spo2;
int sleepActivity;

float temperature;

void setup()
{
  Serial.begin(9600);

  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Vital Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(2000);
}

void loop()
{
  int hrValue = analogRead(HR_PIN);
  int spo2Value = analogRead(SPO2_PIN);
  int sleepValue = analogRead(SLEEP_PIN);

  heartRate = map(hrValue, 0, 1023, 50, 130);
  spo2 = map(spo2Value, 0, 1023, 90, 100);
  sleepActivity = map(sleepValue, 0, 1023, 0, 100);

  temperature = dht.readTemperature();

  if (isnan(temperature))
  {
    lcd.clear();
    lcd.print("DHT Sensor Error");
    delay(2000);
    return;
  }

  // Demonstration status only
  bool alert = (spo2 < 95 || temperature > 38);
  bool warning = (heartRate < 60 || heartRate > 100 ||
                  sleepActivity > 60);

  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(BUZZER, LOW);

  if (alert)
  {
    digitalWrite(RED, HIGH);
    digitalWrite(BUZZER, HIGH);
  }
  else if (warning)
  {
    digitalWrite(YELLOW, HIGH);
  }
  else
  {
    digitalWrite(GREEN, HIGH);
  }

  // LCD screen 1
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HR:");
  lcd.print(heartRate);
  lcd.print(" BPM");

  lcd.setCursor(0, 1);
  lcd.print("SpO2:");
  lcd.print(spo2);
  lcd.print("%");

  delay(2000);

  // LCD screen 2
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature, 1);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Activity:");
  lcd.print(sleepActivity);
  lcd.print("%");

  delay(2000);

  // LCD screen 3
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sleep Demo:");

  lcd.setCursor(0, 1);

  if (sleepActivity <= 30)
    lcd.print("Low Activity");
  else if (sleepActivity <= 60)
    lcd.print("Medium Activity");
  else
    lcd.print("High Activity");

  delay(2000);
}
