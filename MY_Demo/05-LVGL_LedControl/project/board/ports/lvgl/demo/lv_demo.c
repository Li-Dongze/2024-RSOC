/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-17     Meco Man      first version
 * 2022-05-10     Meco Man      improve rt-thread initialization process
 */
#include <lvgl.h>
#include "events_init.h"
#include "gui_guider.h"

lv_ui guider_ui;
// extern lv_ui guider_ui;
lv_obj_t* label_Temp;
lv_obj_t* label_Humi;

void My_LVGLTest(void)
{
    setup_ui(&guider_ui);
    events_init(&guider_ui);

    // 温度动态文本
    label_Temp = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label_Temp,LV_LABEL_LONG_WRAP);//设置长文本模式
    lv_obj_set_pos(label_Temp,60,50);//设置坐标
    lv_obj_set_style_text_font(label_Temp, &lv_font_montserrat_36, 0);
    // lv_label_set_text(label_Temp, buf_Temp);

    // 湿度动态文本
    label_Humi = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label_Humi,LV_LABEL_LONG_WRAP);//设置长文本模式
    lv_obj_set_pos(label_Humi,60,120);//设置坐标
    lv_obj_set_style_text_font(label_Humi, &lv_font_montserrat_36, 0);
    // lv_label_set_text(label_Humi, buf_Humi);
}

void lv_user_gui_init(void)
{
    /* display demo; you may replace with your LVGL application at here */
//    extern void lv_demo_pingpong(void);
//    extern lv_demo_calendar();
//    lv_demo_calendar();


//    extern void lv_demo_music(void);
//    lv_demo_music();
    My_LVGLTest();

    // extern void lv_demo_benchmark(void);
    // lv_demo_benchmark();

//    extern lv_demo_widgets();
//    lv_demo_widgets();
}
