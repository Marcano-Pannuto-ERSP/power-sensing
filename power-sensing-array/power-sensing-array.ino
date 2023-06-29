/*
* Read voltage and current using Soil Power Board with an Arduino Uno
*/

#include <Vector.h>

int voltagePin = A0;
int currentPin = A1;
int PRECISION = 7;
constexpr int MAX_SIZE = 128;

int arr[MAX_SIZE];
int arr2[MAX_SIZE];
Vector<int> voltageArray(arr,0);
Vector<int> currentArray(arr2,0);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float measurement = 0;  // variable to store the value coming from the sensor
  float voltage = 0.00;
  float analog;
  float power;

  /*
   * V = 5D / 1024
  */

  measurement = analogRead(voltagePin);
  if (measurement > 53) { // 53 is .25V
    // Serial.print("received (voltage) = ");
    // Serial.println(measurement);
    voltageArray.push_back(measurement);
    Serial.print("time in miliseconds (before): ");
    Serial.println(millis());

    // // 5V is the reference voltage of the ADC on the Arduino Uno
    // // 1024 is the maximum resolution of ADC (10 bits)
    // analog = (measurement * 5.00)/1024.00;
    // Serial.print("voltage = ");
    // Serial.println(analog, PRECISION);

    // voltage = analog * 0.5;
    // Serial.print("voltage (halved) = ");
    // Serial.println(voltage, PRECISION);

    float vout;
    float current;
    measurement = analogRead(currentPin);
    // Serial.print("received (current) = ");
    // Serial.println(measurement);
    currentArray.push_back(measurement);

    // // 5V is the reference voltage of the ADC on the Arduino Uno
    // // 1024 is the maximum resolution of ADC (10 bits)
    // vout = (measurement * 5.00)/1024.00;
    // Serial.print("vout = ");
    // Serial.println(vout, PRECISION);
    
    // // 100 is G on the board
    // // 2.2 is the number below the range
    // current = float(vout) / float((100*2.2));
    // Serial.print("current = ");
    // Serial.println(current, PRECISION);
    // Serial.println();
  
    // float power = voltage * current;
    // Serial.print("power = ");
    // Serial.println(power, 9); // nano resolution
    // Serial.println();

    for (int i = 0; i < 20; i++) {
      // Serial.println("hello there :)");
      measurement = analogRead(voltagePin);
      voltageArray.push_back(measurement);
      measurement = analogRead(currentPin);
      currentArray.push_back(measurement);
      delayMicroseconds(500);
    }
    Serial.print("time in miliseconds (middle): ");
    Serial.println(millis());

    // Serial.println(voltageArray.size());
    // Serial.println(currentArray.size());

    for (int i = 0; i < voltageArray.size(); i++) {
      Serial.print("raw measurement: ");
      Serial.println(voltageArray.at(i));
      analog = (voltageArray.at(i) * 5.00)/1024.00;
      voltage = analog * 0.5;
      Serial.print("voltage: ");
      Serial.println(voltage, PRECISION);

      vout = (currentArray.at(i) * 5.00)/1024.00;
      current = float(vout) / float((100*2.2));
      Serial.print("current = ");
      Serial.println(current, PRECISION);

      power = voltage * current;
      Serial.print("power = ");
      Serial.println(power, 9); // nano resolution
      Serial.println();
    }
    Serial.print("time in miliseconds (after): ");
    Serial.println(millis());

    voltageArray.clear();
    currentArray.clear();
  }

//  delay(1);
}
