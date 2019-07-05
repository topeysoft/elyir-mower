#ifndef ELYIR_PROXIMITY_SENSOR_H
#define ELYIR_PROXIMITY_SENSOR_H

#include <Arduino.h>
#include <HCSR04.h>

typedef void ProxChangeCallback(bool left, bool center, bool right);
enum
{
    LEFT_INDEX = 0,
    CENTER_INDEX,
    RIGHT_INDEX
};

class ProximitySensor
{
public:
    void setup(int echoPinLeft, int echoPinCenter, int echoPinRight, int trigPin, int obstructionToleranceDistance = 10)
    {
        hc.setup(trigPin, new int[3]{echoPinLeft, echoPinCenter, echoPinRight}, 3);
        _obstructionToleranceDistance = obstructionToleranceDistance;
        // _PIN = PIN;
        // pinMode(_PIN, INPUT);
    }
    // void setup(int PIN, ProxChangeCallback *onBlockedCallback)
    // {
    //     _onBlockedCB = onBlockedCallback;
    //     setup(PIN);
    // }
    // void setup(int PIN, ProxChangeCallback *onBlockedCallback, ProxChangeCallback *onUnBlockedCallback)
    // {
    //     _onBlockedCB = onBlockedCallback;
    //     _onUnBlockedCB = onUnBlockedCallback;
    //     setup(PIN);
    // }

    int left_distance()
    {
        return _getDistance(LEFT_INDEX);
    }
    int center_distance()
    {
        return _getDistance(CENTER_INDEX);
    }
    int right_distance()
    {
        return _getDistance(RIGHT_INDEX);
    }
    bool left_obstructed()
    {
        return _left_obstructed;
    }
    bool center_obstructed()
    {
        return _center_obstructed;
    }
    bool right_obstructed()
    {
        return _right_obstructed;
    }
    bool obstructed()
    {
        return _left_obstructed || _center_obstructed || _right_obstructed;
    }
    void setOnBlockedCallback(ProxChangeCallback *cb)
    {
        _onBlockedCB = cb;
    }
    void setOnUnBlockedCallback(ProxChangeCallback *cb)
    {
        _onUnBlockedCB = cb;
    }
    void run()
    {
        bool justObstructed = false;
        bool justUnObstructed = false;
        if (left_distance() <= _obstructionToleranceDistance)
        {
            if(!_left_obstructed) justObstructed = true;
            _left_obstructed = true;
            // if (_onBlockedCB)
            //     _onBlockedCB();
        }else {
            if(_left_obstructed) justUnObstructed = true;
            _left_obstructed = false;
        }

        if (center_distance() <= _obstructionToleranceDistance)
        {
            if(!_center_obstructed) justObstructed = true;
            _center_obstructed = true;
            // if (_onBlockedCB)
            //     _onBlockedCB();
        }else {
            if(_center_obstructed) justUnObstructed = true;
            _center_obstructed = false;
        }

        if (right_distance() <= _obstructionToleranceDistance)
        {
            if(!_right_obstructed) justObstructed = true;
            _right_obstructed = true;
            // if (_onBlockedCB)
            //     _onBlockedCB();
        } else {
            if(_right_obstructed) justUnObstructed = true;
            _right_obstructed = false;
        }

        if (justObstructed)
        {
            if (_onBlockedCB)
            {
                _onBlockedCB(_left_obstructed, _center_obstructed, _right_obstructed);
            }
        }
        if (justUnObstructed)
        {
            if (_onUnBlockedCB)
            {
                _onUnBlockedCB(_left_obstructed, _center_obstructed, _right_obstructed);
            }
        }

        // _obstructed = false;
    }

private:
    int _PIN;
    HCSR04 hc;
    bool _left_obstructed = false;
    bool _center_obstructed = false;
    bool _right_obstructed = false;
    ProxChangeCallback *_onBlockedCB;
    ProxChangeCallback *_onUnBlockedCB;
    int _obstructionToleranceDistance = 10;
    int _getDistance(int index)
    {
        return hc.dist(index);
    }
};

#endif