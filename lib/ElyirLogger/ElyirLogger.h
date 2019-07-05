#ifndef ELYIR_LOGGER_H
#define ELYIR_LOGGER_H

        const int LOG_LEVEL_NONE = 0;
        const int LOG_LEVEL_LOG = 1;
        const int LOG_LEVEL_INFO= 2;
        const int LOG_LEVEL_ERROR = 3;
        const int LOG_LEVEL_VERIFIED = 4;
        const int LOG_LEVEL_ALL = 5;
#include <Ansiterm.h>

class ElyirLogger{
    public:
    void setup(int baud_rate, int level = 0) {
        _level = level;
        Serial.begin(baud_rate);
    }
    template <typename T>
    void error(T str, bool newLine = false)
    {
        if (_level == LOG_LEVEL_ERROR || _level == LOG_LEVEL_ALL)
        {
            // _ansi.setBackgroundColor(BLUE);//works
            _ansi.setForegroundColor(RED);
            Serial.print("ERROR: ");
            Serial.print(str);
            if(newLine){
                Serial.print("\n");
            }
        }
    }
    template <typename T>
    void errorLn(T str)
    {
        error(str, true);
    }
    template <typename T>
    void info(T str, bool newLine = false)
    {
        if (_level == LOG_LEVEL_INFO || _level == LOG_LEVEL_ALL)
        {
            _ansi.setForegroundColor(CYAN);
            Serial.print("INFO: ");
            Serial.print(str);
            if(newLine){
                Serial.print("\n");
            }
        }
    }
    template <typename T>
    void infoLn(T str)
    {
        info(str, true);
    }
    template <typename T>
    void verified(T str,  bool newLine = false)
    {
        if (_level == LOG_LEVEL_VERIFIED || _level == LOG_LEVEL_ALL)
        {
            _ansi.setForegroundColor(GREEN);
            Serial.print("VERIFIED: ");
            Serial.print(str);
            if(newLine){
                Serial.print("\n");
            }
        }
    }
    template <typename T>
    void verifiedLn(T str)
    {
        verified(str, true);
    }
    template <typename T>
    void log(T str, bool newLine = false)
    {
        if (_level == LOG_LEVEL_INFO || _level == LOG_LEVEL_ALL)
        {
            Serial.print("LOG: ");
            Serial.print(str);
            if(newLine){
                Serial.print("\n");
            }
        }
    }
    template <typename T>
    void logLn(T str)
    {
        log(str, true);
    }
    private:
      int _level = 0;
      Ansiterm _ansi;

};
#endif
