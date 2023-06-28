int currentPin = A0;
int voltagePin = A1;


void setup() {
  Serial.begin(9600);
}

void loop() {
  float measurement = 0;  // variable to store the value coming from the sensor
  float voltage = 0.00;
  float analog;

  measurement = analogRead(voltagePin);
  Serial.print("received (voltage) = ");
  Serial.print(measurement);

  analog = (measurement * 5.00)/1023.00;
  Serial.print("    voltage = ");
  Serial.print(analog);
  voltage = analog * 0.5;
  Serial.print("    voltage (halved) = ");
  Serial.println(voltage);

  float vout;
  float current;
  measurement = analogRead(currentPin);
  Serial.print("received (current) = ");
  Serial.print(measurement);
  
  vout = (measurement * 5.00)/1023.00;
  Serial.print("    vout = ");
  Serial.print(vout);
  
  current = float(vout) / float((100*2.2));
  Serial.print("    current = ");
  Serial.println(current, 5);

  delay(1000);
}
