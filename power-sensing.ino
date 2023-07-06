// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText 2023 Kristin Ebuengan
// SPDX-FileCopyrightText 2023 Melody Gill
// SPDX-FileCopyrightText 2023 Gabriel Marcano

/*
* Read voltage and current using Soil Power Board with an Arduino Uno.
* Take samples once a large enough voltage is detected, and print them to
* serial in CSV format after all the samples are taken.
*/

#include <Vector.h>

int voltagePin = A0;
int currentPin = A1;
int PRECISION = 7;     // Number of decimal places to print
int SAMPLES = 20;      // Number of samples to take
constexpr int MAX_SIZE = 128;     // Max number of samples
int MIN_VOLT_VAL = 53;  // If value from ADC for voltage is above this, then start sampling
                        // 53 from ADC is about 0.25V

int GAIN = 100;   // Gain value selected on the board
float R = 2.2;    // Selected sense resistor

int arr[MAX_SIZE];
int arr2[MAX_SIZE];
Vector<int> voltageArray(arr, 0);
Vector<int> currentArray(arr2, 0);

void setup() {
  Serial.begin(9600);
  Serial.println("voltage,current,power");
}

void loop() {
  float measurement = 0;  // variable to store the value coming from the sensor

  /*
   * V = 5D / 1024
  */

 // Get voltage mesurement
  measurement = analogRead(voltagePin);
  if (measurement > MIN_VOLT_VAL) {
    voltageArray.push_back(measurement);

    // Get current measurement
    measurement = analogRead(currentPin);
    currentArray.push_back(measurement);

    // Take samples from ADC
    for (int i = 0; i < SAMPLES; i++) {
      // Get voltage measurement
      measurement = analogRead(voltagePin);
      voltageArray.push_back(measurement);

      // Get current measurement
      measurement = analogRead(currentPin);
      currentArray.push_back(measurement);

      delayMicroseconds(500);
    }

    output_csv(voltageArray, currentArray);

    // Clear the arrays to get a new sample
    voltageArray.clear();
    currentArray.clear();
  }
}

/**
 * Write the voltage, current, and power values from the two arrays to serial in CSV format
 */
void output_csv(Vector<int> voltageArray, Vector<int> currentArray) {
  for (int i = 0; i < voltageArray.size(); i++) {
    // 5V is the reference voltage of the ADC on the Arduino Uno
    // 1024 is the maximum resolution of ADC (10 bits)
    
    // Calculate voltage
    float analog = (voltageArray.at(i) * 5.00)/1024.00;
    float voltage = analog * 0.5;     // Only if voltage comes from the VOLT 2X SENSE pin
    Serial.print(voltage, PRECISION);
    Serial.print(",");

    // Output current info
    float vout = (currentArray.at(i) * 5.00)/1024.00;
    float current = float(vout) / float((GAIN*R));
    Serial.print(current, PRECISION);
    Serial.print(",");

    // Output power info
    float power = voltage * current;
    Serial.print(power, 9); // nano resolution
    Serial.println();
  }
}
