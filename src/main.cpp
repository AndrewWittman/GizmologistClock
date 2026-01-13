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

int lastMinute = -1;
int lastHour   = -1;

unsigned long lastMinuteTick = 0;     // last time we advanced the minute (ms)
const unsigned long minuteMs = 60000; // 60,000 ms in a minute

int curHour = 4;   // starting hour
int curMinute = 39;  // starting minute

int penPos = 20;
int penUp = 110;
int penDown = 145;

// Pins for the stepper motors
int dirPinLat = 2; // X direction pin
int stepPinLat = 3; // X step pin
int dirPinLong = 5; // Y direction pin, change to 4 for breadboard
int stepPinLong = 6; // Y step pin, change to 5 for breadboard
int hourHigh = 4 ; 
int hourLow = 7 ;
int minHigh = 9 ; //switch to 12 on breadboard
int minLow = 8 ;

int penServoPin = 12; // Pen servo pin, switch to 9 on breadboard

int latLowSwitch = 10; // X low limit switch
int latHighSwitch = 11; // X high limit switch

int longLowSwitch = 13; // Y low limit switch



// Create the stepper motors
Stepper stepperLat = Stepper(stepPinLat, dirPinLat); // X stepper
Stepper stepperLong = Stepper(stepPinLong, dirPinLong); // Y stepper

Plane minuteLowPlace = Plane(106, 417, 0, 560); // Plane for the minute low digit
Plane minuteHighPlace = Plane(576, 901, 0, 560); // Plane for the minute high digit

Plane hourLowPlace = Plane(1064, 1381, 0, 560); // Plane for the hour low digit
Plane hourHighPlace = Plane(1545, 1812, 0, 560); // Plane for the hour high digit

Numbers nums;

void clearDigitSelect();
void selectDigit(int pin);
void drawDigit(Numbers &nums, int digit,
               Stepper &stepperLat, Stepper &stepperLong,
               Plane place, Servo &pen);
void drawTime(Numbers &nums,
              int hour,
              int minute,
              Stepper &stepperLat,
              Stepper &stepperLong,
              Servo &pen);
void computeDisplayDigits(int hour, int minute,
                          int &hTens, int &hOnes,
                          int &mTens, int &mOnes);

void drawTimeChanged(Numbers &nums,
                     int prevHour, int prevMinute,
                     int hour, int minute,
                     Stepper &stepperLat,
                     Stepper &stepperLong,
                     Servo &pen);

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

  
  digitalWrite(hourHigh,1);
  digitalWrite(hourLow,1);
  digitalWrite(minHigh,1);
  digitalWrite(minLow,1);
  delay(500);
  
  lastHour = curHour;
  lastMinute = curMinute;
  lastMinuteTick = millis();

  Serial.print("Starting software clock at ");
  Serial.print(curHour);
  Serial.print(":");
  if (curMinute < 10) Serial.print('0');
  Serial.println(curMinute);

  // Draw initial time
  drawTime(nums, curHour, curMinute, stepperLat, stepperLong, pen);
  Serial.print(stepperLat._maxPosition);



}

void loop() {
  stepperLat.moveTo(20);
  static unsigned long lastPrint = 0;
  unsigned long nowMs = millis();

  // Advance software time every minute
  if (nowMs - lastMinuteTick >= minuteMs) {
    lastMinuteTick += minuteMs;  // handles drift/wrap

    int prevHour = curHour;
    int prevMinute = curMinute;

    // tick time
    curMinute++;
    if (curMinute >= 60) {
      curMinute = 0;
      curHour++;
      if (curHour >= 24) curHour = 0;  // 24h wrap
    }

    // Recalibrate every 2 minutes (testing) or 10 in final
    if (curMinute % 5 == 0) {
      pen.write(penUp);
      delay(200);
      stepperLong.calibrateOne(longLowSwitch);
      stepperLat.calibrate(latLowSwitch, latHighSwitch);
    }

    Serial.print("Updating display for time ");
    if (curHour < 10) Serial.print('0');
    Serial.print(curHour);
    Serial.print(':');
    if (curMinute < 10) Serial.print('0');
    Serial.println(curMinute);

    // 🔹 Only redraw digits that changed
    drawTimeChanged(nums, prevHour, prevMinute,
                    curHour, curMinute,
                    stepperLat, stepperLong, pen);

    lastHour = curHour;
    lastMinute = curMinute;
  }

  // Optional: print current software time once per second for debug
  if (nowMs - lastPrint >= 1000) {
    lastPrint = nowMs;
    Serial.print("Software Time: ");
    if (curHour < 10) Serial.print('0');
    Serial.print(curHour);
    Serial.print(':');
    if (curMinute < 10) Serial.print('0');
    Serial.print(curMinute);
    Serial.print(" (ms=");
    Serial.print(nowMs);
    Serial.println(")");
  }
}

void clearDigitSelect() {
  digitalWrite(minLow, LOW);
  digitalWrite(minHigh, LOW);
  digitalWrite(hourLow, LOW);
  digitalWrite(hourHigh, LOW);
}

void selectDigit(int pin) {
  clearDigitSelect();
  if (pin >= 0) {
    digitalWrite(pin, HIGH);
  }
}

