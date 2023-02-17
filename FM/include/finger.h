/**
 *指纹传感器头文件
 */
#ifndef __FINGER_H__
#define __FINGER_H__
#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include "mykeyboard.h"

#define mySerial Serial1

class MYFINGER
{
    private:

    public:
    void init();
    void add_finger();
    void matc_finger();
    void del_finger();
    
};

uint8_t getFingerprintEnroll();
uint8_t readnumber(void);
int getFingerprintIDez();
uint8_t getFingerprintID();
void jianche();
//uint8_t readnumber(void);
uint8_t deleteFingerprint(uint8_t id);

extern Adafruit_Fingerprint finger;
extern bool finger_flag;
extern Keypad myKeypad;
#endif