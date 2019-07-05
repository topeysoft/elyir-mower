#ifndef ELYIR_ESP32_COMM_H
#define ELYIR_ESP32_COMM_H

#include "ElyirConfig.h"
// #include "ElyirLogger.h"
#include "SoftwareSerial.h"
#include "ElyirCommCommon.h"
// #include <HardwareSerial.h>
// #include "BluetoothSerial.h"
// HardwareSerial espPort(1);
SoftwareSerial espPort(ESP_RX_PIN, ESP_TX_PIN, false, 256);
// SoftwareSerial espPort(ESP_RX_PIN, ESP_TX_PIN);
template <typename T>
void log(T str)
{
    Serial.print(str);
}
template <typename T>
void logln(T str)
{
    Serial.println(str);
}
class Esp32Comm
{
public:
    bool showLog = true;
    // byte getDataFromMega()
    // {
    //     return _dataFromMega;
    // }
    // bool megaDataAvailable()
    // {
    //     return _megaAvailable;
    // }
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
    void setup()
    {
        // espPort.begin(espBaud, SERIAL_8N1, ESP_RX_PIN, ESP_TX_PIN);
        logln("Setting up ESP communication");
        espPort.begin(ESP_BAUD);
        // ESP_BT.begin("Elyir Lawn Mower");
    }

    void run()
    {
        // listenToBluetooth();
        listenToMega();
    }

    void listenToBluetooth()
    {
        // if (ESP_BT.available() > 0)
        // {
        //     // byte incomingByte = ESP_BT.read();
        //     // log("ESP32 received from BT: ");
        //     // logln(incomingByte);
        //     // processBTCommand(incomingByte);
        // }
    }
    void listenToMega()
    {
        int a = espPort.available();
        if (a > 0)
        {
            char[a];
            char[] _dataFromMega = espPort.readStringUntil('\n');
            log("ESP32 received from Mega: ");
            logln(_dataFromMega);
            if (_updateDataChangeCb)
            {
                // _updateDataChangeCb(_dataFromMega);
            }
            //         _dataFromMega = ""; // Clear recieved
        }
        // String _dataFromMega = "";
        // while (espPort.available() > 0)
        // {
        //     // _megaAvailable = true;
        //     char recieved = espPort.read();
        //         log("ESP32 received char: ");
        //         logln(recieved);
        //     if (recieved == '\n')
        //     {
        //         log("ESP32 received from Mega: ");
        //         logln(_dataFromMega);
        //         if (_updateDataChangeCb)
        //         {
        //             // _updateDataChangeCb(_dataFromMega);
        //         }
        //         _dataFromMega = ""; // Clear recieved buffer
        //     }
        //     else
        //     {
        //         _dataFromMega += recieved;
        //     }
        // }
        // else
        // {
        //     _megaAvailable = false;
        // }
    }
    template <typename T>
    void sendToMega(T command)
    {
        String str = String(command);
        // byte data[str.length()];
        // str.getBytes(data, str.length());
        espPort.write(str.c_str());
    }

    void setDataUpdateCallback(ChangeCallback *cb)
    {
        _updateDataChangeCb = cb;
    }

private:
    // BluetoothSerial ESP_BT;
    int dir = 0;
    bool _megaAvailable = false;
    ChangeCallback *_updateDataChangeCb;
};

#endif