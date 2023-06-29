/*
* Read voltage and current using Soil Power Board with an Arduino Uno.
* Take samples once a large enough voltage is detected, and print them to
* serial after all the samples are taken.
*/

#include <Vector.h>

int voltagePin = A0;
int currentPin = A1;
int PRECISION = 7;     // Number of decimal places to print
int SAMPLES = 20;      // Number of samples to take
constexpr int MAX_SIZE = 128;     // Max number of samples
int MIN_VOLT_VAL = 53;  // If value from ADC for voltage is above this, then start sampling
                        // 53 from ADC is about 0.25V

int arr[MAX_SIZE];
int arr2[MAX_SIZE];
Vector<int> voltageArray(arr, 0);
Vector<int> currentArray(arr2, 0);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float measurement = 0;  // variable to store the value coming from the sensor
  float voltage = 0.00;
  float analog;
  float power;
  float vout;
  float current;

  /*
   * V = 5D / 1024
  */

  measurement = analogRead(voltagePin);
  if (measurement > MIN_VOLT_VAL) {
    // Serial.print("received (voltage) = ");
    // Serial.println(measurement);
    voltageArray.push_back(measurement);
    Serial.print("time in miliseconds (before): ");
    Serial.println(millis());

    
    measurement = analogRead(currentPin);
    // Serial.print("received (current) = ");
    // Serial.println(measurement);
    currentArray.push_back(measurement);

    // Take samples from ADC
    for (int i = 0; i < SAMPLES; i++) {
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

    // Print sample information to serial
    for (int i = 0; i < voltageArray.size(); i++) {
      // Output voltage info
      Serial.print("raw measurement: ");
      Serial.println(voltageArray.at(i));
      // 5V is the reference voltage of the ADC on the Arduino Uno
      // 1024 is the maximum resolution of ADC (10 bits)
      analog = (voltageArray.at(i) * 5.00)/1024.00;
      voltage = analog * 0.5;
      Serial.print("voltage: ");
      Serial.println(voltage, PRECISION);

      // Output current info
      vout = (currentArray.at(i) * 5.00)/1024.00;
      current = float(vout) / float((100*2.2));
      Serial.print("current = ");
      Serial.println(current, PRECISION);

      // Output power info
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
}
