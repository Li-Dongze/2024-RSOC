/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     The first version
 */
#include <lvgl.h>
#include <stdbool.h>
#include <rtdevice.h>
#include <board.h>
#include <drv_gpio.h>

#define KEY_DOWN    GET_PIN(C, 1)

uint8_t Key_Value;
uint8_t Key_Down;
uint8_t Key_Old;

uint8_t Key_Read(void)
{
    uint8_t Key_Value = 0;
    if(!rt_pin_read(KEY_DOWN)){
        Key_Value = 1;
    }
    return Key_Value;
}

static void button_read(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    Key_Value = Key_Read();
    Key_Down = Key_Value&(Key_Value^Key_Old);
    Key_Old = Key_Value;

    switch (Key_Down)
    {
    case 1/* constant-expression */:
        /* code */
        data->btn_id = 0;
        data->state = LV_INDEV_STATE_PRESSED;
        break;
    
    default:
        data->state = LV_INDEV_STATE_RELEASED;
        break;
    }


}

lv_indev_drv_t indev_drv;

void lv_port_indev_init(void)
{
     rt_pin_mode(KEY_DOWN, PIN_MODE_INPUT_PULLUP);
     lv_indev_drv_init(&indev_drv);
     indev_drv.type = LV_INDEV_TYPE_BUTTON;
     indev_drv.read_cb = button_read;
     lv_indev_t* indev_button = lv_indev_drv_register(&indev_drv);

     static const lv_point_t btn_points[1] = {
            {120, 120}   /*Button 0 -> x:10; 	y:10 	KEY0*/           
     };
     // 把外设映射到屏幕的像素上
     lv_indev_set_button_points(indev_button, btn_points);

}
