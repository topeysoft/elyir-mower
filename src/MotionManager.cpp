#include "Config.h"
#include <driver/dac.h>
#include "Arduino.h"
#include "MotionManager.h"


void ElyirMowerMotionManager_setup(){
    dac_output_enable(PIN_LEFT_MOTOR_VR);
    dac_output_enable(PIN_RIGHT_MOTOR_VR);
    pinMode(PIN_LEFT_MOTOR_EL, OUTPUT);
    pinMode(PIN_RIGHT_MOTOR_EL, OUTPUT);
    pinMode(PIN_LEFT_MOTOR_DIR, OUTPUT);
    pinMode(PIN_RIGHT_MOTOR_DIR, OUTPUT);
}

int speedPercentToPwm(int speedPercent){
  return map(speedPercent, 0, 100, PARAM_MOTOR_SPEED_MIN_PWM, PARAM_MOTOR_SPEED_MAX_PWM);
}

void _leftForward(int speedPercent){
  int speedVal = speedPercentToPwm(speedPercent);
  digitalWrite(PIN_LEFT_MOTOR_EL, HIGH);
  digitalWrite(PIN_LEFT_MOTOR_DIR, HIGH);
  dac_output_voltage(PIN_LEFT_MOTOR_VR, speedVal);
}
void _rightForward(int speedPercent){
  int speedVal = speedPercentToPwm(speedPercent);
  digitalWrite(PIN_RIGHT_MOTOR_EL, HIGH);
  digitalWrite(PIN_RIGHT_MOTOR_DIR, HIGH);
  dac_output_voltage(PIN_RIGHT_MOTOR_VR, speedVal);

}
void _leftReverse(int speedPercent){
  int speedVal = speedPercentToPwm(speedPercent);
  digitalWrite(PIN_LEFT_MOTOR_EL, HIGH);
  digitalWrite(PIN_LEFT_MOTOR_DIR, LOW);
  dac_output_voltage(PIN_LEFT_MOTOR_VR, speedVal);
}
void _rightReverse(int speedPercent){
  int speedVal = speedPercentToPwm(speedPercent);
  digitalWrite(PIN_RIGHT_MOTOR_EL, HIGH);
  digitalWrite(PIN_RIGHT_MOTOR_DIR, LOW);
  dac_output_voltage(PIN_RIGHT_MOTOR_VR, speedVal);
}
void _leftStop(){
  digitalWrite(PIN_LEFT_MOTOR_EL, HIGH);
}
void _rightStop(){
  digitalWrite(PIN_RIGHT_MOTOR_EL, LOW);
}

void ElyirMowerMotionManager_forward(int speedPercent){
  _leftForward(speedPercent);
  _rightForward(speedPercent);
}
void ElyirMowerMotionManager_backward (int speedPercent){
  _leftBackward(speedPercent);
  _rightBackward(speedPercent);
}
void ElyirMowerMotionManager_leftTurn (int speedPercent, bool reverse){
  if(!reverse){
    _leftStop()
  _rightForward(speedPercent);
  } else {
    _rightStop()
    _leftBackward(speedPercent);
  }
}
void ElyirMowerMotionManager_rightTurn (int speedPercent, bool reverse){
  if(!reverse){
    _leftForward(speedPercent);
  _rightStop();
  } else {
    _leftStop()
    _rightBackward(speedPercent);
  }
  
}
void ElyirMowerMotionManager_stop (){
  _leftStop();
  _rightStop();
}
void ElyirMowerMotionManager_zeroTurnLeft (int speedPercent, bool reverse){
  if(!reverse){
    _leftBackward(speedPercent);
  _rightForward(speedPercent);
  } else {
    _rightBackward(speedPercent);
    _leftForward(speedPercent);
  }
  
}
void ElyirMowerMotionManager_zeroTurnRight (int speedPercent, bool reverse){
  if(reverse){
    _leftBackward(speedPercent);
  _rightForward(speedPercent);
  } else {
    _rightBackward(speedPercent);
    _leftForward(speedPercent);
  }
}

// define zeroTurnAroundLeft control