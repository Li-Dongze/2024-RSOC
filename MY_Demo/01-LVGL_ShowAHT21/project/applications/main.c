/*
 * Copyright (c) 2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-06     Supperthomas first version
 * 2023-12-03     Meco Man     support nano version
 */

#include <board.h>
#include <rtthread.h>
#include <drv_gpio.h>
#ifndef RT_USING_NANO
#include <rtdevice.h>

#include "drv_aht21.h"
#include <lvgl.h>

char buf[16];
lv_obj_t* label;

#define LOG_TAG "main"
#define LOG_LVL LOG_LVL_DBG
#include "ulog.h"

#endif /* RT_USING_NANO */

#define GPIO_LED_B    GET_PIN(F, 11)
#define GPIO_LED_R    GET_PIN(F, 12)
int main(void)
{
    rt_pin_mode(GPIO_LED_R, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(GPIO_LED_R, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(GPIO_LED_R, PIN_LOW);
        rt_thread_mdelay(500);

        uint16_t Tem = My_AHT21GetTemperature();
        rt_sprintf(buf, LV_SYMBOL_HOME "%d.%02d", Tem/100, Tem%100);
        lv_label_set_text(label, buf);
    }
}

void lv_user_gui_init(void)
{
    /* display demo; you may replace with your LVGL application at here */
//    extern void lv_demo_pingpong(void);
//    extern lv_demo_calendar();
//    lv_demo_calendar();


//    extern void lv_demo_music(void);
//    lv_demo_music();


    // extern void lv_demo_benchmark(void);
    // lv_demo_benchmark();

    // extern void lv_demo_calendar(void);
    // lv_demo_calendar();

    label = lv_label_create(lv_scr_act());
    
    
    lv_obj_center(label);

//    extern lv_demo_widgets();
//    lv_demo_widgets();
}