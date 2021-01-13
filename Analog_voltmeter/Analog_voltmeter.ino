/*
DC Voltmeter 
Nithiwadee Thaicharoen

Modified from 
[1] https://www.electroschematics.com/arduino-digital-voltmeter/?fbclid=IwAR0Kkp78s5Bwi1jGN2MRhYXTVi1dI5TJkzCsJLj2fsR1XAd0o9VJwWipM6E
[2] https://www.allaboutcircuits.com/projects/make-a-digital-voltmeter-using-the-arduino/

LCD datasheet: https://www.openhacks.com/uploadsproductos/eone-1602a1.pdf

V. 1.0
  Wiring of the board is similar to one in [1]
  Read the input voltage from A0 and A1, output value on an LCD screen (1602A)
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int analogInput = 0;
float vread1 = 0.0;   // value read from A0
float vread2 = 0.0;   // value read from A1

float vin1 = 0.0;   // convert A0 read to voltage
float vin2 = 0.0;   // convert A1 read to voltage

float vscale1 = 0.0;   // scale A0 using potential divider
float vscale2 = 0.0;   // scale A1 using potential divider

float R1 = 0.0; // resistance of R1 (100K)
float R2 = 1.0; // resistance of R2 (10K)

String tset = "T SET: ";
String treal = "T REAL: ";

void setup(){

    Serial.begin(9600);     //  opens serial port, sets data rate to 9600 bps
      
    pinMode(analogInput, INPUT);
    lcd.begin(16, 2);
    lcd.print(tset);
//    lcd.print(tset.length());
    lcd.setCursor(0, 1);
    lcd.print(treal);

}
void loop(){
  
  //Conversion formula for voltage
  int vread1 = analogRead(A0);
  int vread2 = analogRead(A1);
  vin1 = (vread1 * 5.0) / 1024.0; // Convert bit value to volt
  vin2 = (vread2 * 5.0) / 1024.0; // Convert bit value to volt
  if (vin1 < 0.1) {
   vin1=0.0;
  } 
  if (vin2 < 0.1) {
   vin2=0.0;
  } 
  
  vscale1 = vin1 / (R2/(R1+R2));   // Scale the voltage using potential divider
  vscale2 = vin2 / (R2/(R1+R2));   // Scale the voltage using potential divider

  //Output readout value on an LCD
  lcd.setCursor(tset.length(), 0);  // top row
  lcd.print(vscale1);
  lcd.print(" C");

  lcd.setCursor(treal.length(), 1); // bottom row
  lcd.print(vscale2);
  lcd.print(" C");
  delay(500);
}
