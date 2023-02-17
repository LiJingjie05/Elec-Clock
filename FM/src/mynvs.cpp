#include "mynvs.h"

void MEMORY::init()
{
    Preferences prefs;
    MEMORY i;
    if(prefs.getString("root_passwd","505").c_str()=="505")
    i.write_NVS("root_passwd","888888");
    if(prefs.getString("user_passwd","505").c_str()=="505")
    i.write_NVS("root_passwd","012345");

}
void MEMORY::write_NVS(const char*  name,String root_passwd)
{
    Preferences prefs;
    prefs.begin("lock",false); // 打开命名空间mynamespace
    
    //root_passwd; // 累加计数
    prefs.putString(name, root_passwd); // 将数据保存到当前命名空间的"count"键中
                                                // 如果没有该元素则返回默认值0
    Serial.println();
    Serial.print("剩余空间为：");
    Serial.println(prefs.freeEntries());//获取空余nvs空间
    prefs.end(); // 关闭当前命名空间
}

void MEMORY::read_NVS(const char*  name)
{
    Preferences prefs;
    prefs.begin("lock",true);
    Serial.printf(prefs.getString(name,"505").c_str());
    passwd_buff = prefs.getString(name,"505").c_str();
    Serial.println();
    Serial.print("剩余空间为：");
    Serial.println(prefs.freeEntries());//获取空余nvs空间
    prefs.end(); // 关闭当前命名空间
}
