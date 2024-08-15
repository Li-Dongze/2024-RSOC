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
#include "events_init.h"
#include "gui_guider.h"
#include "icm20608_get.h"
#include <math.h>  // 包含 fabs 函数的头文件

#define KEY_DOWN        GET_PIN(C, 1)
#define KEY_LEFT        GET_PIN(C, 0)
#define KEY_RIGHT       GET_PIN(C, 4)
#define KEY_UP          GET_PIN(C, 5)

#define ANGLE_MAX       30

uint8_t Key_Value;
uint8_t Key_Down;
uint8_t Key_Old;

enum Key_Num{
    UP = 1,
    DOWN,
    LEFT,
    RIGHT,
    CLICK
};

uint8_t icm20608_Read(void)
{
    if(!rt_pin_read(KEY_DOWN))
    {
        return CLICK;
    }
    if(imu_Angle.Roll < ANGLE_MAX && imu_Angle.Roll > -ANGLE_MAX && imu_Angle.Pitch < ANGLE_MAX && imu_Angle.Pitch > -ANGLE_MAX)
    {
        return 0;
    }
    else if(fabs(imu_Angle.Roll) > fabs(imu_Angle.Pitch) && imu_Angle.Roll > 0)
    {
        return DOWN;
    }
    else if(fabs(imu_Angle.Roll) > fabs(imu_Angle.Pitch) && imu_Angle.Roll < 0)
    {
        return UP;
    }
    else if(fabs(imu_Angle.Roll) < fabs(imu_Angle.Pitch) && imu_Angle.Pitch > 0)
    {
        return RIGHT;
    }
    else if(fabs(imu_Angle.Roll) < fabs(imu_Angle.Pitch) && imu_Angle.Pitch < 0)
    {
        return LEFT;
    }
}

static void keypadRead(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    Key_Value = icm20608_Read();
    Key_Down = Key_Value&(Key_Value^Key_Old);
    Key_Old = Key_Value;

    switch (Key_Down)
    {
    case CLICK/* constant-expression */:
        /* code */
        data->key = LV_KEY_ENTER;
        data->state = LV_INDEV_STATE_PRESSED;
        break;

    case LEFT:
        data->key = LV_KEY_PREV;
        data->state = LV_INDEV_STATE_PRESSED;
        break;    

    case RIGHT:
        data->key = LV_KEY_NEXT;
        data->state = LV_INDEV_STATE_PRESSED;
        break;

    case DOWN:
        data->key = LV_KEY_DOWN;
        data->state = LV_INDEV_STATE_PRESSED;
        break;     

    case UP:
        data->key = LV_KEY_UP;
        data->state = LV_INDEV_STATE_PRESSED;
        break;           
    
    default:
        data->state = LV_INDEV_STATE_RELEASED;
        break;
    }

}

uint8_t Key_Read(void)
{
    uint8_t Key_Value = 0;
    if(!rt_pin_read(KEY_DOWN)){
        Key_Value = 1;
    }else if(!rt_pin_read(KEY_LEFT)){
        Key_Value = 2;
    }else if(!rt_pin_read(KEY_RIGHT)){
        Key_Value = 3;
    }else if(!rt_pin_read(KEY_UP)){
        Key_Value = 4;
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

// static void keypadRead(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
// {
//     Key_Value = Key_Read();
//     Key_Down = Key_Value&(Key_Value^Key_Old);
//     Key_Old = Key_Value;

//     switch (Key_Down)
//     {
//     case 1/* constant-expression */:
//         /* code */
//         data->key = LV_KEY_ENTER;
//         data->state = LV_INDEV_STATE_PRESSED;
//         break;

//     case 2:
//         data->key = LV_KEY_PREV;
//         data->state = LV_INDEV_STATE_PRESSED;
//         break;    

//     case 3:
//         data->key = LV_KEY_NEXT;
//         data->state = LV_INDEV_STATE_PRESSED;
//         break;

//     case 4:
//         data->key = LV_KEY_DOWN;
//         data->state = LV_INDEV_STATE_PRESSED;
//         break;            
    
//     default:
//         data->state = LV_INDEV_STATE_RELEASED;
//         break;
//     }

// }


lv_indev_drv_t indev_drv;
lv_indev_t* keypadIndevice;
lv_group_t* group_main;
lv_group_t* group_screen1;

void lv_port_indev_init(void)
{
    rt_pin_mode(KEY_DOWN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY_LEFT, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY_RIGHT, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY_UP, PIN_MODE_INPUT_PULLUP);
    //  lv_indev_drv_init(&indev_drv);
    //  indev_drv.type = LV_INDEV_TYPE_BUTTON;
    //  indev_drv.read_cb = button_read;
    //  lv_indev_t* indev_button = lv_indev_drv_register(&indev_drv);

    //  static const lv_point_t btn_points[1] = {
    //         {120, 120}   /*Button 0 -> x:10; 	y:10 	KEY0*/           
    //  };
    //  // 把外设映射到屏幕的像素上
    //  lv_indev_set_button_points(indev_button, btn_points);

    //创建主界面部件组
    // lv_group_t* group_main = lv_group_create();
    // //lv_group_add_obj(group_main, guider_ui.screen_btn_1_label);
    // lv_group_set_default(group_main);
    //创建screen1部件组
    // lv_group_t* group_screen1 = lv_group_create();
    // lv_group_add_obj(group_screen1, guider_ui.screen_1_btn_AllBlue);
    // lv_group_add_obj(group_screen1, guider_ui.screen_1_btn_AllGreen);
    // lv_group_add_obj(group_screen1, guider_ui.screen_1_btn_AllRed);
    // lv_group_add_obj(group_screen1, guider_ui.screen_1_btn_Back);
    // lv_group_add_obj(group_screen1, guider_ui.screen_1_btn_blue);
    // lv_group_add_obj(group_screen1, guider_ui.screen_1_btn_green);
    // lv_group_add_obj(group_screen1, guider_ui.screen_1_btn_MulticColour);
    // lv_group_add_obj(group_screen1, guider_ui.screen_1_btn_red);
    // lv_group_add_obj(group_screen1, guider_ui.screen_1_btn_white);
    // lv_group_add_obj(group_screen1, guider_ui.screen_1_ddlist_ColourSelect);

    //创建键盘输入外设
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypadRead;

    keypadIndevice = lv_indev_drv_register(&indev_drv);

    // // 把按键捆绑到组上
    // lv_indev_set_group(keypadIndevice, group_main);
    // //lv_indev_set_group(keypadIndevice, group_screen1);
    

}