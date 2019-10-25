//Written by Ahmet Burkay KIRNIK
//TR_CapaFenLisesi
//Measure Angle with a MPU-6050(GY-521)

// #include<Wire.h>

#include <Arduino.h>

#include "MotionManager.h"
#include "timer.h"
#include "timerManager.h"
#include "timerManager.h"

void runTest();
void setupWheels();
void testProgress();
void setupTimer();
void spinner();


//Timer object
Timer testTimer;
Timer progressTimer;
Timer spinnerTimer;
int currentTest = 1;
bool testInProgress = false;
bool highSpeed = false;
enum
{
  LEFT_WHEEL_FORWARD = 1,
  LEFT_WHEEL_REVERSE,
  RIGHT_WHEEL_FORWARD,
  RIGHT_WHEEL_REVERSE,
  BOTH_WHEELS_FORWARD,
  BOTH_WHEELS_REVERSE,
  BOTH_WHEELS_STOP,
  ALL_DONE,
};

void setupWheels()
{
  ElyirMowerMotionManager_setup();
}
void setupTimer()
{
  testTimer.setInterval(3000);
  progressTimer.setInterval(1000);
  spinnerTimer.setInterval(50);

  //Set our callback function
  testTimer.setCallback(runTest);
  progressTimer.setCallback(testProgress);
  spinnerTimer.setCallback(spinner);

  //Start the timer
  // timer.start();
  TimerManager::instance().start();
}

void runTest()
{
  if(currentTest != ALL_DONE){
    if(highSpeed) {
      Serial.println("\n");
      Serial.print("-- Full Speed -- ");
    } else {
      Serial.println("\n");
      Serial.print("-- Half Speed -- ");
    }
      // Serial.println("------------------------\n");
  }
   
  if(highSpeed) {
    ElyirMowerMotionManager_forward(100);
  } else {
    ElyirMowerMotionManager_forward(50);
  }
  switch (currentTest)
  {
  case LEFT_WHEEL_FORWARD:
    testInProgress = true;
    Serial.println("");
    Serial.print("");
    Serial.println("Testing Left Wheel Forward ");
    ElyirMowerMotionManager_turnRight(75);
    break;
  case LEFT_WHEEL_REVERSE:
    testInProgress = true;
    Serial.println("");
    Serial.print("");
    Serial.println("Testing Left Wheel Reverse ");
    ElyirMowerMotionManager_turnLeft(75, true);
    break;
  case RIGHT_WHEEL_FORWARD:
    testInProgress = true;
    Serial.println("");
    Serial.print("");
    Serial.println("Testing Right Wheel Forward ");
    ElyirMowerMotionManager_turnLeft(75);
    break;
  case RIGHT_WHEEL_REVERSE:
    testInProgress = true;
    Serial.println("");
    Serial.print("");
    Serial.println("Testing Right Wheel Reverse ");
    ElyirMowerMotionManager_turnRight(75, true);
    break;
  case BOTH_WHEELS_FORWARD:
    testInProgress = true;
    Serial.println("");
    Serial.print("");
    Serial.println("Testing Both Wheels Forward ");
    ElyirMowerMotionManager_forward(75);
    break;
  case BOTH_WHEELS_REVERSE:
    testInProgress = true;
    Serial.println("");
    Serial.print("");
    Serial.println("Testing Both Wheels Reverse ");
    _left.reverse();
    _right.reverse();
    break;
  case BOTH_WHEELS_STOP:
    testInProgress = true;
    Serial.println("");
    Serial.print("");
    Serial.println("Testing Both Wheels Stop ");
    _left.stop();
    _right.stop();
    break;
  case ALL_DONE:
    testInProgress = false;
    Serial.println("");
    Serial.print("");
    if(highSpeed) {
      Serial.print("Full Speed ");
    } else {
      Serial.print("Half Speed ");
    }
    Serial.print("Tests Completed, Sarting over with ");
    if(!highSpeed) {
      Serial.print("Full Speed \n:----------------------------:");
    } else {
      Serial.println("Half Speed \n:----------------------------:");
    }
    Serial.println(" ");
    highSpeed = !highSpeed;
    currentTest = 0;
    break;
  default:
    testInProgress = false;
    break;
  }
  // if(testInProgress){
  currentTest++;
  // }
}

void testProgress()
{
  if (testInProgress)
  {
    Serial.print("=========");
  }
}
int spin = 0;
void spinner()
{
  if (testInProgress)
  {

    switch (spin)
    {
    case 0:
      Serial.print('\b');
      Serial.print("-");
      break;
    case 1:
      Serial.print('\b');
      Serial.print("|");
      break;
    case 2:
      Serial.print('\b');
      Serial.print("/");
      break;
    case 3:
      Serial.print('\b');
      Serial.print("-");
      break;
    case 4:
      Serial.print('\b');
      Serial.print("|");
      break;
    default:
      spin = -1;
      break;
    }
    spin++;
  }
}

void setup()
{

  Serial.begin(115200);
  setupWheels();
  setupTimer();
  Serial.println("Elyir Mower Test :::: Wheels \n----------------------------------------- \n-----------------------------------------");
  runTest();
}
void loop()
{

  TimerManager::instance().update();
}
