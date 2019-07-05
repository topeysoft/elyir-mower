#ifndef ELYIR_HA_SERVO_H
#define ELYIR_HA_SERVO_H

#include <Servo.h>

class HeightAdjuster
{
public:
    void setup(
        int PIN,
        int H_LOW,
        int H_MEDIUM,
        int H_HIGH,
        int H_CHARGE)
    {
        _haServo.attach(PIN);
        _PIN = PIN,
        _H_LOW = H_LOW,
        _H_MEDIUM = H_MEDIUM,
        _H_HIGH = H_HIGH,
        _H_CHARGE = H_CHARGE;
    }
    void setLowCut()
    {
        setHeight(_H_LOW);
    }
    void setMediumCut()
    {
        setHeight(_H_MEDIUM);
    }
    void setHighCut()
    {
        setHeight(_H_HIGH);
    }
    void setChargeHeight()
    {
        setHeight(_H_CHARGE);
    }

private:
    Servo _haServo;
    int _PIN;
        int _H_LOW;
        int _H_MEDIUM;
        int _H_HIGH;
        int _H_CHARGE;
        void setHeight(int height)
    {
        _haServo.write(height);
    }
};

#endif