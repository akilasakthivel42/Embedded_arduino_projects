#define VOLTAGE_SENSOR A0
#define CURRENT_SENSOR A1
#define LED 8

int voltageValue;
int currentValue;

float voltage;
float current;
float power;

void setup()
{
  Serial.begin(9600);

  pinMode(VOLTAGE_SENSOR, INPUT);
  pinMode(CURRENT_SENSOR, INPUT);
  pinMode(LED, OUTPUT);

  Serial.println("ELECTRICAL GRID MONITORING");
  Serial.println("-------------------------");
}

void loop()
{
  voltageValue = analogRead(VOLTAGE_SENSOR);
  currentValue = analogRead(CURRENT_SENSOR);

  // Simulated voltage range: 0 to 24 V
  voltage = voltageValue * (24.0 / 1023.0);

  // Simulated current range: 0 to 5 A
  current = currentValue * (5.0 / 1023.0);

  power = voltage * current;

  Serial.println("\n--- GRID DETAILS ---");

  Serial.print("Voltage: ");
  Serial.print(voltage, 2);
  Serial.println(" V");

  Serial.print("Current: ");
  Serial.print(current, 2);
  Serial.println(" A");

  Serial.print("Power: ");
  Serial.print(power, 2);
  Serial.println(" W");

  if (voltage >= 10 && voltage <= 20)
  {
    digitalWrite(LED, HIGH);
    Serial.println("GRID STATUS: NORMAL");
    Serial.println("ENERGY STATUS: STABLE");
  }
  else
  {
    digitalWrite(LED, LOW);
    Serial.println("GRID STATUS: VOLTAGE ALERT");
    Serial.println("ENERGY STATUS: CHECK REQUIRED");
  }

  Serial.println("-------------------------");

  delay(1000);
}