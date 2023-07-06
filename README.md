# Power-Sensing

## How to calulate the voltage, current, and power using the Soil Power Sensor Board

Refer to the Soil_Power_Sensing_Board_Manual.pdf on the repo to get the detials of how the Soil Power Sensor Board works.

**Voltage:**
A0 pin on the Arduino Uno is what you want to connect to the voltage you want to measure. The voltage you will receive is will be the voltage x2, so to see the true measurment of voltage you would want to half the amount you recieve.

NOTICE: the voltage will cap out at 2.4 V as this board was specifically made for Microbial Fuel Cells (MFCs) in mind. 

**Current:**
A1 pin on the Arduino Uno is what you want to connect to the voltage you want to measure

NOTICE: there aren't any precautions to prevent a circuit shortage