/**
 * 函数名：elec_lock
 * 功能：实现门锁的开关
 **/
#include "elec_lock.h"

int sw = 5;

void LOCK::eleclock_init()
{
    pinMode(sw,OUTPUT);
    digitalWrite(sw,LOW);
}

void LOCK::eleclock()
{
    if(lock_flag == false&&cont_flag == true)
    {
        lock_flag = true;
        cont_flag = false;
        digitalWrite(sw,HIGH);
        open_time = millis();
        Serial.println("开门成功！");
    }
    if(lock_flag == true&&millis()-open_time > time_flag)
    {
        lock_flag = false;
        Serial.println("回锁！");
        gui.label("门锁已关闭");
        digitalWrite(sw,LOW);
        delay(3000);
        gui.label("本产品支持密码解锁，指纹解锁，RFID解锁，远程解锁");
    }
    
}