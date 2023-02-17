/**
 *用于开启显示的头文件  
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <lvgl.h>
#include <TFT_eSPI.h>


class Display
{
    private:


    public:
        void init();
        void routine();
        //void setBackLight(float);

};


#endif