void drawDigit(Numbers &nums,
               int digit,
               Stepper &stepperLat,
               Stepper &stepperLong,
               Plane place,
               Servo &pen)
{
  switch (digit) {
    case 0: nums.draw0(stepperLat, stepperLong, place, stepperLat.getPos(), stepperLong.getPos(), pen, penUp, penDown); break;
    case 1: nums.draw1(stepperLat, stepperLong, place, stepperLat.getPos(), stepperLong.getPos(), pen, penUp, penDown); break;
    case 2: nums.draw2(stepperLat, stepperLong, place, stepperLat.getPos(), stepperLong.getPos(), pen, penUp, penDown); break;
    case 3: nums.draw3(stepperLat, stepperLong, place, stepperLat.getPos(), stepperLong.getPos(), pen, penUp, penDown); break;
    case 4: nums.draw4(stepperLat, stepperLong, place, stepperLat.getPos(), stepperLong.getPos(), pen, penUp, penDown); break;
    case 5: nums.draw5(stepperLat, stepperLong, place, stepperLat.getPos(), stepperLong.getPos(), pen, penUp, penDown); break;
    case 6: nums.draw6(stepperLat, stepperLong, place, stepperLat.getPos(), stepperLong.getPos(), pen, penUp, penDown); break;
    case 7: nums.draw7(stepperLat, stepperLong, place, stepperLat.getPos(), stepperLong.getPos(), pen, penUp, penDown); break;
    case 8: nums.draw8(stepperLat, stepperLong, place, stepperLat.getPos(), stepperLong.getPos(), pen, penUp, penDown); break;
    case 9: nums.draw9(stepperLat, stepperLong, place, stepperLat.getPos(), stepperLong.getPos(), pen, penUp, penDown); break;
  }
}

void drawTime(Numbers &nums,
              int hour,
              int minute,
              Stepper &stepperLat,
              Stepper &stepperLong,
              Servo &pen)
{
  // Convert 24h -> 12h for display
  if (hour == 0) {
    hour = 12;        // 00:xx -> 12:xx AM
  } else if (hour > 12) {
    hour -= 12;       // 13–23 -> 1–11 PM
  }

  int hTens = hour / 10;     // 0 or 1 for 1–12
  int hOnes = hour % 10;
  int mTens = minute / 10;
  int mOnes = minute % 10;

  // --- Hour tens (leftmost) ---
  // Only draw if non-zero (i.e., 10, 11, 12 -> 1)
  if (hTens > 0) {
    selectDigit(hourHigh);
    drawDigit(nums, hTens, stepperLat, stepperLong, hourHighPlace, pen);
    delay(200);
  } else {
    // Just ensure selector LEDs off; we do NOT draw a 0 here.
    clearDigitSelect();
  }

  // --- Hour ones ---
  selectDigit(hourLow);
  drawDigit(nums, hOnes, stepperLat, stepperLong, hourLowPlace, pen);
  delay(200);

  // --- Minute tens ---
  selectDigit(minHigh);
  drawDigit(nums, mTens, stepperLat, stepperLong, minuteHighPlace, pen);
  delay(200);

  // --- Minute ones ---
  selectDigit(minLow);
  drawDigit(nums, mOnes, stepperLat, stepperLong, minuteLowPlace, pen);
  delay(200);

  clearDigitSelect();
  pen.write(penUp);  // make sure pen is up at end
}

void computeDisplayDigits(int hour, int minute,
                          int &hTens, int &hOnes,
                          int &mTens, int &mOnes)
{
  // Apply same 12h + leading-blank logic basis
  if (hour == 0) {
    hour = 12;
  } else if (hour > 12) {
    hour -= 12;
  }

  hTens = hour / 10;       // 0 or 1
  hOnes = hour % 10;
  mTens = minute / 10;
  mOnes = minute % 10;
}

void drawTimeChanged(Numbers &nums,
                     int prevHour, int prevMinute,
                     int hour, int minute,
                     Stepper &stepperLat,
                     Stepper &stepperLong,
                     Servo &pen)
{
  int oldHT, oldHO, oldMT, oldMO;
  int newHT, newHO, newMT, newMO;

  computeDisplayDigits(prevHour, prevMinute, oldHT, oldHO, oldMT, oldMO);
  computeDisplayDigits(hour,      minute,     newHT, newHO, newMT, newMO);

  // --- Hour tens (leftmost) ---
  if (newHT != oldHT) {
    clearDigitSelect();
    if (newHT > 0) { // only draw if non-zero; keeps leading blank for 1-9
      selectDigit(hourHigh);
      drawDigit(nums, newHT, stepperLat, stepperLong, hourHighPlace, pen);
      delay(200);
    }
    // if newHT == 0: we leave it blank (no draw)
  }

  // --- Hour ones ---
  if (newHO != oldHO) {
    selectDigit(hourLow);
    drawDigit(nums, newHO, stepperLat, stepperLong, hourLowPlace, pen);
    delay(200);
  }

  // --- Minute tens ---
  if (newMT != oldMT) {
    selectDigit(minHigh);
    drawDigit(nums, newMT, stepperLat, stepperLong, minuteHighPlace, pen);
    delay(200);
  }

  // --- Minute ones ---
  if (newMO != oldMO) {
    selectDigit(minLow);
    drawDigit(nums, newMO, stepperLat, stepperLong, minuteLowPlace, pen);
    delay(200);
  }

  clearDigitSelect();
  pen.write(penUp);
}