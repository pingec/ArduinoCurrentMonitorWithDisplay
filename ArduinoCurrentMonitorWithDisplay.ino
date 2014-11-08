/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include "EmonLib.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 13, 4, 5, 6, 7);
// Create an EnergyMonitor instance 
EnergyMonitor emon1;
EnergyMonitor emon2;   
EnergyMonitor emon3;   

const int alarm_threshold = 25;
const int alarm_pin = 3;

void setup() {
  Serial.begin(9600);
  
  // Current: input pin, calibration. Cur Const= Ratio/BurdenR. 1800/62 = 29.
  emon1.current(0, 29 * 1.01); 
  // Current: input pin, calibration. Cur Const= Ratio/BurdenR. 1800/62 = 29.
  emon2.current(1, 29 * 1.01); 
  // Current: input pin, calibration. Cur Const= Ratio/BurdenR. 1800/62 = 29.
  emon3.current(2, 29 * 1.01); 
  
  // initialize the digital pin as an output (for alarm siren).
  pinMode(3, OUTPUT);  
  digitalWrite(alarm_pin, LOW); 
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a static text (line 0)
  lcd.print("Ph1   Ph2   Ph3");
}

void loop() {
  // Calculate Irms only
  double Irms = emon1.calcIrms(1480);
  double Irms2 = emon2.calcIrms(1480);
  double Irms3 = emon3.calcIrms(1480);
  
  if(Irms > alarm_threshold || Irms2 > alarm_threshold || Irms3 > alarm_threshold){
    digitalWrite(alarm_pin, HIGH);
  }
  else{
    digitalWrite(alarm_pin, LOW);
  }
  
  //Serial.print(Irms*230.0);	       // Apparent power

  //print to serial port
  Serial.print(Irms);		       // Irms
  Serial.print(" ");
  Serial.print(Irms2);		       // Irms
  Serial.print(" ");
  Serial.println(Irms3);	        // Irms

  //print to LCD display
  //convert doubles to strings
  char str1[6];
  char str2[6];
  char str3[6];
  //dtostrf(FLOAT,WIDTH,PRECSISION,BUFFER);  
  dtostrf(Irms, 1, 1, str1);
  dtostrf(Irms2, 1, 1, str2);
  dtostrf(Irms3, 1, 1, str3);
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // clear whole line
  lcd.print("                ");
  
  // reset the cursor
  lcd.setCursor(0, 1);
  // print the data
  lcd.print(str1);
  lcd.print("A");   
  lcd.setCursor(6, 1);
  lcd.print(str2);
  lcd.print("A");
  lcd.setCursor(12, 1);
  lcd.print(str3);
  lcd.print("A");
}
