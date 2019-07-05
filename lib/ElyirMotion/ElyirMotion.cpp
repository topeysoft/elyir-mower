

#include <ElyirCompass.h>
#include <math.h>
#include "ElyirMotion.h"

const float COURSE_TOLERANGE = 12;
const int COURSE_DELAY = 1;
const int WAIT_BEFORE_OBSTACLE = 2000;
const int OBSTACLE_STOP_DELAY = 500;
const int OBSTACLE_REVERSE_DELAY = 1000;
const int OBSTACLE_TURN_DELAY = 3000;
const int OBSTACLE_FORWARD_DELAY = 2000;
const int TOTAL_OBSTACLE_DELAY = OBSTACLE_STOP_DELAY + OBSTACLE_REVERSE_DELAY + OBSTACLE_TURN_DELAY + OBSTACLE_FORWARD_DELAY;
// const int HEADING_UPDATE_DELAY = 1000;

template <typename T>
T normalizeValue(T val, T minVal = 0, T maxVal = 360)
{
    T v = fmod(val, maxVal);
    if (v < minVal)
    {
        v += maxVal;
    }
    return v;
}

ElyirMotion::ElyirMotion() {}

void ElyirMotion::setup(int IN1_L, int IN2_L, int EN_L, int IN1_R, int IN2_R, int EN_R, int maxSpeedPwm)
{
    _left.setup(IN1_L, IN2_L, EN_L);
    _right.setup(IN1_R, IN2_R, EN_R);
    setMaxSpeedPWM(maxSpeedPwm);
}
void ElyirMotion::_updateHeading()
{
    _current_heading = compass.getHeading();
}
void ElyirMotion::setMaxSpeedPWM(int pwm)
{
    _left.setMaxSpeedPWM(pwm);
    _right.setMaxSpeedPWM(pwm);
}

/**
     * Continuosly move forward until another command is issued
     */
void ElyirMotion::goForward()
{
    _direction = MOVING_FORWARD;
}
/**
     * Continuosly move backward until another command is issued
     */
void ElyirMotion::goBackward()
{
    _direction = MOVING_BACKWARD;
}
/**
     * Stop until another command is issued
     */
void ElyirMotion::stop()
{
    _direction = STOPPED;
}
/**
     * Continuosly move in current direction in full speed
     */
void ElyirMotion::goFullSpeed()
{
    _left.fullSpeed();
    _right.fullSpeed();
}
/**
     * Continuosly move in current direction in half speed
     */
void ElyirMotion::goHalfSpeed()
{
    _left.halfSpeed();
    _right.halfSpeed();
}
/**
     * Turn 90 degree left and stop
     */
void ElyirMotion::turnLeft()
{
    _direction = TURNING_LEFT;
    _target_heading = normalizeValue(_target_heading + 90.0);
}
/**
     * Turn 90 degree right and stop
     */
void ElyirMotion::turnRight()
{
    _direction = TURNING_RIGHT;
    _target_heading = normalizeValue(_target_heading - 90.0);
}
/**
     * Turn 180 degree left and stop
     */
void ElyirMotion::turnAroundLeft()
{
    _direction = TURNING_AROUND_LEFT;
    _target_heading = normalizeValue(_target_heading + 180.0);
}
/**
     * Turn 180 degree right and stop
     */
void ElyirMotion::turnAroundRight()
{
    _direction = TURNING_AROUND_RIGHT;
    _target_heading = normalizeValue(_target_heading - 180.0);
}
/**
     * Must be called in side loop to keep things going (for example to maintain course)
     */
