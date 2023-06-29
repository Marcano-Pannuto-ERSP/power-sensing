/*
* Read voltage and current using Soil Power Board with an Arduino Uno
*/

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

  /*
   * V = 5D / 1024
  */

  measurement = analogRead(voltagePin);
  if (measurement > 53) { // 53 is .25V
    Serial.print("received (voltage) = ");
    Serial.println(measurement);

    // 5V is the reference voltage of the ADC on the Arduino Uno
    // 1024 is the maximum resolution of ADC (10 bits)
    analog = (measurement * 5.00)/1024.00;
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

    // 5V is the reference voltage of the ADC on the Arduino Uno
    // 1024 is the maximum resolution of ADC (10 bits)
    vout = (measurement * 5.00)/1024.00;
    Serial.print("vout = ");
    Serial.println(vout, PRECISION);
    
    // 100 is G on the board
    // 2.2 is the number below the range
    current = float(vout) / float((100*2.2));
    Serial.print("current = ");
    Serial.println(current, PRECISION);
    Serial.println();
  
    float power = voltage * current;
    Serial.print("power = ");
    Serial.println(power, 9); // nano resolution
    Serial.println();
  }

//  delay(1);
}
