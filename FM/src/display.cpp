/**
 * 函数名：display
 * 功能：显示驱动，LVGL设置好内容，通过该驱动把内容显示到屏幕上
 **/
#include "display.h"

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */

/*屏幕的宽高在这里修改*/
static const uint32_t screenWidth  = 320;
static const uint32_t screenHight = 172;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

//开启日志后调用的函数，启用该功能需要修改lvgl_conf.h的对应功能
void my_print( lv_log_level_t level, const char * file, uint32_t line, const char * fn_name, const char * dsc )
{
   Serial.printf( "%s(%s)@%d->%s\r\n", file, fn_name, line, dsc );
   Serial.flush();
}

/* 刷新屏幕 */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
   uint32_t w = ( area->x2 - area->x1 + 1 );
   uint32_t h = ( area->y2 - area->y1 + 1 );

   tft.startWrite();
   tft.setAddrWindow( area->x1, area->y1, w, h );
   tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
   tft.endWrite();

   lv_disp_flush_ready( disp );//图像显示驱动就绪
}

void Display::init( )//初始化屏幕的函数，放在setup里开始初始化屏幕
{
    tft.fillScreen(0xffffff);
    tft.begin();          /* TFT init ，初始化屏幕*/
    tft.setRotation( 1 ); /* 旋转屏幕，n * 90度 ，3表示270度*/

    lv_init();//初始化LVGL

    // 建立一个屏幕宽*10大小的缓冲区
    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );

    /*初始化屏幕*/
    static lv_disp_drv_t disp_drv;//画笔
    lv_disp_drv_init( &disp_drv );//初始化画笔
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;//宽
    disp_drv.ver_res = screenHight;//高
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );
   //  lv_disp_set_bg_color(lv_disp_get_default(),lv_color_make(0xcc,0xcc,0xff));
}
void Display::routine()
{
	lv_task_handler();
   lv_tick_inc(1);
}
