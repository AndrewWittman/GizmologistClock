/*
 * Created by CPDiener on 9/11/2023
 * Provides the motor movement for numbers
 * */

// Height is around 1.44 x width

#include <Arduino.h>
#include <Numbers.h>
#include <Plane.h>
#include <Stepper.h>
#include <Servo.h>

void Numbers::draw0(Stepper &motorX, Stepper &motorY, Plane numPlace, int currentX, int currentY, Servo &pen, int penUp, int penDown) {
  relativeMove(motorX, motorY, numPlace, 10, 10);
  pen.write(penDown-3);
  delay(200);
  relativeMove(motorX, motorY, numPlace, 10, 90);
  pen.write(penDown-3);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 90, 90);
  pen.write(penDown-3);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 90, 10);
  pen.write(penDown-3);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 10);
  pen.write(penUp);
  delay(200);
}
void Numbers::draw1(Stepper &motorX, Stepper &motorY, Plane numPlace, int currentX, int currentY, Servo &pen, int penUp, int penDown) {
    relativeMove(motorX, motorY, numPlace, 10, 90);
    pen.write(penDown+2);
    delay(200);
    relativeMove(motorX, motorY, numPlace, 10, 10);
    delay(50);    
    pen.write(penUp);
    delay(200);
}
void Numbers::draw2(Stepper &motorX, Stepper &motorY, Plane numPlace, int currentX, int currentY, Servo &pen, int penUp, int penDown) {
    relativeMove(motorX, motorY, numPlace, 90, 10);
    pen.write(penDown+2);
    delay(200);
    relativeMove(motorX, motorY, numPlace, 10, 10);
    pen.write(penDown);
    delay(50);    
    relativeMove(motorX, motorY, numPlace, 10, 50);
    delay(50);
    relativeMove(motorX, motorY, numPlace, 90, 50);
    delay(50);
    relativeMove(motorX, motorY, numPlace, 90, 90);
    delay(50);
    relativeMove(motorX, motorY, numPlace, 10, 90);
    delay(50);
    pen.write(penDown-20);
    delay(50);
    relativeMove(motorX, motorY, numPlace, 10, 80);
    pen.write(penUp);
    delay(200);
}
void Numbers::draw3(Stepper &motorX, Stepper &motorY, Plane numPlace, int currentX, int currentY, Servo &pen, int penUp, int penDown){
  relativeMove(motorX, motorY, numPlace, 90, 10);
  pen.write(penDown);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 10);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 50);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 50, 50);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 50);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 90);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 90, 90);
  pen.write(penUp);
  delay(50);
}
void Numbers::draw4(Stepper &motorX, Stepper &motorY, Plane numPlace, int currentX, int currentY, Servo &pen, int penUp, int penDown){
  relativeMove(motorX, motorY, numPlace, 90, 10);
  pen.write(penDown-2);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 90, 50);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 50);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 10);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 90);
  pen.write(penUp);
  delay(50);
}
void Numbers::draw5(Stepper &motorX, Stepper &motorY, Plane numPlace, int currentX, int currentY, Servo &pen, int penUp, int penDown){
  relativeMove(motorX, motorY, numPlace, 90, 90);
  pen.write(penDown);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 90);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 50);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 90, 50);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 90, 10);
  delay(50);
  pen.write(penDown+2);
  relativeMove(motorX, motorY, numPlace, 10, 10);
  pen.write(penUp);
  delay(50);
}
void Numbers::draw6(Stepper &motorX, Stepper &motorY, Plane numPlace, int currentX, int currentY, Servo &pen, int penUp, int penDown){
  relativeMove(motorX, motorY, numPlace, 10, 10);
  pen.write(penDown);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 90, 10);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 90, 90);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 90);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 50);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 90, 50);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 50);
  delay(50);
  pen.write(penUp);
  delay(50);
}

void Numbers::draw7(Stepper &motorX, Stepper &motorY, Plane numPlace, int currentX, int currentY, Servo &pen, int penUp, int penDown) {
    relativeMove(motorX, motorY, numPlace, 90, 10);
    pen.write(penDown+2);
    delay(200);
    relativeMove(motorX, motorY, numPlace, 10, 10);
    pen.write(penDown);
    delay(50);    
    relativeMove(motorX, motorY, numPlace, 10, 90);
    delay(10);
    relativeMove(motorX, motorY, numPlace, 10, 80);
    pen.write(penUp);
    delay(200);
}
void Numbers::draw8(Stepper &motorX, Stepper &motorY, Plane numPlace, int currentX, int currentY, Servo &pen, int penUp, int penDown) {
    relativeMove(motorX, motorY, numPlace, 10, 10);
    pen.write(penDown);
    delay(200);
    relativeMove(motorX, motorY, numPlace, 10, 50);
    delay(50);
    relativeMove(motorX, motorY, numPlace, 90, 50);
    delay(50);
    relativeMove(motorX, motorY, numPlace, 90, 90);
    delay(50);
    relativeMove(motorX, motorY, numPlace, 10, 90);
    delay(50);
    relativeMove(motorX, motorY, numPlace, 10, 50);
    delay(50);
    relativeMove(motorX, motorY, numPlace, 90, 50);
    delay(50);
    relativeMove(motorX, motorY, numPlace, 90, 10);
    delay(50);
    pen.write(penDown+2);
    relativeMove(motorX, motorY, numPlace, 10, 10);
    pen.write(penUp);
    delay(50);
}

void Numbers::draw9(Stepper &motorX, Stepper &motorY, Plane numPlace, int currentX, int currentY, Servo &pen, int penUp, int penDown){
  relativeMove(motorX, motorY, numPlace, 90, 90);
  pen.write(penDown);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 90);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 10);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 90, 10);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 90, 50);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 10, 50);
  delay(50);
  relativeMove(motorX, motorY, numPlace, 90, 50);
  delay(50);
  pen.write(penUp);
  delay(50);
}

void Numbers::relativeMoveX(Stepper &motorX, Plane numPlace, int relX) {
  int width = numPlace.getWidth();
  int height = numPlace.getHeight();
  int relWidth = 100 * (width / height);
  int absX = ((relX / relWidth) * width) + numPlace.getXMin();
  motorX.moveTo(absX);

}


void Numbers::relativeMove(Stepper &motorX, Stepper &motorY, Plane numPlace, int relX, int relY) {
  float width = numPlace.getWidth();
  float height = numPlace.getHeight();

  // Convert percentages (0–100) to absolute positions
  float absX = numPlace.getXMin() + (relX / 100.0f) * width;
  float absY = numPlace.getYMin() + (relY / 100.0f) * height;

  Serial.print("Moving to X: "); Serial.print(absX);
  Serial.print(", Y: "); Serial.println(absY);

  motorX.moveTo((int)absX);
  motorY.moveTo((int)absY);
}