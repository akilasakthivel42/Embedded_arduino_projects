#define PIR 2
#define DOOR_SENSOR A0
#define LED 8
#define BUZZER 7

int motionValue;
int doorValue;

void setup()
{
  Serial.begin(9600);

  pinMode(PIR, INPUT);
  pinMode(DOOR_SENSOR, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("PROPERTY SECURITY SYSTEM");
  Serial.println("------------------------");
}

void loop()
{
  motionValue = digitalRead(PIR);
  doorValue = analogRead(DOOR_SENSOR);

  Serial.println("\n--- SECURITY DETAILS ---");

  if (motionValue == HIGH)
    Serial.println("MOTION: DETECTED");
  else
    Serial.println("MOTION: NOT DETECTED");

  if (doorValue > 500)
    Serial.println("DOOR: OPEN");
  else
    Serial.println("DOOR: CLOSED");

  if (motionValue == HIGH || doorValue > 500)
  {
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    Serial.println("SECURITY STATUS: ALERT");
    Serial.println("ACCESS ACTIVITY DETECTED");
  }
  else
  {
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);

    Serial.println("SECURITY STATUS: NORMAL");
  }

  Serial.println("------------------------");

  delay(1000);
}