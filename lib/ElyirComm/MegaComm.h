#ifndef ELYIR_MEGA_COMM_H
#define ELYIR_MEGA_COMM_H

#include <ArduinoJson.h>
#include "ElyirCommCommon.h"
#include "ElyirConfig.h"
#include "ElyirLogger.h"
#include <ElyirMotion.h>

class MegaComm
{
public:
    void setDirectionChangeCallback(ChangeCallback *cb)
    {
        _dirChangeCb = cb;
    }
    void setHeightChangeCallback(ChangeCallback *cb)
    {
        _heightChangeCb = cb;
    }
    void setSpeedChangeCallback(ChangeCallback *cb)
    {
        _spdChangeCb = cb;
    }
    void setBladeStateChangeCallback(ChangeCallback *cb)
    {
        _bladeChangeCb = cb;
    }
    void setup(ElyirLogger *logger)
    {   _logger = logger;
        _logger->logLn("Setting up ESP communication");
        megaPort->begin(megaBaud);
    }
    //  void setEventManager(EventManager &evManager){
    //      _evManager = evManager;
    //  }

    void run()
    {
        listenToEsp();
    }
    void listenToEsp()
    {
        if (megaPort->available() > 0)
        {
            String incoming = megaPort->readString();
            _logger->log("MEGA received from ESP32: ");
            _logger->logLn(incoming);
            processESPCommand(incoming);
        }
    }
    void sendDataUpdate(String ref, String data)
    {
        String update = "{\"ref\":\""+ref+"\", \"data\":"+data+"\"}\n";
        // byte buf;
        // byte buf[update.length() + 1];
        // message.getBytes(bytes, message.length() + 1);
        // update.getBytes(buf, update.length() + 1);
        _logger->log("Sending update to esp: ");
        _logger->logLn(update);
        megaPort->write("Mega TEST");
        // megaPort->write(update.c_str());
    }
    // void sendToEsp(byte command)
    // {
    //     megaPort.write(command);
    // }
    void processESPCommand(String incoming)
    {
        // _evManager.queueEvent( EV_BT_DATA_RECEIVED, incomingByte );
        // if (dir  != incomingByte)
        // {
        // const char* dir = incoming.c_str();
        DynamicJsonDocument doc(512);
        deserializeJson(doc, incoming);

        _logger->log("CHAR: ");
        _logger->log(incoming);
        _logger->log(" LEN: ");
        _logger->logLn(incoming.length());
        _logger->logLn("--------------");
        String path = doc["p"];
        if (path.equalsIgnoreCase(MSG_PATH_DIRECTION) || path.equalsIgnoreCase(MESSAGE_PATH_DIRECTION))
        {
            if(_dirChangeCb) _dirChangeCb(doc["v"]);
            
        }
        else if (path.equalsIgnoreCase(MSG_PATH_SPEED) || path.equalsIgnoreCase(MESSAGE_PATH_SPEED))
        {
           if(_spdChangeCb)  _spdChangeCb(doc["v"]);
        }
        else if (path.equalsIgnoreCase(MSG_PATH_CUT_HEIGHT) || path.equalsIgnoreCase(MESSAGE_PATH_CUT_HEIGHT))
        {
           if(_heightChangeCb)  _heightChangeCb(doc["v"]);
        }
        else if (path.equalsIgnoreCase(MSG_PATH_BLADE_POWER) || path.equalsIgnoreCase(MESSAGE_PATH_BLADE_POWER))
        {
           if(_bladeChangeCb)  _bladeChangeCb(doc["v"]);
        }
    }
    // setMotionInstance(ElyirMotion *m){
    //     motion = m
    // }
private:
    ChangeCallback *_bladePowerChangeCb;
    ChangeCallback *_spdChangeCb;
    ChangeCallback *_dirChangeCb;
    ChangeCallback *_heightChangeCb;
    ChangeCallback *_bladeChangeCb;
    ElyirLogger *_logger;
};

#endif