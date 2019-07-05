
/**
 * How it works:
 *
 * LEFT MOTOR (A)
 * -------------------------------
 * EnA  |  IN1  |  IN2  | STATUS
 * -------------------------------
 * 255  |   1   |   0   | Forward
 * 255  |   0   |   1   | Reverse
 * 255  |   0   |   0   | Brake
 *  0   |   0   |   0   | Stop
 * -------------------------------
 * Half Speed
 * -------------------------------
 * 127  |   1   |   0   | Forward
 * 127  |   0   |   1   | Reverse
 * 127  |   0   |   0   | Brake
 *  0   |   0   |   0   | Stop
 * ------------------------------
 *
 *
 * RIGHT MOTOR (B)
 * -------------------------------
 * EnB  |  IN3  |  IN4  | STATUS
 * -------------------------------
 * 255  |   1   |   0   | Forward
 * 255  |   0   |   1   | Reverse
 * 255  |   0   |   0   | Brake
 *  0   |   0   |   0   | Stop
 * -------------------------------
 * Half Speed
 * -------------------------------
 * 127  |   1   |   0   | Forward
 * 127  |   0   |   1   | Reverse
 * 127  |   0   |   0   | Brake
 *  0   |   0   |   0   | Stop
 *
 */
#include "L298N.h"
#include "Arduino.h"

L298N::L298N()
{
    _speed = HALF_SPEED;
    _direction = STOP;
}
void L298N::setMaxSpeedPWM(int maxSpeed)
{
    MAX_SPEED = maxSpeed;
    FULL_SPEED = MAX_SPEED;
    HALF_SPEED = FULL_SPEED / 2;
}
void L298N::setup(int IN1, int IN2, int EN, int maxSpeedPWM)
{
    _IN1 = IN1;
    _IN2 = IN2;
    _EN = EN;
    pinMode(_IN1, OUTPUT);
    pinMode(_IN2, OUTPUT);
    pinMode(_EN, OUTPUT);
    setMaxSpeedPWM(maxSpeedPWM);
}

void L298N::forward()
{
    _direction = FORWARD;
    _run();
}
void L298N::reverse()
{
    _direction = REVERSE;
    _run();
}
void L298N::stop()
{
    _direction = STOP;
    _run();
}
void L298N::fullSpeed()
{
    _speed = FULL_SPEED;
    _run();
}
void L298N::halfSpeed()
{
    _speed = HALF_SPEED;
    _run();
}
void L298N::setSpeed(int speed = 100)
{
    _speed = (int)((speed / 100) * MAX_SPEED);
    _run();
}
int L298N::getSpeed()
{
    return (int)((_speed / MAX_SPEED) * 100);
}
int L298N::getDirection()
{
    return _direction;
}
void L298N::_run()
{
    // _is_running = true;
    switch (_direction)
    {
    case FORWARD:
        digitalWrite(_IN1, HIGH);
        digitalWrite(_IN2, LOW);
        analogWrite(_EN, _speed);
        break;
    case REVERSE:
        digitalWrite(_IN1, LOW);
        digitalWrite(_IN2, HIGH);
        analogWrite(_EN, _speed);
        break;
    case STOP:
        digitalWrite(_IN1, LOW);
        digitalWrite(_IN2, LOW);
        analogWrite(_EN, 0);
        break;
    }
}