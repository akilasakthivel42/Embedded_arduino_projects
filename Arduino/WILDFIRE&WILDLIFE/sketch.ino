#include <DHT.h>

#define DHTPIN 3
#define DHTTYPE DHT22

#define MQ2 A0
#define PIR 2

#define BUZZER 7
#define GREEN 8
#define YELLOW 9
#define RED 10

DHT dht(DHTPIN, DHTTYPE);

float temperature;
int gasValue;
int motionDetected;

bool temperatureWarning;
bool gasWarning;

void setup()
{
  Serial.begin(9600);

  dht.begin();

  pinMode(MQ2, INPUT);
  pinMode(PIR, INPUT);

  pinMode(BUZZER, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);

  Serial.println("ENVIRONMENT MONITOR");
  Serial.println("System Starting...");
  delay(2000);
}

void loop()
{
  // Read temperature

  temperature = dht.readTemperature();

  // Read gas sensor

  gasValue = analogRead(MQ2);

  // Detect movement

  motionDetected = digitalRead(PIR);

  if (isnan(temperature))
  {
    Serial.println("Temperature Sensor Error");
    delay(2000);
    return;
  }

  // Warning conditions

  temperatureWarning = (temperature >= 45);
  gasWarning = (gasValue > 400);

  // Reset indicators

  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(BUZZER, LOW);

  // Environmental warning

  if (temperatureWarning || gasWarning)
  {
    digitalWrite(RED, HIGH);
    digitalWrite(BUZZER, HIGH);

    Serial.println("ENVIRONMENT WARNING!");
  }
  else if (motionDetected == HIGH)
  {
    digitalWrite(YELLOW, HIGH);

    Serial.println("MOVEMENT DETECTED");
  }
  else
  {
    digitalWrite(GREEN, HIGH);

    Serial.println("ENVIRONMENT NORMAL");
  }

  // Display readings in Serial Monitor

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Gas Level: ");
  Serial.println(gasValue);

  Serial.print("Wildlife Movement: ");

  if (motionDetected == HIGH)
  {
    Serial.println("Detected");
  }
  else
  {
    Serial.println("Not Detected");
  }

  Serial.println("--------------------");

  delay(2000);
}