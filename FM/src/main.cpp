/**
 * 名称：基于esp32的多功能门锁设计
 * 功能：实现一个可以使用多种验证方式的门锁系统
 **/
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <FreeRTOS.h>
#include "mqtt.h"
#include "elec_lock.h"
#include "mywifi.h"
#include "mykeyboard.h"
#include "mynvs.h"
#include <TFT_eSPI.h>
#include "display.h"
#include "gui.h"
#include "finger.h"
#include "rfid.h"
#include "hcsr.h"

extern lv_obj_t * label1;

bool keyboard_falg = false;
String passwd = ""; 
int passwd_len = 0;
String passwd_buff = "";

bool finger_flag = false;

bool lock_flag = false;
bool cont_flag = false;
unsigned long open_time;
unsigned long time_flag = 5000;

bool mqtt_flag = false;
bool pub_flag = false;

const char* Mqtt_sub_topic; 
const char* Mqtt_pub_topic;

bool rfid_flag = false;

unsigned long time_lock;

MYWIFI mywifi;
MQTT mqtt;
LOCK lock;
MEMORY mymemory;
KEYBOARD keyboard;
MYGUI gui;
Display screen;
MYFINGER myfinger;
RFID rfid;
HCSR hcsr;

void taskOne(void *parameter)
{
  for(;;)
  {
    screen.routine();//LVGL管理
    //mqtt.mqtt_loop();//心跳
    delay(5);
  }
}

void setup() 
{
  Serial.begin(115200);
  SPI.begin();
  xTaskCreate(
  taskOne,   /* Task function. */
  "TaskOne", /* String with name of task. */
  1024*3,     /* Stack size in bytes. */
  NULL,      /* Parameter passed as input of the task */
  1,         /* Priority of the task. */
  NULL);
  screen.init();
  gui.gui_inti();
  mywifi.wifi_init();
  Mqtt_sub_topic = "lock/#";
  mqtt.mqtt_init();
  Serial.println("mqtt.mqtt_init();");
  Serial.println(" gui.gui_inti();");
  myfinger.init();
  lock.eleclock_init();
  rfid.init();
  mymemory.init();
  Serial.println("初始化完成！");
  gui.label("你好，世界！");
  time_lock = millis();
  delay(5000);
  gui.label("本产品支持密码解锁，指纹解锁，RFID解锁，远程解锁");
}

void myloop()
{
  if(mqtt_flag == true&&(unsigned long)(millis()-time_lock)>(unsigned long)(5000))
  {
    pub_flag = true;
    cont_flag = true;
    Mqtt_pub_topic = "lock/get";
    mqtt_flag = false;
    Serial.println("开门");
    gui.label("远程解锁成功");
    delay(200);
    String json = "{\"lockstate\":\"the door is open\"}";
    mqtt.pubTopic(Mqtt_pub_topic,json.c_str());
    time_lock = millis();
  }
  
  keyboard.keyboard();//按键检测函数
  if((unsigned long)(millis()-time_lock)>(unsigned long)(5000))//门锁打开后禁用输入设备
  {
    keyboard.keyboard_handle();//密码匹配
  }
   //指纹匹配成功后，将keyboard_falg置为true。
  if(keyboard_falg==true&&(unsigned long)(millis()-time_lock)>(unsigned long)(5000))
  {
    pub_flag = true;//发布主题标志位
    cont_flag = true;//控制门锁开门标志位
    Mqtt_pub_topic = "lock/get";//发布的MQTT主题名称
    keyboard_falg = false;//重置密码匹配成功标志位
    gui.label("密码解锁成功");//打印信息到屏幕
    String json = "{\"lockstate\":\"the door is open\"}";//向主题发布的信息
    mqtt.pubTopic(Mqtt_pub_topic,json.c_str());//主题发布函数
    time_lock = millis();//获取单片机系统内部时间，起计时作用
  }
  if((unsigned long)(millis()-time_lock)>(unsigned long)(5000))//让指纹不能连续触发
  {
    myfinger.matc_finger();//指纹匹配
  }
  //指纹匹配成功后，将finger_flag置为true。
  if(finger_flag == true&&(unsigned long)(millis()-time_lock)>(unsigned long)(5000))
  {
    finger_flag = false;//将finger_flag置为true。
    pub_flag = true;//将pub_flag置为true,用于给上位机发布开关门信息
    cont_flag = true;//将cont_flag置为true,开锁信号
    Mqtt_pub_topic = "lock/get";//MQTT发布的主题名称
    gui.label("指纹解锁成功");//打印信息到屏幕上
    String json = "{\"lockstate\":\"the door is open\"}";//要发布给主题的信息
    mqtt.pubTopic(Mqtt_pub_topic,json.c_str());//主题发布函数
    time_lock = millis();//获取单片机系统时间
  }
  if((unsigned long)(millis()-time_lock)>(unsigned long)(5000))//让RFID不能连续触发
  {
    rfid.matcID();//RFID匹配
  }
  if(rfid_flag == true&&(unsigned long)(millis()-time_lock)>(unsigned long)(5000))
  {
    rfid_flag = false;//将rfid_flag置为true。
    pub_flag = true;//将pub_flag置为true,用于给上位机发布开关门信息
    cont_flag = true;//将cont_flag置为true,开锁信号
    Mqtt_pub_topic = "lock/get";//MQTT发布的主题名称
    gui.label("RFID解锁成功");//打印信息到屏幕上
    String json = "{\"lockstate\":\"the door is open\"}";//要发布给主题的信息
    mqtt.pubTopic(Mqtt_pub_topic,json.c_str());//主题发布函数
    time_lock = millis();//获取单片机系统时间
  }
  if(lock_flag==false&&pub_flag == true&&cont_flag==false)
  {
    pub_flag = false;
    Mqtt_pub_topic = "lock/get";
    String json = "{\"lockstate\":\"the door is close\"}";
    mqtt.pubTopic(Mqtt_pub_topic,json.c_str());
  }

  lock.eleclock();
  Serial.println("*");
  delay(50);
}

void loop() 
{
  int i = hcsr.hcsrmain();
  if(i>=1)
  {
    unsigned long time_main = millis();
    while(millis()-time_main<60000)
    {
      mqtt.mqtt_loop();//MQTT心跳
      myloop();
    }
  }
   mqtt.mqtt_loop();//MQTT心跳
}