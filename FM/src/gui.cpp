/**
 * 函数名：gui
 * 功能：显示内容，用于提示用操作
 **/
#include "gui.h"
/*//初始化完成WIFI初始化MQTT初始化指纹初始化...RFID初始化ESP32cam初始化人体红外初始化
//密码输入正确密码输入错误管理员模式0123456789输入1修改管理员密码2修改用户密码
//3修改指纹设置4修改RFID远程监控开启门锁打开门锁关闭你好世界*/
LV_FONT_DECLARE(lock_font);

lv_obj_t * label1;//创建标签对象
void MYGUI::gui_inti()//标签显示初始化函数
{
    label1 = lv_label_create(lv_scr_act());//创建标签对象在父对象上，父对象为lv_scr_act()，lv_scr_act()是屏幕
    lv_obj_set_width(label1,320);//设置标签宽度为320
    lv_obj_set_height(label1,50);//
    lv_obj_center(label1);//使标签居中
    lv_obj_set_style_text_color(label1,lv_color_hex(0x00ffdd),0);//设置字体颜色
    lv_obj_set_style_text_font(label1,&lock_font,0);//设置字体为自定义，&lock_font自定义字体C数组
    lv_label_set_text(label1,"显示初始化...");//设置文本
    lv_label_set_long_mode(label1,LV_LABEL_LONG_SCROLL_CIRCULAR);//字数过长无法显示时,滚动显示
}

void MYGUI::label(const char * text)//显示内容的对象，主函数调用该对象即可修改显示内容
{
    lv_label_set_text(label1,"");//设置文本
    delay(50);  
    lv_label_set_text(label1,text);//设置文本
    delay(50);//延时使新内容可以上载到屏幕上
}