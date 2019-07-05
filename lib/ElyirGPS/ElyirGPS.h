#ifndef ELYIR_GPS_H
#define ELYIR_GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>
// #include <ElyirConfig.h>

class ElyirGPS
{
public:
  void run()
  {

    setPersistentVariables();
    // _printAllData();
  

    // if (millis() > 5000 && _gps.charsProcessed() < 10)
    //   Serial.println(F("No GPS data received: check wiring"));

  } // GPSloop

  //--------------------------

  void setup()
  {
    // DEBUG_PORT.begin(9600);
    Serial2.begin(38400);
  }

  double speedMPS()
  {
    return _speedMPS;
  }
  double speedMPH()
  {
    return _speedMPH;
  }
  double speedKMPH()
  {
    return _speedKMPH;
  }
  double lat()
  {
    return _lat;
  }
  double lng()
  {
    return _lng;
  }

  char *cardinal()
  {
    return _gps.course.isValid() ? TinyGPSPlus::cardinal(_gps.course.deg()) : "*** ";
  }
  TinyGPSCourse course()
  {
    return _gps.course;
  }
  TinyGPSSpeed speed()
  {
    return _gps.speed;
  }
  TinyGPSLocation location()
  {
    return _gps.location;
  }

private:
  TinyGPSPlus _gps;
  double _speedMPS = 0;
  double _speedMPH = 0;
  double _speedKMPH = 0;
  double _lat = 0;
  double _lng = 0;
  void _smartDelay(unsigned long ms)
  {
    unsigned long start = millis();
    do
    {
      while (Serial2.available()){
        _gps.encode(Serial2.read());
        //  Serial.println(F("here"));
      }
    } while (millis() - start < ms);
  }

  void setPersistentVariables(){
    _smartDelay(0);
    if(_gps.speed.isValid()){

      // Serial.print("SPEED IS VALID\n ---------------------\n ");
      // Serial.print("MPS: ");
      // Serial.print(_speedMPS);
      // Serial.print("\nMPH: ");
      // Serial.print(_speedMPH);
      // Serial.print("\nKMPH: ");
      // Serial.print(_speedKMPH);
       _speedMPS = _gps.speed.mps();
       _speedMPH = _gps.speed.mph();
       _speedKMPH = _gps.speed.kmph();
    }
    if(location().isValid()){
       _lat = location().lat();
       _lng = location().lng();
    }
  }

   void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  _smartDelay(0);
}

 void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  _smartDelay(0);
}

 void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  _smartDelay(0);
}

 void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  _smartDelay(0);
}

void _printAllData (){
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

  printInt(_gps.satellites.value(), _gps.satellites.isValid(), 5);
  printFloat(_gps.hdop.hdop(), _gps.hdop.isValid(), 6, 1);
  printFloat(_gps.location.lat(), _gps.location.isValid(), 11, 6);
  printFloat(_gps.location.lng(), _gps.location.isValid(), 12, 6);
  printInt(_gps.location.age(), _gps.location.isValid(), 5);
  printDateTime(_gps.date, _gps.time);
  printFloat(_gps.altitude.meters(), _gps.altitude.isValid(), 7, 2);
  printFloat(_gps.course.deg(), _gps.course.isValid(), 7, 2);
  printFloat(_gps.speed.kmph(), _gps.speed.isValid(), 6, 2);
  printStr(_gps.course.isValid() ? TinyGPSPlus::cardinal(_gps.course.deg()) : "*** ", 6);

  unsigned long distanceKmToLondon =
    (unsigned long)TinyGPSPlus::distanceBetween(
      _gps.location.lat(),
      _gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON) / 1000;
  printInt(distanceKmToLondon, _gps.location.isValid(), 9);

  double courseToLondon =
    TinyGPSPlus::courseTo(
      _gps.location.lat(),
      _gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON);

  printFloat(courseToLondon, _gps.location.isValid(), 7, 2);

  const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

  printStr(_gps.location.isValid() ? cardinalToLondon : "*** ", 6);

  printInt(_gps.charsProcessed(), true, 6);
  printInt(_gps.sentencesWithFix(), true, 10);
  printInt(_gps.failedChecksum(), true, 9);
  Serial.println();
}
};
#endif