#define PIR 2
#define LDR A0
#define POT A1
#define LED 8

int motionValue;
int lightValue;
int energyValue;

void setup()
{
  Serial.begin(9600);

  pinMode(PIR, INPUT);
  pinMode(LDR, INPUT);
  pinMode(POT, INPUT);
  pinMode(LED, OUTPUT);

  Serial.println("SMART FACILITY MONITORING");
  Serial.println("-------------------------");
}

void loop()
{
  motionValue = digitalRead(PIR);
  lightValue = analogRead(LDR);
  energyValue = analogRead(POT);

  Serial.println("\n--- FACILITY DETAILS ---");

  Serial.print("Motion: ");
  if (motionValue == HIGH)
    Serial.println("DETECTED");
  else
    Serial.println("NOT DETECTED");

  Serial.print("Light Value: ");
  Serial.println(lightValue);

  Serial.print("Simulated Energy Value: ");
  Serial.println(energyValue);

  if (motionValue == HIGH)
  {
    digitalWrite(LED, HIGH);
    Serial.println("ACCESS ACTIVITY: DETECTED");
  }
  else
  {
    digitalWrite(LED, LOW);
    Serial.println("ACCESS ACTIVITY: NONE");
  }

  if (lightValue < 500)
    Serial.println("LIGHT: LOW");
  else
    Serial.println("LIGHT: SUFFICIENT");

  if (energyValue > 700)
    Serial.println("ENERGY STATUS: HIGH");
  else
    Serial.println("ENERGY STATUS: NORMAL");

  Serial.println("-------------------------");

  delay(1000);
}