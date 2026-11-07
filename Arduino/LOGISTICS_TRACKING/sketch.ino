#define POT A0
#define LED 8
#define BUZZER 7

int conditionValue;

void setup()
{
  Serial.begin(9600);

  pinMode(POT, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("LOGISTICS MONITORING SYSTEM");
  Serial.println("----------------------------");
}

void loop()
{
  conditionValue = analogRead(POT);

  Serial.println("\n--- SHIPMENT DETAILS ---");

  Serial.print("Condition Value: ");
  Serial.println(conditionValue);

  if (conditionValue <= 700)
  {
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);

    Serial.println("SHIPMENT: NORMAL");
    Serial.println("STATUS: SAFE");
  }
  else
  {
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    Serial.println("SHIPMENT: CONDITION ALERT");
    Serial.println("STATUS: CHECK REQUIRED");
  }

  Serial.println("----------------------------");

  delay(1000);
}