int voltagePin = A0;
int currentPin = A1;
int PRECISION = 7;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float measurement = 0;  // variable to store the value coming from the sensor
  float voltage = 0.00;
  float analog;

  measurement = analogRead(voltagePin);
  if (measurement > 53) {
    Serial.print("received (voltage) = ");
    Serial.println(measurement);
  
    analog = (measurement * 5.00)/1023.00;
    Serial.print("voltage = ");
    Serial.println(analog, PRECISION);
    voltage = analog * 0.5;
    Serial.print("voltage (halved) = ");
    Serial.println(voltage, PRECISION);

    float vout;
    float current;
    measurement = analogRead(currentPin);
    Serial.print("received (current) = ");
    Serial.println(measurement);
    
    vout = (measurement * 5.00)/1023.00;
    Serial.print("vout = ");
    Serial.println(vout, PRECISION);
    
    current = float(vout) / float((100*2.2));
    Serial.print("current = ");
    Serial.println(current, PRECISION);
    Serial.println();
  
    float power = voltage * current;
    Serial.print("power = ");
    Serial.println(power, 9);     // nano resolution
    Serial.println();
  }
    

//  delay(1);
}
