#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define VIBRATION A0
#define GREEN 8
#define YELLOW 9
#define RED 10
#define BUZZER 6

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int vibrationValue;
float temperature;

void setup()
{
    Serial.begin(9600);

    pinMode(VIBRATION, INPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    dht.begin();

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("MACHINE HEALTH");
    delay(2000);
    lcd.clear();
}

void loop()
{
    temperature = dht.readTemperature();
    vibrationValue = analogRead(VIBRATION);

    if (isnan(temperature))
    {
        Serial.println("Temperature Sensor Error");
        delay(2000);
        return;
    }

    Serial.print("Temperature: ");
    Serial.println(temperature);

    Serial.print("Vibration: ");
    Serial.println(vibrationValue);

    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(temperature);
    lcd.print(" C   ");

    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);
    digitalWrite(BUZZER, LOW);

    if (temperature > 45 || vibrationValue > 600)
    {
        digitalWrite(RED, HIGH);
        digitalWrite(BUZZER, HIGH);

        lcd.setCursor(0, 1);
        lcd.print("MACHINE: FAULT ");

        Serial.println("ABNORMAL CONDITION");
    }
    else if (temperature >= 35 || vibrationValue >= 350)
    {
        digitalWrite(YELLOW, HIGH);

        lcd.setCursor(0, 1);
        lcd.print("MACHINE: WARN  ");

        Serial.println("WARNING CONDITION");
    }
    else
    {
        digitalWrite(GREEN, HIGH);

        lcd.setCursor(0, 1);
        lcd.print("MACHINE: NORMAL");

        Serial.println("MACHINE NORMAL");
    }

    delay(2000);
}