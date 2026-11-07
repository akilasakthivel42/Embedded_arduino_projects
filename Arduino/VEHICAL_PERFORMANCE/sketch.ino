#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define TRIG 5
#define ECHO 6
#define LED 8
#define BUZZER 7

DHT dht(DHTPIN, DHTTYPE);

float temperature;
float distance;
long duration;

void setup()
{
  Serial.begin(9600);

  dht.begin();

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("VEHICLE DIAGNOSTIC SYSTEM");
  Serial.println("------------------------");
}

void loop()
{
  temperature = dht.readTemperature();

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

  if (isnan(temperature))
  {
    Serial.println("Temperature Sensor Error");
    delay(2000);
    return;
  }

  Serial.println("\n--- VEHICLE DETAILS ---");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Distance: ");
  if (distance < 0)
    Serial.println("No Echo");
  else
  {
    Serial.print(distance);
    Serial.println(" cm");
  }

  if (temperature > 45 || (distance >= 0 && distance < 10))
  {
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    Serial.println("VEHICLE STATUS: WARNING");
    Serial.println("DIAGNOSTIC: CHECK REQUIRED");
  }
  else
  {
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);

    Serial.println("VEHICLE STATUS: NORMAL");
    Serial.println("DIAGNOSTIC: SYSTEM OK");
  }

  Serial.println("------------------------");

  delay(2000);
}