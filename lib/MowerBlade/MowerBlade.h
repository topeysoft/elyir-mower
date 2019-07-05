#ifndef ELYIR_CUT_BLADE_H
#define ELYIR_CUT_BLADE_H

#include <Arduino.h>

class MowerBlade
{
public:
    void setup(
        int PIN)
    {
        _PIN = PIN,
        pinMode(_PIN, OUTPUT);
    }
    void turnOn()
    {
        digitalWrite(_PIN, HIGH);
    }
    void turnOff()
    {
        digitalWrite(_PIN, LOW);
    }

private:
    int _PIN;
};

#endif