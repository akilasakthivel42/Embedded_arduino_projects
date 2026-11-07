#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define VIBRATION A0
#define LED 8
#define BUZZER 6

DHT dht(DHTPIN, DHTTYPE);

float temperature;
int vibrationValue;
int maintenanceDays;

void setup()
{
  Serial.begin(9600);

  dht.begin();

  pinMode(VIBRATION, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("MACHINE HEALTH MONITOR");
  Serial.println("----------------------");
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

  Serial.println("\n--- SENSOR DATA ---");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Vibration: ");
  Serial.println(vibrationValue);

  if (temperature > 45 || vibrationValue > 700)
  {
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    maintenanceDays = 0;

    Serial.println("STATUS: MACHINE FAULT");
    Serial.println("ACTION: Inspection Required");
    Serial.println("MAINTENANCE: Immediate");
  }

  else if (temperature >= 35 || vibrationValue >= 400)
  {
    digitalWrite(BUZZER, LOW);

    maintenanceDays = 7;

    Serial.println("STATUS: MACHINE WARNING");
    Serial.println("ACTION: Check Machine");
    Serial.println("MAINTENANCE: Within 7 Days");

    digitalWrite(LED, HIGH);
    delay(300);
    digitalWrite(LED, LOW);
    delay(300);
  }

  else
  {
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);

    maintenanceDays = 30;

    Serial.println("STATUS: MACHINE NORMAL");
    Serial.println("MAINTENANCE: 30 Days");
  }

  Serial.println("----------------------");

  delay(2000);
}