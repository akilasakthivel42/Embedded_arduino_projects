#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define SOIL_SENSOR A0
#define LDR_SENSOR A1
#define LED 8

DHT dht(DHTPIN, DHTTYPE);

int soilValue;
int lightValue;
float temperature;

void setup()
{
  Serial.begin(9600);

  dht.begin();

  pinMode(SOIL_SENSOR, INPUT);
  pinMode(LDR_SENSOR, INPUT);
  pinMode(LED, OUTPUT);

  Serial.println("SMART AGRICULTURE MONITORING");
  Serial.println("----------------------------");
}

void loop()
{
  soilValue = analogRead(SOIL_SENSOR);
  lightValue = analogRead(LDR_SENSOR);
  temperature = dht.readTemperature();

  if (isnan(temperature))
  {
    Serial.println("Temperature Sensor Error");
    digitalWrite(LED, LOW);
    delay(2000);
    return;
  }

  Serial.println("\n--- CROP DETAILS ---");

  Serial.print("Soil Moisture Value: ");
  Serial.println(soilValue);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Light Intensity: ");
  Serial.println(lightValue);

  if (soilValue < 400 || temperature > 40)
  {
    digitalWrite(LED, HIGH);
    Serial.println("CROP STATUS: ATTENTION REQUIRED");
  }
  else
  {
    digitalWrite(LED, LOW);
    Serial.println("CROP STATUS: NORMAL");
  }

  if (lightValue < 500)
    Serial.println("LIGHT: LOW");
  else
    Serial.println("LIGHT: SUFFICIENT");

  Serial.println("----------------------------");

  delay(2000);
}