#include <DHT.h>

#define DHTPIN 3
#define DHTTYPE DHT22

#define PIR_PIN 2
#define LDR_PIN A0
#define LED_PIN 8
#define RELAY_PIN 7

DHT dht(DHTPIN, DHTTYPE);

int lightValue;
int motion;
float temperature;

void setup()
{
    Serial.begin(9600);

    pinMode(PIR_PIN, INPUT);
    pinMode(LDR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT);

    digitalWrite(LED_PIN, LOW);
    digitalWrite(RELAY_PIN, HIGH);

    dht.begin();

    Serial.println("SMART HOME SYSTEM");
}

void loop()
{
    temperature = dht.readTemperature();

    lightValue = analogRead(LDR_PIN);

    motion = digitalRead(PIR_PIN);

    Serial.println("----------------");

    Serial.print("Temperature: ");
    Serial.println(temperature);

    Serial.print("Light Value: ");
    Serial.println(lightValue);

    Serial.print("Motion: ");
    Serial.println(motion);

    // Automatic lighting control

    if (motion == HIGH && lightValue < 500)
    {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Light: ON");
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
        Serial.println("Light: OFF");
    }

    // Temperature-based appliance control

    if (!isnan(temperature) && temperature >= 30)
    {
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("Appliance: ON");
    }
    else
    {
        digitalWrite(RELAY_PIN, HIGH);
        Serial.println("Appliance: OFF");
    }

    delay(2000);
}