#ifndef __MYKEYBOARD_H__
#define __MYKEYBOARD_H__

#include <Keypad.h>
#include "mynvs.h"
#include "mqtt.h"
#include "gui.h"
#include "finger.h"

class KEYBOARD
{
    private:

    public:
    void keyboard();
    void keyboard_handle();
    void keyboard_matc();
};

extern String passwd_input;
extern String passwd_buff;
extern bool keyboard_falg;
extern String passwd;
extern int passwd_len;
extern MYGUI gui;


#endif