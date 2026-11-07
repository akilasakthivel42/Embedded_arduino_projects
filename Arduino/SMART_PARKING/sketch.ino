#define TRIG 5
#define ECHO 6

#define GREEN_LED 8
#define RED_LED 9

long duration;
float distance;

void setup()
{
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  Serial.println("SMART PARKING MANAGEMENT");
  Serial.println("------------------------");
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

  Serial.println("\n--- PARKING SLOT STATUS ---");

  if (distance < 0)
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);

    Serial.println("SENSOR: NO ECHO");
    Serial.println("STATUS: CHECK SENSOR");
  }
  else
  {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 15)
    {
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);

      Serial.println("PARKING SLOT: AVAILABLE");
    }
    else
    {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);

      Serial.println("PARKING SLOT: OCCUPIED");
    }
  }

  Serial.println("------------------------");

  delay(1000);
}