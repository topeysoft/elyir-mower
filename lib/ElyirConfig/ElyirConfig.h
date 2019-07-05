#ifndef ELYIR_CONFIG_H
#define ELYIR_CONFIG_H
#include "Arduino.h"

const int DATA_UPDATE_INTERVAL = 2000; // (miliseconds)

const HardwareSerial *megaPort = &Serial1;
const HardwareSerial GPS_PORT = Serial2;
// #define espPort Serial1

        // const int LOG_LEVEL_NONE = 0;
        // const int LOG_LEVEL_LOG = 1;
        // const int LOG_LEVEL_INFO= 2;
        // const int LOG_LEVEL_ERROR = 3;
        // const int LOG_LEVEL_VERIFIED = 4;
        // const int LOG_LEVEL_ALL = 5;

const int LOG_LEVEL = 5;
const int ESP_BAUD = 9600;
#define megaBaud 9600

const int LOG_BAUD_RATE = 9600; //  300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200;
const int GPS_BAUD_RATE = 38400;

const int ESP_RX_PIN = 16;
const int ESP_TX_PIN = 17;
const int CUT_HEIGHT_SERVO_PIN = 7;

#define MAX_WHEEL_SPEED_PWM 255

#if !defined(ARDUINO_ARCH_ESP32)
// void analogWrite(int pin, int val){}

const int EN_L = 13;
const int IN1_L = 12;
const int IN2_L = 11;
const int IN1_R = 10;
const int IN2_R = 9;
const int EN_R = 8;

const int PROXIMITY_SENSOR_COMMON = 3;
const int PROXIMITY_SENSOR_LEFT_PIN = 4;
const int PROXIMITY_SENSOR_CENTER_PIN = 5;
const int PROXIMITY_SENSOR_RIGHT_PIN = 6;
const int OBSTACLE_DISTANCE_TOLERANCE = 25;

//  const int EN_L  = 22;
// const int IN1_L =  24;
// const int IN2_L =  26;
// const int IN1_R =  28;
// const int IN2_R =  30;
// const int EN_R  = 32;
#endif

// Message Path strings
const String MSG_PATH_DIRECTION("/dir");
const String MESSAGE_PATH_DIRECTION("/direction");

const String MSG_PATH_SPEED("/spd");
const String MESSAGE_PATH_SPEED("/speed");

const String MSG_PATH_CUT_HEIGHT("/hgt");
const String MESSAGE_PATH_CUT_HEIGHT("/height");

const String MSG_PATH_BLADE_POWER("/hgt");
const String MESSAGE_PATH_BLADE_POWER("/height");


// Command  value strings
const String COMMAND_FORWARD("F");
const String COMMAND_BACKWARD("B");
const String COMMAND_RIGHT("R");
const String COMMAND_LEFT("L");
const String COMMAND_STOP("S");
const String COMMAND_SPEED_UP("+");
const String COMMAND_SLOW_DOWN("-");
const String COMMAND_SPINDLE("T");
const String COMMAND_SPEED_HIGH("H");
const String COMMAND_SPEED_LOW("L");

const String COMMAND_CUT_HEIGHT_HIGH("H");
const String COMMAND_CUT_HEIGHT_MEDIUM("M");
const String COMMAND_CUT_HEIGHT_LOW("L");
const String COMMAND_CUT_HEIGHT_CHARGE("C");

const String COMMAND_BLADE_POWER_STATE_ON("1");
const String COMMAND_BLADE_POWER_STATE_OFF("0");


const String DB_BASE_PATH = "YtTfN91AUQNrgutI1dZ2JRwmKwq2";


const int CUT_HEIGHT_HIGH = 0;
const int CUT_HEIGHT_MEDIUM = 40;
const int CUT_HEIGHT_LOW = 80;
const int CUT_HEIGHT_CHARGE = 45;

#endif