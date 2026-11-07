#define MOVEMENT_SENSOR A0
#define LED 8

int movementValue;

void setup()
{
  Serial.begin(9600);

  pinMode(MOVEMENT_SENSOR, INPUT);
  pinMode(LED, OUTPUT);

  Serial.println("SMART LIVESTOCK MONITORING");
  Serial.println("--------------------------");
}

void loop()
{
  movementValue = analogRead(MOVEMENT_SENSOR);

  Serial.println("\n--- LIVESTOCK DETAILS ---");

  Serial.print("Movement Value: ");
  Serial.println(movementValue);

  if (movementValue > 500)
  {
    digitalWrite(LED, HIGH);

    Serial.println("MOVEMENT: DETECTED");
    Serial.println("ACTIVITY: ACTIVE");
  }
  else
  {
    digitalWrite(LED, LOW);

    Serial.println("MOVEMENT: LOW");
    Serial.println("ACTIVITY: RESTING");
  }

  Serial.println("--------------------------");

  delay(1000);
}