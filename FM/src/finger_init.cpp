/**
 * 函数名：finger_init
 * 功能：实现指纹传感器与主控进行通信
 **/
#include "finger.h"

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//指纹传感器初始化
void MYFINGER::init()
{
    finger.begin(57600);
    if (finger.verifyPassword()) 
    {
        Serial.println("Found fingerprint sensor!");
        Serial.println("指纹传感器连接成功!");
    } 
    else 
    {
        Serial.println("Did not find fingerprint sensor :(");
        Serial.println("指纹传感器连接失败!");
        while (1) 
        { 
            delay(2000);
            break; 
        }
    }
}