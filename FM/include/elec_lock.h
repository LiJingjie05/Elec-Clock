/**
 *电磁锁函数头文件
 */
#ifndef __ELEC_LOCK_H__
#define __ELEC_LOCK_H__

//#define sw 34

#include <Arduino.h>
#include "gui.h"
class LOCK
{
    private:

    public:
    void eleclock_init();
    void eleclock();
};

extern bool lock_flag;
extern bool cont_flag;
extern unsigned long open_time;
extern unsigned long time_flag;
extern lv_obj_t * label1;
extern MYGUI gui;

#endif