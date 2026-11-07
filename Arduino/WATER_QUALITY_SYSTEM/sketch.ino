#define PH_SENSOR A0
#define TURBIDITY_SENSOR A1
#define LED 8

int phValue;
int turbidityValue;

float simulatedPH;

void setup()
{
  Serial.begin(9600);

  pinMode(PH_SENSOR, INPUT);
  pinMode(TURBIDITY_SENSOR, INPUT);
  pinMode(LED, OUTPUT);

  Serial.println("SMART WATER QUALITY MONITORING");
  Serial.println("--------------------------------");
}

void loop()
{
  phValue = analogRead(PH_SENSOR);
  turbidityValue = analogRead(TURBIDITY_SENSOR);

  // Simulated pH value (0 to 14)
  simulatedPH = phValue * (14.0 / 1023.0);

  Serial.println("\n--- WATER QUALITY DETAILS ---");

  Serial.print("Simulated pH Value: ");
  Serial.println(simulatedPH, 2);

  Serial.print("Turbidity Value: ");
  Serial.println(turbidityValue);

  if (simulatedPH < 6.5 || simulatedPH > 8.5 ||
      turbidityValue > 600)
  {
    digitalWrite(LED, HIGH);
    Serial.println("WATER STATUS: QUALITY ALERT");
  }
  else
  {
    digitalWrite(LED, LOW);
    Serial.println("WATER STATUS: NORMAL");
  }

  Serial.println("--------------------------------");

  delay(1000);
}