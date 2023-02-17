//IO32->#开始
#include "mykeyboard.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {25, 26, 32, 33}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {27, 14, 12, 13}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
MEMORY keymemory;
MQTT keymqtt;
extern MYFINGER myfinger;

void KEYBOARD::keyboard()
{
  char key = myKeypad.getKey();
  if(key != NO_KEY)
  {
    const char * text = "";
    passwd_len++;
    Serial.print(key);
    Serial.print(" ");
    passwd+=key;
    switch (passwd_len)
    {
    case 0:
      text = "";
      break;
    case 1:
      text = "*";
      break;
    case 2:
      text = "**";
      break;
    case 3:
      text = "***";
      break;
    case 4:
      text = "****";
      break;
    case 5:
      text = "*****";
      break;
    case 6:
      text = "******";
      break;
    default:
      break;
    }
    gui.label(text);
    text = "";
  }
}

void KEYBOARD::keyboard_handle()
{
  if(passwd == "#")
  {
    passwd = "";
    passwd_len = 0;
    Serial.println();
    Serial.println("请求远程开门！！！");
    //gui.label("管理员权限 输入1修改管理员密码 输入2修改用户密码 输入3设置RFID 输入4设置指纹 输入0退出");
    gui.label("请求远程开门中...");
    //发布MQTT主题以及信息
    keymqtt.pubTopic("lock/get","{\"lockstate\":\"Please open the door\"}");
  }
  if(passwd_len>=6)//接收到密码长度为6时开始运行
  {
    int j = 0;
    Serial.println();
    Serial.println(passwd);
    keymemory.read_NVS("root_passwd");
    if(passwd == passwd_buff)
    {
      j=1;
      passwd = "";
      passwd_len = 0;
      passwd_buff = "";
      // gui.label("正在进入管理员模式...");
      Serial.println("管理员权限 输入1修改管理员密码 输入2修改用户密码 输入3设置RFID 输入4设置指纹 输入0退出");
      gui.label("管理员权限 输入1修改管理员密码 输入2修改用户密码 输入3设置RFID 输入4设置指纹 输入0退出");
      int i;
      int fi = -1;
      KEYBOARD root_passwd;
      while(1)
      {
        i = (int)(myKeypad.getKey()-'0');
        switch(i)
        {
          case 1:
              i = -1;
              passwd = "";
              passwd_buff = "";
              passwd_len = 0;
              Serial.println("修改管理员密码：");
              gui.label("修改管理员密码中...");
              while(1)
              {
                  root_passwd.keyboard();//调用后修改全局变量passwd;
                  if(passwd_len>=6)
                  {
                    passwd_len = 0;
                    keymemory.write_NVS("root_passwd",passwd);
                    keymemory.read_NVS("root_passwd");
                    if(passwd == passwd_buff)
                    {
                      Serial.print("输入密码为：");
                      Serial.println(passwd);
                      Serial.print("修改管理员密码为：");
                      Serial.println(passwd_buff);
                      gui.label("修改管理员密码成功");
                      delay(3000);
                    }
                    passwd = "";
                    passwd_buff = "";
                    gui.label("管理员权限 输入1修改管理员密码 输入2修改用户密码 输入3设置RFID 输入4设置指纹 输入0退出");
                    break;
                  }
              }
          break;
          case 2:
              i = -1;
              passwd = "";
              passwd_buff = "";
              passwd_len = 0;
              Serial.println("修改用户密码：");
              gui.label("修改用户密码中...");
              while(1)
              {
                  root_passwd.keyboard();//调用后修改全局变量passwd;
                  if(passwd_len>=6)
                  {
                    passwd_len = 0;
                    keymemory.write_NVS("user_passwd",passwd);
                    keymemory.read_NVS("user_passwd");
                    if(passwd == passwd_buff)
                    {
                      Serial.print("输入密码为：");
                      Serial.println(passwd);
                      Serial.print("修改用户密码为：");
                      Serial.println(passwd_buff);
                      gui.label("修改用户密码成功");
                      delay(3000);
                    }
                    passwd = "";
                    passwd_buff = "";
                    gui.label("管理员权限 输入1修改管理员密码 输入2修改用户密码 输入3设置RFID 输入4设置指纹 输入0退出");
                    break;
                  }
              }
          break;
          case 3:
              //修改RFID
               i = -1;
          break;
          case 4:
              //修改指纹
              i = -1;
              passwd = "";
              passwd_buff = "";
              passwd_len = 0;
              Serial.println("输入1添加指纹 输入2删除指纹 输入0返回上一级");
              gui.label("输入1添加指纹 输入2删除指纹 输入0返回上一级");
              while(1)
              {
                fi = (int)(myKeypad.getKey()-'0');
                if(fi == 1)
                {
                  Serial.println("正在添加指纹...");
                  gui.label("正在进入添加指纹...");
                  fi = -1;
                  delay(2000);
                  myfinger.add_finger();
                  gui.label("输入1添加指纹 输入2删除指纹 输入0返回上一级");
                }
                if(fi == 2)
                {
                  Serial.println("正在删除指纹...");
                  gui.label("正在进入删除指纹...");
                  delay(2000);
                  fi = -1;
                  myfinger.del_finger();
                  gui.label("输入1添加指纹 输入2删除指纹 输入0返回上一级");
                }
                if(fi == 0)
                {
                  fi = -1;
                  Serial.println("退出指纹设置");
                  gui.label("正在退出指纹设置");
                  delay(2000);
                  Serial.println("正在返回上一级！");
                  gui.label("正在返回上一级！");
                  delay(2000);
                  break;
                }
              }
          gui.label("管理员权限 输入1修改管理员密码 输入2修改用户密码 输入3设置RFID 输入4设置指纹 输入0退出");
          delay(2000);
          Serial.println("已结束指纹设置");
          Serial.println(i);
          break;
        }
        if(i == 0)
        {
          i = -1;
          Serial.println("退出管理员模式");
          gui.label("正在退出管理员模式...");
          delay(3000);
          gui.label("本产品支持密码解锁，指纹解锁，RFID解锁，远程解锁");
          break;
        }
      }
    }
    keymemory.read_NVS("user_passwd");
    if(passwd == passwd_buff)
    {
      j = 2;
      passwd_len = 0;
      passwd = "";
      passwd_buff = "";
      Serial.println("密码输入正确");
      gui.label("密码输入正确");
      keyboard_falg = true;
    }
    if(j == 0)
    {
      Serial.println("密码输入错误");
      gui.label("密码输入错误");
      delay(3000);
      gui.label("本产品支持密码解锁，指纹解锁，RFID解锁，远程解锁");
      //gui.label("你好世界");
      j = 0;
    }
  passwd = "";
  passwd_len = 0;
  passwd_buff = "";
  } 
}