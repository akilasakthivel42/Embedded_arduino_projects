#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SOIL_SENSOR A0
#define RELAY 7
#define LED 8

int soilValue;
int moisture;

void setup()
{
    pinMode(SOIL_SENSOR, INPUT);
    pinMode(RELAY, OUTPUT);
    pinMode(LED, OUTPUT);

    digitalWrite(RELAY, HIGH);
    digitalWrite(LED, LOW);

    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("SOIL MONITORING");

    delay(2000);
    lcd.clear();
}

void loop()
{
    soilValue = analogRead(SOIL_SENSOR);

    moisture = map(soilValue, 0, 1023, 0, 100);

    lcd.setCursor(0, 0);
    lcd.print("Moisture:");
    lcd.print(moisture);
    lcd.print("%   ");

    Serial.print("Moisture: ");
    Serial.print(moisture);
    Serial.println("%");

    if (moisture < 30)
    {
        digitalWrite(RELAY, LOW);
        digitalWrite(LED, HIGH);

        lcd.setCursor(0, 1);
        lcd.print("Pump: ON       ");

        Serial.println("Soil Dry - Pump ON");
    }
    else
    {
        digitalWrite(RELAY, HIGH);
        digitalWrite(LED, LOW);

        lcd.setCursor(0, 1);
        lcd.print("Pump: OFF      ");

        Serial.println("Soil Wet - Pump OFF");
    }

    delay(1000);
}