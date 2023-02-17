#ifndef _MYNVS_H_
#define _MYNVS_H_

#include <Preferences.h>
class MEMORY
{
    private:

    public:
    void init();
    void write_NVS(const char*  name,String root_passwd);
    void read_NVS(const char*  name);
};

extern String passwd_input;
extern String passwd_buff;

#endif