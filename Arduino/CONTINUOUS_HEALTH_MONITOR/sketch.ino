#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define PULSE_INPUT A0
#define LED 8
#define BUZZER 7

DHT dht(DHTPIN, DHTTYPE);

int pulseValue;
float temperature;

void setup()
{
  Serial.begin(9600);

  dht.begin();

  pinMode(PULSE_INPUT, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("HEALTH MONITORING SYSTEM");
  Serial.println("------------------------");
}

void loop()
{
  pulseValue = analogRead(PULSE_INPUT);
  temperature = dht.readTemperature();

  if (isnan(temperature))
  {
    Serial.println("Temperature Sensor Error");
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);
    delay(2000);
    return;
  }

  Serial.println("\n--- HEALTH DETAILS ---");

  Serial.print("Simulated Pulse Value: ");
  Serial.println(pulseValue);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  if (temperature > 38 || pulseValue > 900)
  {
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    Serial.println("STATUS: ALERT");
    Serial.println("ACTION: CHECK REQUIRED");
  }
  else
  {
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);

    Serial.println("STATUS: NORMAL");
  }

  Serial.println("------------------------");

  delay(1000);
}