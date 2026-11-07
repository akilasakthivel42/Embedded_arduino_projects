#define TRIG 5
#define ECHO 6

#define GREEN 8
#define YELLOW 9
#define RED 10

#define BUZZER 7

long duration;
float distance;

void setup()
{
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  Serial.println("SMART RETAIL MONITOR");
  Serial.println("--------------------");
}

void loop()
{
  // Ultrasonic measurement

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

  // Reset indicators

  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(BUZZER, LOW);

  Serial.println("\n--- STOCK DETAILS ---");

  if (distance < 0)
  {
    Serial.println("Sensor Error");
  }

  else if (distance <= 5)
  {
    digitalWrite(GREEN, HIGH);

    Serial.println("STOCK: AVAILABLE");
    Serial.println("ARRANGEMENT: GOOD");
  }

  else if (distance <= 15)
  {
    digitalWrite(YELLOW, HIGH);

    Serial.println("STOCK: LOW");
    Serial.println("ACTION: RESTOCK SOON");
  }

  else
  {
    digitalWrite(RED, HIGH);
    digitalWrite(BUZZER, HIGH);

    Serial.println("STOCK: EMPTY");
    Serial.println("ACTION: RESTOCK REQUIRED");
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.println("--------------------");

  delay(1000);
}