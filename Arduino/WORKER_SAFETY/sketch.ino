#include <DHT.h>

#define DHTPIN 3
#define DHTTYPE DHT22

#define PIR 2
#define GAS_SENSOR A0
#define LED 8
#define BUZZER 7

DHT dht(DHTPIN, DHTTYPE);

int motionValue;
int gasValue;
float temperature;

void setup()
{
  Serial.begin(9600);

  dht.begin();

  pinMode(PIR, INPUT);
  pinMode(GAS_SENSOR, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("CONSTRUCTION SITE SAFETY");
  Serial.println("------------------------");
}

void loop()
{
  motionValue = digitalRead(PIR);
  gasValue = analogRead(GAS_SENSOR);
  temperature = dht.readTemperature();

  if (isnan(temperature))
  {
    Serial.println("Temperature Sensor Error");
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);
    delay(2000);
    return;
  }

  Serial.println("\n--- SITE MONITORING ---");

  Serial.print("Worker Movement: ");
  if (motionValue == HIGH)
    Serial.println("DETECTED");
  else
    Serial.println("NOT DETECTED");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  if (temperature > 45 || gasValue > 400)
  {
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    Serial.println("SITE STATUS: HAZARD ALERT");
    Serial.println("ACTION: CHECK REQUIRED");
  }
  else
  {
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);

    Serial.println("SITE STATUS: NORMAL");
  }

  Serial.println("------------------------");

  delay(2000);
}