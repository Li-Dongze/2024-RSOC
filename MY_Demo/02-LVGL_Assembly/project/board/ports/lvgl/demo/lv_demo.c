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
void My_LVGLTest(void)
{
     setup_ui(&guider_ui);
    events_init(&guider_ui);
}

void lv_user_gui_init(void)
{
    /* display demo; you may replace with your LVGL application at here */
//    extern void lv_demo_pingpong(void);
//    extern int lv_demo_calendar();
//    lv_demo_calendar();

    My_LVGLTest();

//    extern void lv_demo_music(void);
//    lv_demo_music();


    // extern void lv_demo_benchmark(void);
    // lv_demo_benchmark();

//    extern lv_demo_widgets();
//    lv_demo_widgets();
}
