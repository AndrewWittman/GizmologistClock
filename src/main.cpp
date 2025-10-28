/*
 * Created by CPDiener on 9/6/2023
 * Functions as the main file arduino file for the clock (replacing the typical .ino file)
 * */

#include <Arduino.h>
#include <Stepper.h>
#include <Numbers.h>
#include <ClockFunction.h>
#include <Servo.h>
#include <Plane.h>

Servo pen;

int penPos = 20;
int penUp = 110;
int penDown = 145;

// Pins for the stepper motors
int dirPinLat = 2; // X direction pin
int stepPinLat = 3; // X step pin
int dirPinLong = 4; // Y direction pin
int stepPinLong = 5; // Y step pin
int hourHigh = 6 ;
int hourLow = 7 ;
int minHigh = 12 ;
int minLow = 8 ;

int penServoPin = 9; // Pen servo pin

int blueLED = 7; // Blue LED pin

int latLowSwitch = 10; // X low limit switch
int latHighSwitch = 11; // X high limit switch

int longLowSwitch = 13; // Y low limit switch



// Create the stepper motors
Stepper stepperLat = Stepper(stepPinLat, dirPinLat); // X stepper
Stepper stepperLong = Stepper(stepPinLong, dirPinLong); // Y stepper

Plane hourHighPlace = Plane(86, 397, 0, 560); // Plane for the hour high digit
Plane hourLowPlace = Plane(556, 881, 0, 560); // Plane for the hour low digit

Plane minuteHighPlace = Plane(1054, 1371, 0, 560); // Plane for the minute high digit
Plane minuteLowPlace = Plane(1545, 1812, 0, 560); // Plane for the minute-low digit

Numbers nums;


void setup() {
  Serial.begin(9600);
  // Set the pin modes for the motors
  pinMode(stepPinLat, OUTPUT);
  pinMode(stepPinLong, OUTPUT);
  pinMode(dirPinLat, OUTPUT);
  pinMode(dirPinLong, OUTPUT);
  
  pinMode(minLow, OUTPUT);
  pinMode(minHigh, OUTPUT);
  pinMode(hourLow,OUTPUT);
  pinMode(hourHigh, OUTPUT);
  pen.attach(penServoPin);


//  pen.attach(penServoPin);


  // Set the pin modes for the limit switches
  pinMode(latLowSwitch, INPUT);
  pinMode(latHighSwitch, INPUT);
  pinMode(longLowSwitch, INPUT);


  delay(500);
  penPos = 110;  
  pen.write(penPos);

  // Calibrate the stepper motors
  stepperLong.calibrateOne(longLowSwitch);
  stepperLat.calibrate(latLowSwitch, latHighSwitch);

  //erase
  digitalWrite(minLow,1);
  digitalWrite(minHigh,1);
  digitalWrite(hourLow,1);
  digitalWrite(hourHigh,1);
  delay(200);
  digitalWrite(minLow,0);
  digitalWrite(minHigh,0);
  digitalWrite(hourLow,0);
  digitalWrite(hourHigh,0);
  delay(500);
  nums.draw1(stepperLat,stepperLong, hourHighPlace, stepperLat.getPos(), stepperLong.getPos(), pen);
  delay(500);
  nums.draw5(stepperLat,stepperLong, hourLowPlace, stepperLat.getPos(), stepperLong.getPos(), pen);
  delay(500);
  nums.draw2(stepperLat,stepperLong, minuteHighPlace, stepperLat.getPos(), stepperLong.getPos(), pen);
  delay(500);
  nums.draw1(stepperLat,stepperLong, minuteLowPlace, stepperLat.getPos(), stepperLong.getPos(), pen);
  Serial.print(stepperLat._maxPosition);







}

void loop() {
}
