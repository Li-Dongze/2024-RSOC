/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include <drv_matrix_led.h>

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

extern lv_indev_t* keypadIndevice;
extern lv_group_t* group_main;
extern lv_group_t* group_screen1;

extern rt_mutex_t dynamic_mutex;
extern int led_mode;
extern uint16_t list_id;

static void screen_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.screen_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_MOVE_LEFT, 240, 10, true, false);
		// 切换捆绑键盘输入
		lv_indev_set_group(keypadIndevice, group_screen1);
		break;
	}
    default:
        break;
    }
}

void events_init_screen (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_btn_1, screen_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_1_btn_AllRed_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		/* P操作 */ 
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);

		led_mode = 1;

		/* V操作 */ 
        rt_mutex_release(dynamic_mutex);
		break;
	}
    default:
        break;
    }
}

static void screen_1_btn_AllGreen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		/* P操作 */ 
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);

		led_mode = 2;
		
		/* V操作 */ 
        rt_mutex_release(dynamic_mutex);
		break;
	}
    default:
        break;
    }
}

static void screen_1_btn_AllBlue_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		/* P操作 */ 
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);

		led_mode = 3;
		
		/* V操作 */ 
        rt_mutex_release(dynamic_mutex);
		break;
	}
    default:
        break;
    }
}

static void screen_1_btn_MulticColour_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		/* P操作 */ 
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);

		led_mode = 4;
		
		/* V操作 */ 
        rt_mutex_release(dynamic_mutex);
		break;
	}
    default:
        break;
    }
}

static void screen_1_btn_Back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen_1_del, setup_scr_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 240, 10, true, false);
		// 切换捆绑键盘输入
		lv_indev_set_group(keypadIndevice, group_main);
		break;
	}
    default:
        break;
    }
}

static void screen_1_ddlist_ColourSelect_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		/* P操作 */ 
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);

		uint16_t id = lv_dropdown_get_selected(guider_ui.screen_1_ddlist_ColourSelect);
		list_id = id;

		/* V操作 */ 
        rt_mutex_release(dynamic_mutex);
		break;
	}
    default:
        break;
    }
}

static void screen_1_btn_blue_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		/* P操作 */ 
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);

		led_mode = 5;
		
		/* V操作 */ 
        rt_mutex_release(dynamic_mutex);
		break;
	}
    default:
        break;
    }
}

static void screen_1_btn_green_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		/* P操作 */ 
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);

		led_mode = 6;
		
		/* V操作 */ 
        rt_mutex_release(dynamic_mutex);
		break;
	}
    default:
        break;
    }
}

static void screen_1_btn_red_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		/* P操作 */ 
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);

		led_mode = 7;
		
		/* V操作 */ 
        rt_mutex_release(dynamic_mutex);
		break;
	}
    default:
        break;
    }
}

static void screen_1_btn_white_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		/* P操作 */ 
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);

		led_mode = 8;
		
		/* V操作 */ 
        rt_mutex_release(dynamic_mutex);
		break;
	}
    default:
        break;
    }
}

void events_init_screen_1 (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_1_btn_AllRed, screen_1_btn_AllRed_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_1_btn_AllGreen, screen_1_btn_AllGreen_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_1_btn_AllBlue, screen_1_btn_AllBlue_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_1_btn_MulticColour, screen_1_btn_MulticColour_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_1_btn_Back, screen_1_btn_Back_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_1_ddlist_ColourSelect, screen_1_ddlist_ColourSelect_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_1_btn_blue, screen_1_btn_blue_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_1_btn_green, screen_1_btn_green_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_1_btn_red, screen_1_btn_red_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_1_btn_white, screen_1_btn_white_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}