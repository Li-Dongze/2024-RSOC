/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

extern lv_indev_t* keypadIndevice;
extern lv_group_t* group_screen1;

void setup_scr_screen_1(lv_ui *ui)
{
	//Write codes screen_1
	ui->screen_1 = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_1, 240, 240);
	lv_obj_set_scrollbar_mode(ui->screen_1, LV_SCROLLBAR_MODE_OFF);
	// 创建组
	group_screen1 = lv_group_create();

	//Write style for screen_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_1_btn_AllRed
	ui->screen_1_btn_AllRed = lv_btn_create(ui->screen_1);
	ui->screen_1_btn_AllRed_label = lv_label_create(ui->screen_1_btn_AllRed);
	lv_label_set_text(ui->screen_1_btn_AllRed_label, "全红灯");
	lv_label_set_long_mode(ui->screen_1_btn_AllRed_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_1_btn_AllRed_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_1_btn_AllRed, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_1_btn_AllRed_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_1_btn_AllRed, 17, 16);
	lv_obj_set_size(ui->screen_1_btn_AllRed, 62, 36);

	//Write style for screen_1_btn_AllRed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_1_btn_AllRed, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_1_btn_AllRed, lv_color_hex(0xf00000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_AllRed, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_1_btn_AllRed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_1_btn_AllRed, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_1_btn_AllRed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_1_btn_AllRed, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_1_btn_AllRed, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_1_btn_AllRed, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_1_btn_AllRed, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_1_btn_AllGreen
	ui->screen_1_btn_AllGreen = lv_btn_create(ui->screen_1);
	ui->screen_1_btn_AllGreen_label = lv_label_create(ui->screen_1_btn_AllGreen);
	lv_label_set_text(ui->screen_1_btn_AllGreen_label, "全绿灯");
	lv_label_set_long_mode(ui->screen_1_btn_AllGreen_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_1_btn_AllGreen_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_1_btn_AllGreen, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_1_btn_AllGreen_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_1_btn_AllGreen, 17, 67);
	lv_obj_set_size(ui->screen_1_btn_AllGreen, 60, 35);

	//Write style for screen_1_btn_AllGreen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_1_btn_AllGreen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_1_btn_AllGreen, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_AllGreen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_1_btn_AllGreen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_1_btn_AllGreen, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_1_btn_AllGreen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_1_btn_AllGreen, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_1_btn_AllGreen, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_1_btn_AllGreen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_1_btn_AllGreen, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_1_btn_AllBlue
	ui->screen_1_btn_AllBlue = lv_btn_create(ui->screen_1);
	ui->screen_1_btn_AllBlue_label = lv_label_create(ui->screen_1_btn_AllBlue);
	lv_label_set_text(ui->screen_1_btn_AllBlue_label, "全蓝灯");
	lv_label_set_long_mode(ui->screen_1_btn_AllBlue_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_1_btn_AllBlue_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_1_btn_AllBlue, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_1_btn_AllBlue_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_1_btn_AllBlue, 17.5, 128);
	lv_obj_set_size(ui->screen_1_btn_AllBlue, 61, 35);

	//Write style for screen_1_btn_AllBlue, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_1_btn_AllBlue, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_1_btn_AllBlue, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_AllBlue, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_1_btn_AllBlue, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_1_btn_AllBlue, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_1_btn_AllBlue, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_1_btn_AllBlue, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_1_btn_AllBlue, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_1_btn_AllBlue, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_1_btn_AllBlue, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_1_btn_MulticColour
	ui->screen_1_btn_MulticColour = lv_btn_create(ui->screen_1);
	ui->screen_1_btn_MulticColour_label = lv_label_create(ui->screen_1_btn_MulticColour);
	lv_label_set_text(ui->screen_1_btn_MulticColour_label, "彩灯");
	lv_label_set_long_mode(ui->screen_1_btn_MulticColour_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_1_btn_MulticColour_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_1_btn_MulticColour, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_1_btn_MulticColour_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_1_btn_MulticColour, 17, 188);
	lv_obj_set_size(ui->screen_1_btn_MulticColour, 62, 38);

	//Write style for screen_1_btn_MulticColour, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_1_btn_MulticColour, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_1_btn_MulticColour, lv_color_hex(0xff00f7), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_MulticColour, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_1_btn_MulticColour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_1_btn_MulticColour, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_1_btn_MulticColour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_1_btn_MulticColour, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_1_btn_MulticColour, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_1_btn_MulticColour, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_1_btn_MulticColour, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_1_btn_Back
	ui->screen_1_btn_Back = lv_btn_create(ui->screen_1);
	ui->screen_1_btn_Back_label = lv_label_create(ui->screen_1_btn_Back);
	lv_label_set_text(ui->screen_1_btn_Back_label, "Back");
	lv_label_set_long_mode(ui->screen_1_btn_Back_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_1_btn_Back_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_1_btn_Back, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_1_btn_Back_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_1_btn_Back, 128, 170);
	lv_obj_set_size(ui->screen_1_btn_Back, 100, 50);

	//Write style for screen_1_btn_Back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_1_btn_Back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_1_btn_Back, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_Back, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_1_btn_Back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_1_btn_Back, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_1_btn_Back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_1_btn_Back, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_1_btn_Back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_1_btn_Back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_1_btn_Back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_1_ddlist_ColourSelect
	ui->screen_1_ddlist_ColourSelect = lv_dropdown_create(ui->screen_1);
	lv_dropdown_set_options(ui->screen_1_ddlist_ColourSelect, "LED1-6\nLED7-12\nLED13-18");
	lv_obj_set_pos(ui->screen_1_ddlist_ColourSelect, 99, 34);
	lv_obj_set_size(ui->screen_1_ddlist_ColourSelect, 130, 30);

	//Write style for screen_1_ddlist_ColourSelect, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_1_ddlist_ColourSelect, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_1_ddlist_ColourSelect, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_1_ddlist_ColourSelect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_1_ddlist_ColourSelect, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_1_ddlist_ColourSelect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_1_ddlist_ColourSelect, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_1_ddlist_ColourSelect, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_1_ddlist_ColourSelect, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_1_ddlist_ColourSelect, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_1_ddlist_ColourSelect, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_1_ddlist_ColourSelect, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_1_ddlist_ColourSelect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_1_ddlist_ColourSelect, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_1_ddlist_ColourSelect, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_1_ddlist_ColourSelect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for &style_screen_1_ddlist_ColourSelect_extra_list_selected_checked
	static lv_style_t style_screen_1_ddlist_ColourSelect_extra_list_selected_checked;
	ui_init_style(&style_screen_1_ddlist_ColourSelect_extra_list_selected_checked);
	
	lv_style_set_border_width(&style_screen_1_ddlist_ColourSelect_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_screen_1_ddlist_ColourSelect_extra_list_selected_checked, 255);
	lv_style_set_border_color(&style_screen_1_ddlist_ColourSelect_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_1_ddlist_ColourSelect_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_1_ddlist_ColourSelect_extra_list_selected_checked, 3);
	lv_style_set_bg_opa(&style_screen_1_ddlist_ColourSelect_extra_list_selected_checked, 255);
	lv_style_set_bg_color(&style_screen_1_ddlist_ColourSelect_extra_list_selected_checked, lv_color_hex(0x00a1b5));
	lv_style_set_bg_grad_dir(&style_screen_1_ddlist_ColourSelect_extra_list_selected_checked, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_1_ddlist_ColourSelect), &style_screen_1_ddlist_ColourSelect_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for &style_screen_1_ddlist_ColourSelect_extra_list_main_default
	static lv_style_t style_screen_1_ddlist_ColourSelect_extra_list_main_default;
	ui_init_style(&style_screen_1_ddlist_ColourSelect_extra_list_main_default);
	
	lv_style_set_max_height(&style_screen_1_ddlist_ColourSelect_extra_list_main_default, 90);
	lv_style_set_text_color(&style_screen_1_ddlist_ColourSelect_extra_list_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_1_ddlist_ColourSelect_extra_list_main_default, &lv_font_montserratMedium_12);
	lv_style_set_text_opa(&style_screen_1_ddlist_ColourSelect_extra_list_main_default, 255);
	lv_style_set_border_width(&style_screen_1_ddlist_ColourSelect_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_screen_1_ddlist_ColourSelect_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_1_ddlist_ColourSelect_extra_list_main_default, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_1_ddlist_ColourSelect_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_1_ddlist_ColourSelect_extra_list_main_default, 3);
	lv_style_set_bg_opa(&style_screen_1_ddlist_ColourSelect_extra_list_main_default, 255);
	lv_style_set_bg_color(&style_screen_1_ddlist_ColourSelect_extra_list_main_default, lv_color_hex(0xffffff));
	lv_style_set_bg_grad_dir(&style_screen_1_ddlist_ColourSelect_extra_list_main_default, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_1_ddlist_ColourSelect), &style_screen_1_ddlist_ColourSelect_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_1_ddlist_ColourSelect_extra_list_scrollbar_default
	static lv_style_t style_screen_1_ddlist_ColourSelect_extra_list_scrollbar_default;
	ui_init_style(&style_screen_1_ddlist_ColourSelect_extra_list_scrollbar_default);
	
	lv_style_set_radius(&style_screen_1_ddlist_ColourSelect_extra_list_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_screen_1_ddlist_ColourSelect_extra_list_scrollbar_default, 255);
	lv_style_set_bg_color(&style_screen_1_ddlist_ColourSelect_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
	lv_style_set_bg_grad_dir(&style_screen_1_ddlist_ColourSelect_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_1_ddlist_ColourSelect), &style_screen_1_ddlist_ColourSelect_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write codes screen_1_btn_blue
	ui->screen_1_btn_blue = lv_btn_create(ui->screen_1);
	ui->screen_1_btn_blue_label = lv_label_create(ui->screen_1_btn_blue);
	lv_label_set_text(ui->screen_1_btn_blue_label, "");
	lv_label_set_long_mode(ui->screen_1_btn_blue_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_1_btn_blue_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_1_btn_blue, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_1_btn_blue_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_1_btn_blue, 171, 111);
	lv_obj_set_size(ui->screen_1_btn_blue, 29, 25);

	//Write style for screen_1_btn_blue, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_1_btn_blue, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_1_btn_blue, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_blue, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_1_btn_blue, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_1_btn_blue, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_1_btn_blue, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_1_btn_blue, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_1_btn_blue, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_1_btn_blue, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_1_btn_blue, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_1_btn_green
	ui->screen_1_btn_green = lv_btn_create(ui->screen_1);
	ui->screen_1_btn_green_label = lv_label_create(ui->screen_1_btn_green);
	lv_label_set_text(ui->screen_1_btn_green_label, "");
	lv_label_set_long_mode(ui->screen_1_btn_green_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_1_btn_green_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_1_btn_green, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_1_btn_green_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_1_btn_green, 135, 111);
	lv_obj_set_size(ui->screen_1_btn_green, 29, 25);

	//Write style for screen_1_btn_green, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_1_btn_green, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_1_btn_green, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_green, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_1_btn_green, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_1_btn_green, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_1_btn_green, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_1_btn_green, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_1_btn_green, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_1_btn_green, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_1_btn_green, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_1_btn_red
	ui->screen_1_btn_red = lv_btn_create(ui->screen_1);
	ui->screen_1_btn_red_label = lv_label_create(ui->screen_1_btn_red);
	lv_label_set_text(ui->screen_1_btn_red_label, "");
	lv_label_set_long_mode(ui->screen_1_btn_red_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_1_btn_red_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_1_btn_red, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_1_btn_red_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_1_btn_red, 99, 111);
	lv_obj_set_size(ui->screen_1_btn_red, 29, 25);

	//Write style for screen_1_btn_red, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_1_btn_red, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_1_btn_red, lv_color_hex(0xf00000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_red, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_1_btn_red, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_1_btn_red, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_1_btn_red, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_1_btn_red, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_1_btn_red, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_1_btn_red, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_1_btn_red, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_1_btn_white
	ui->screen_1_btn_white = lv_btn_create(ui->screen_1);
	ui->screen_1_btn_white_label = lv_label_create(ui->screen_1_btn_white);
	lv_label_set_text(ui->screen_1_btn_white_label, "");
	lv_label_set_long_mode(ui->screen_1_btn_white_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_1_btn_white_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_1_btn_white, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_1_btn_white_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_1_btn_white, 207, 111);
	lv_obj_set_size(ui->screen_1_btn_white, 29, 25);

	//Write style for screen_1_btn_white, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_1_btn_white, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_1_btn_white, lv_color_hex(0xe3e3e3), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_white, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_1_btn_white, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_1_btn_white, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_1_btn_white, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_1_btn_white, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_1_btn_white, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_1_btn_white, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_1_btn_white, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of screen_1.
	// 添加到组
	lv_group_add_obj(group_screen1, ui->screen_1_btn_AllBlue);
    lv_group_add_obj(group_screen1, ui->screen_1_btn_AllGreen);
    lv_group_add_obj(group_screen1, ui->screen_1_btn_AllRed);
    lv_group_add_obj(group_screen1, ui->screen_1_btn_Back);
    lv_group_add_obj(group_screen1, ui->screen_1_btn_blue);
    lv_group_add_obj(group_screen1, ui->screen_1_btn_green);
    lv_group_add_obj(group_screen1, ui->screen_1_btn_MulticColour);
    lv_group_add_obj(group_screen1, ui->screen_1_btn_red);
    lv_group_add_obj(group_screen1, ui->screen_1_btn_white);
    lv_group_add_obj(group_screen1, ui->screen_1_ddlist_ColourSelect);
	
	lv_indev_set_group(keypadIndevice, group_screen1);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_1);

	//Init events for screen.
	events_init_screen_1(ui);
}
