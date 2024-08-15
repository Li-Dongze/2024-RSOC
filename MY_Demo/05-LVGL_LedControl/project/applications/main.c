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
#endif /* RT_USING_NANO */

#include "aht10.h"
#include <lvgl.h>
#include "icm20608_get.h"
#include <drv_matrix_led.h>

#define GPIO_LED_B    GET_PIN(F, 11)
#define GPIO_LED_R    GET_PIN(F, 12)

// AHT挂载的总线名字
#define AHT10_I2C_BUS "i2c3"

/* tid_icm10608线程参数 */
#define THREAD1_PRIORITY         25
#define THREAD1_STACK_SIZE       1024
#define THREAD1_TIMESLICE        5
/* tid_led线程参数 */
#define THREAD2_PRIORITY         25
#define THREAD2_STACK_SIZE       1024
#define THREAD2_TIMESLICE        5
/* tid_aht10线程参数 */
#define THREAD3_PRIORITY         25
#define THREAD3_STACK_SIZE       2048
#define THREAD3_TIMESLICE        5

extern aht10_device_t Dev;

char buf_Temp[20];
char buf_Humi[20];
// Humi:湿度值,Temp:温度值
float Humi, Temp;

static rt_thread_t tid_icm10608 = RT_NULL;
static rt_thread_t tid_led = RT_NULL;
static rt_thread_t tid_aht10 = RT_NULL;

/* 指向互斥量的指针 */
rt_mutex_t dynamic_mutex = RT_NULL;
int led_mode = 0;
uint16_t list_id = 0;

/* 线程 1 的入口函数 */
static void icm10608_NomalData(void *parameter)
{
    while (1)
    {
        /* 读 取 三 轴 加 速 度 */
        icm20608_get_accel(dev, &Ax, &Ay, &Az);

        /* 读 取 三 轴 陀 螺 仪 */
        icm20608_get_gyro(dev, &Gx, &Gy, &Gz);
    }
}

/* 线程 2 的入口函数 */
static void led_control(void *parameter)
{
    while (1)
    {
        /* P操作 */ 
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);

        switch (led_mode)
        {
        case 1:
            /* 全红灯 */
            led_matrix_fill(RED);
            led_mode = 0;
            break;

        case 2:
            /* 全绿灯 */
            led_matrix_fill(GREEN);
            led_mode = 0;
            break;

        case 3:
            /* 全蓝灯 */
            led_matrix_fill(BLUE);
            led_mode = 0;
            break;

        case 4:
            /* 彩灯，灯珠滚动 */
            led_matrix_show_color((uint8_t)imu_Angle.Roll, (uint8_t)imu_Angle.Pitch, (uint8_t)imu_Angle.Yaw);
            break;

        case 5:
            /* 1/3蓝灯 */
            LED_Set(list_id, BLUE);
            led_mode = 0;
            break;

        case 6:
            /* 1/3绿灯 */
            LED_Set(list_id, GREEN);
            led_mode = 0;
            break;

        case 7:
            /* 1/3红灯 */
            LED_Set(list_id, RED);
            led_mode = 0;
            break;

        case 8:
            /* 1/3白灯 */
            LED_Set(list_id, WHITE);
            led_mode = 0;
            break;
        
        default:
            break;
        }

        /* V操作 */ 
        rt_mutex_release(dynamic_mutex);
    }
}

/* 线程 3 的入口函数 */
static void aht10_read(void *parameter)
{
    while(1)
    {
        // 读取温湿度值
        Humi = aht10_read_humidity(Dev);
        Temp = aht10_read_temperature(Dev);

        rt_sprintf(buf_Temp, LV_SYMBOL_HOME "%d.%d", (int)Temp, (int)(Temp * 10) % 10);
        // lv_label_set_text(label_Temp, buf_Temp);
        rt_sprintf(buf_Humi, LV_SYMBOL_BELL "%d.%d", (int)Humi, (int)(Humi * 10) % 10);
        // lv_label_set_text(label_Humi, buf_Humi);
    }
}

int main(void)
{
    rt_pin_mode(GPIO_LED_R, PIN_MODE_OUTPUT);

    /* 创建一个动态互斥量 */
    dynamic_mutex = rt_mutex_create("dmutex", RT_IPC_FLAG_PRIO);
    if (dynamic_mutex == RT_NULL)
    {
        rt_kprintf("create dynamic mutex failed.\n");
    }

    /* 创建线程tid_icm10608 */
    tid_icm10608 = rt_thread_create("tid_icm10608",
                            icm10608_NomalData, RT_NULL,
                            THREAD1_STACK_SIZE,
                            THREAD1_PRIORITY, THREAD1_TIMESLICE);
    /* 如果获得线程控制块，启动这个线程 */
    if (tid_icm10608 != RT_NULL)
        rt_thread_startup(tid_icm10608);
    /* 开启定时器，5ms获取一次欧拉角 */
    timer_icm20608();

    /* 创建线程tid_led */
    tid_led = rt_thread_create("tid_led",
                            led_control, RT_NULL,
                            THREAD2_STACK_SIZE,
                            THREAD2_PRIORITY, THREAD2_TIMESLICE);
    /* 如果获得线程控制块，启动这个线程 */
    if (tid_led != RT_NULL)
        rt_thread_startup(tid_led);

    /* 创建线程tid_aht10 */
    tid_aht10 = rt_thread_create("tid_aht10",
                            aht10_read, RT_NULL,
                            THREAD3_STACK_SIZE,
                            THREAD3_PRIORITY, THREAD3_TIMESLICE);
    /* 如果获得线程控制块，启动这个线程 */
    if (tid_aht10 != RT_NULL)
        rt_thread_startup(tid_aht10);

    while (1)
    {
        rt_pin_write(GPIO_LED_R, PIN_HIGH);
        rt_thread_mdelay(100);
        rt_pin_write(GPIO_LED_R, PIN_LOW);
        rt_thread_mdelay(100);

        // rt_kprintf("roll: %.2f, pitch: %.2f, yaw: %.2f\n", imu_Angle.Roll, imu_Angle.Pitch, imu_Angle.Yaw);

    }
}
