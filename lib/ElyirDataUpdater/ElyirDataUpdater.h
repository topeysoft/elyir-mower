#ifndef ELYIR_POST_UPDATER_H
#define ELYIR_POST_UPDATER_H

#include "MegaComm.h"

typedef struct DataUpdate {
    String ref;
    String data;
} DataUpdate_t;

class ElyirDataUpdater
{
public:
    void setup(MegaComm *comm){
        _megaComm = comm;
    }
    void queueUpdate(DataUpdate_t update)
    {
        _update = update;
    }

    void run()
    {
        unsigned long currentMillis = millis();

        if (currentMillis - _prevMillis >= DATA_UPDATE_INTERVAL)
        {
            _prevMillis = currentMillis;
            _megaComm->sendDataUpdate(_update.ref, _update.data);
        }
    }

private:
    int _prevMillis = millis();
    DataUpdate_t _update;
    MegaComm *_megaComm;
};
#endif