#define TRIG 5
#define ECHO 6
#define LED 8
#define BUZZER 7

long duration;
float distance;

void setup()
{
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("SMART WASTE BIN MONITORING");
  Serial.println("--------------------------");
}

void loop()
{
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

  Serial.println("\n--- WASTE BIN DETAILS ---");

  if (distance < 0)
  {
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);

    Serial.println("SENSOR: NO ECHO");
    Serial.println("STATUS: CHECK SENSOR");
  }
  else
  {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 20)
    {
      digitalWrite(LED, LOW);
      digitalWrite(BUZZER, LOW);

      Serial.println("BIN STATUS: EMPTY / LOW");
    }
    else if (distance > 10)
    {
      digitalWrite(LED, LOW);
      digitalWrite(BUZZER, LOW);

      Serial.println("BIN STATUS: HALF FILLED");
    }
    else
    {
      digitalWrite(LED, HIGH);
      digitalWrite(BUZZER, HIGH);

      Serial.println("BIN STATUS: FULL");
      Serial.println("ACTION: EMPTY THE BIN");
    }
  }

  Serial.println("--------------------------");

  delay(1000);
}
