#ifndef __RFID_H__
#define __RFID_H__

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
//#include "gui.h"

#define RST_PIN         22          // Configurable, see typical pin layout above
#define SS_PIN          21         // Configurable, see typical pin layout above

class RFID
{
    private:

    public:
    void matcID();
    void init();
};

extern bool rfid_flag;

#endif