#ifndef L298N_H
#define L298N_H

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

class L298N
{
public:
    L298N();
    void setup(int IN1, int IN2, int EN, int maxSpeedPWM = 255);
    void forward();
    void reverse();
    void stop();
    void fullSpeed();
    void halfSpeed();
    void setSpeed(int speed);
    int getSpeed();
    void setMaxSpeedPWM(int maxSpeed);
    int getDirection();
    typedef enum
    {
        FORWARD = 0,
        REVERSE = 1,
        STOP = 2,
    } Direction;


private:
    int _speed;
    int _direction = FORWARD;
    int _IN1;
    int _IN2;
    int _EN;
    bool _is_running = false;
    int MAX_SPEED = 255;
    int FULL_SPEED;
    int HALF_SPEED;
    void _run();
};

#endif