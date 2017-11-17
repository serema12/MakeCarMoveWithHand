/*
    L3G4200D Triple Axis Gyroscope: Pitch, Roll and Yaw.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-l3g4200d.html
    GIT: https://github.com/jarzebski/Arduino-L3G4200D
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <L3G4200D.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

L3G4200D gyroscope;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
void setup() 
{
  Serial.begin(115200);
   
  // Initialize L3G4200D
  Serial.println("Initialize L3G4200D");

  // Set scale 2000 dps and 400HZ Output data rate (cut-off 50)
  while(!gyroscope.begin(L3G4200D_SCALE_2000DPS, L3G4200D_DATARATE_400HZ_50))
  {
    Serial.println("Could not find a valid L3G4200D sensor, check wiring!");
    delay(500);
  }
 
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  gyroscope.calibrate(100);
   
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00001
  radio.openReadingPipe(1, addresses[0]); // 00002
  radio.setPALevel(RF24_PA_MIN);
}

void loop()
{
  delay(5);
   radio.stopListening();
  float a[3];
    XYZ();
    a[0]=pitch;
    a[1]=roll;
   a[2]=yaw;
  Serial.print(" Pitch = ");
  Serial.print(a[0]);
  Serial.print(" Roll = ");
  Serial.print(a[1]);  
  Serial.print(" Yaw = ");
  Serial.print(a[2]);
  Serial.println("");

 
 
 
   radio.write(&a[1],sizeof(a[1]));
    delay(100);
   if (roll<-3.5) roll=-3;
   if (roll>3.5) roll=3; 
  
}
void XYZ ()
{  
  timer = millis();

  // Read normalized values
  Vector norm = gyroscope.readNormalize();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  // Output raw
 // Serial.print(" Pitch = ");
 // Serial.print(pitch);
 // Serial.print(" Roll = ");
 // Serial.print(roll);  
//  Serial.print(" Yaw = ");
 // Serial.println(yaw);

  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
} 

