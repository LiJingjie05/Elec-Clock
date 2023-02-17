/**
 * 函数名：gui.h
 * 功能：屏幕显示头文件
 **/
#ifndef _GUI_H_
#define _GUI_H_

#include <Arduino.h>
#include <lvgl.h>
#include <display.h>

class MYGUI
{
    private:

    public:
        void label(const char * text);
        void gui_inti();
};

extern TFT_eSPI tft;
#endif