void ElyirMotion::run()
{
    _checkCourseInterval();
    _current_heading = compass.getHeading();
    _checkForObstacles();
    _avoidObstacle();
}
void ElyirMotion::_avoidObstacle()
{

    if (_direction == AVOIDING_OBSTACLE)
    {
        unsigned long currentMillis = millis();
        if (_direction == AVOIDING_OBSTACLE)
            Serial.println("Direction is Avoiding obstacles: \n ------------");

        if ((currentMillis - _totalObstaclePreviousMillis < TOTAL_OBSTACLE_DELAY))
        {

            Serial.println("Avoid Obstacle Routine: \n ------------");

            if (currentMillis - _obstacleStopPreviousMillis < OBSTACLE_STOP_DELAY)
            {
                _left.stop();
                _right.stop();
                _obstacleReversePreviousMillis = millis();
                Serial.println("STOP Routine: ");
            }
            else if (currentMillis - _obstacleReversePreviousMillis < OBSTACLE_REVERSE_DELAY)
            {
                _left.reverse();
                _right.reverse();
                _obstacleTurnPreviousMillis = millis();
                Serial.println("REVERSE Routine: ");
            }
            else if (currentMillis - _obstacleTurnPreviousMillis < OBSTACLE_TURN_DELAY)
            {
                _obstacleForwardPreviousMillis = millis();
                if (_left_obstacle)
                {
                    _left.forward();
                    _right.stop();
                }
                else
                {
                    _left.stop();
                    _right.forward();
                }
                Serial.println("TURN Routine: ");
                Serial.println(!_left_obstacle?"LEFT":"RIGHT");
            }
            else if (currentMillis - _obstacleForwardPreviousMillis < OBSTACLE_FORWARD_DELAY)
            {
                _left.forward();
                _right.forward();
                Serial.println("FORWARD Routine: ");
            }
        }
        else
        {
            _clearedObstacles();
        }
    }
}

/**
     * Turn 180 degree right and stop
     */
void ElyirMotion::_maintainCourse()
{
    int offset = _getHeadingOffset();
    if (_direction == STOPPED)
    {
        _left.stop();
        _right.stop();
        _logger->log("Stopped. Offset: ");
        _logger->logLn(offset);
    }
    else if (_direction == MOVING_FORWARD)
    {
        _left.forward();
        _right.forward();
        _logger->log("Moving forward. Offset: ");
        _logger->logLn(offset);
    }
    else if (_direction == MOVING_BACKWARD)
    {
        _left.reverse();
        _right.reverse();
        _logger->log("Moving backward. Offset: ");
        _logger->logLn(offset);
    }

    if (_direction != AVOIDING_OBSTACLE)
    {
        if (offset < -COURSE_TOLERANGE && !_obstructed())
        { // turn left
            while (offset < -COURSE_TOLERANGE && !_obstructed())
            {
                offset = _getHeadingOffset();
                _left.stop();
                _right.forward();
                _logger->log("Turning left. Offset: ");
                _logger->logLn(offset);
            }
        }
        else if (offset > COURSE_TOLERANGE && !_obstructed())
        {
            while (offset > COURSE_TOLERANGE && !_obstructed())
            {
                offset = _getHeadingOffset();
                _left.forward();
                _right.stop();
                _logger->log("Turning right. Offset: ");
                _logger->logLn(offset);
            }
        }
        else
        {
            _direction = MOVING_FORWARD;
        }
    }
    // _logger->logLn("Maintaining course: ");
    // _logger->log("Current heading: ");
    // _logger->logLn(_current_heading);
    // _logger->log("Target heading: ");
    // _logger->logLn(_target_heading);
    // _logger->logLn("----------------------------");
}

// unsigned headingUpdatePreviousMillis = millis();
void ElyirMotion::_checkCourseInterval()
{
    unsigned long currentMillis = millis();

    if (currentMillis - _coursePreviousMillis >= COURSE_DELAY)
    {
        _coursePreviousMillis = currentMillis;
        _maintainCourse();
    }
}
// void checkCourseInterval() {
//     unsigned long currentMillis = millis();

//   if (currentMillis - headingUpdatePreviousMillis >=        HEADING_UPDATE_DELAY) {
//     // save the last time you blinked the LED
//     headingUpdatePreviousMillis = currentMillis;

//   }
// }
// _updateHeadingCB() {
//     ElyirMotion::_maintainCourse();
// }
// _maintainCourseCB() {}