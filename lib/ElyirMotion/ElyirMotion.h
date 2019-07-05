#ifndef ELYIR_MOTION_H
#define ELYIR_MOTION_H

#include <Arduino.h>
#include "ElyirGPS.h"
#include "ElyirCompass.h"
#include "ProximitySensor.h"
#include "ElyirLogger.h"
#include "L298N.h"

class ElyirMotion
{
public:
    ElyirMotion();
    bool showLog = true;
    void setup(int IN1_L, int IN2_L, int EN_L,
               int IN1_R, int IN2_R, int EN_R, int maxSpeedPWM = 255);

    void setMaxSpeedPWM(int maxSpeed);
    /**
     * Continuosly move forward until another command is issued
     */
    void goForward();
    /**
     * Continuosly move backward until another command is issued
     */
    void goBackward();
    /**
     * Stop until another command is issued
     */
    void stop();
    /**
     * Continuosly move in current direction in full speed
     */
    void goFullSpeed();
    /**
     * Continuosly move in current direction in half speed
     */
    void goHalfSpeed();
    /**
     * Turn 90 degree left and stop
     */
    void turnLeft();
    /**
     * Turn 90 degree right and stop
     */
    void turnRight();
    /**
     * Turn 180 degree left and stop
     */
    void turnAroundLeft();
    /**
     * Turn 180 degree right and stop
     */
    void turnAroundRight();

    int getCurrentHeading()
    {
        return _current_heading;
    }
    int getTargetHeading()
    {
        return _target_heading;
    }
    void clearedLeftObstacle()
    {
        _clearedObstacles();
    }
    void clearedCenterObstacle()
    {
        _clearedObstacles();
    }
    void clearedRightObstacle()
    {
        _clearedObstacles();
    }
    void setLogger(ElyirLogger *logger)
    {
        _logger = logger;
    }
    void setGps(ElyirGPS *gps)
    {
        _gps = gps;
    }
    void setSensors(ProximitySensor *s)
    {
        _sensors = s;
    }

    void approachingObstacle(bool left, bool center, bool right)
    {
        _left_obstacle = left;
        _center_obstacle = center;
        _right_obstacle = right;
        _beginObstacleAvoidance();
    }

    void run();
    typedef enum
    {
        MOVING_FORWARD = 0,
        MOVING_BACKWARD = 1,
        STOPPED = 2,
        TURNING_LEFT,
        TURNING_RIGHT,
        TURNING_AROUND_LEFT,
        TURNING_AROUND_RIGHT,
        AVOIDING_OBSTACLE
    } Direction;

private:
    L298N _left;
    L298N _right;
    ElyirCompass compass;
    ElyirGPS *_gps;
    ElyirLogger *_logger;
    ProximitySensor *_sensors;
    unsigned _coursePreviousMillis = millis();
    unsigned _waitBeforeObstaclePrevMillis = millis();
    unsigned _obstacleStopPreviousMillis = millis();
    unsigned _obstacleReversePreviousMillis = millis();
    unsigned _obstacleTurnPreviousMillis = millis();
    unsigned _obstacleForwardPreviousMillis = millis();
    unsigned _totalObstaclePreviousMillis = millis();

    bool _left_obstacle = false;
    bool _flagged_for_obstacle = false;
    bool _center_obstacle = false;
    bool _right_obstacle = false;
    void _foundLeftObstacle()
    {
        // _left_obstacle = true;
        _beginObstacleAvoidance();
    }
    void _foundCenterObstacle()
    {
        // _center_obstacle = true;
        _beginObstacleAvoidance();
    }
    void _foundRightObstacle()
    {
        // _right_obstacle = true;
        _beginObstacleAvoidance();
    }
    void _avoidObstacle();
    // void _avoidLeftObstacle();
    // void _avoidRightObstacle();
    // void _avoidCenterObstacle();
    void _checkForObstacles()
    {
        if (_sensors->obstructed() && _direction != AVOIDING_OBSTACLE)
        {
            _direction = MOVING_FORWARD;
           _left_obstacle = _sensors->left_obstructed();
        _center_obstacle = _sensors->center_obstructed();
        _right_obstacle = _sensors->right_obstructed();
        _beginObstacleAvoidance();
        //  approachingObstacle(_sensors->left_obstructed(), _sensors->center_obstructed(), _sensors->right_obstructed());
        }
    }
    bool _obstructed()
    {
        return _sensors->obstructed();
    }
    void _clearedObstacles()
    {
        // _left_obstacle = false;
        // _center_obstacle = false;
        // _right_obstacle = false;
        // _flagged_for_obstacle = false;
        
            _direction = MOVING_FORWARD;
            Serial.println("Obstacle CLEARED");
    }

    int _direction;
    float _target_heading;
    float _current_heading;
    void _checkCourseInterval();
    void _maintainCourse();
    void _beginObstacleAvoidance()
    {
        _totalObstaclePreviousMillis = millis();
        _obstacleStopPreviousMillis = millis();
        _obstacleReversePreviousMillis = millis();
        _obstacleTurnPreviousMillis = millis();
        _obstacleForwardPreviousMillis = millis();
        _direction = AVOIDING_OBSTACLE;
    }
    void _updateHeading();
    float _getHeadingOffset()
    {
        _updateHeading();
        const float R = 10; // arbitrary value for radius. it can be any positive value
        return 2 * PI * R * ((_current_heading - _target_heading) / 360);
    }
    // template <typename T>
    // void log(T str)
    // {
    //     if (showLog)
    //     {
    //         Serial.print(str);
    //     }
    // }
    // template <typename T>
    // void logln(T str)
    // {
    //     log(str);
    //     log("\n");
    // }
};

#endif
