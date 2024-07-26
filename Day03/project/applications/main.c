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

#define PIN_KEY0    GET_PIN(C, 0)

#define GPIO_LED_B    GET_PIN(F, 11)
#define GPIO_LED_R    GET_PIN(F, 12)

/*=============================================测试例程================================================*/

// #include <rtthread.h>

// #define THREAD_PRIORITY         25
// #define THREAD_TIMESLICE        5

// /* 指向信号量的指针 */
// static rt_sem_t dynamic_sem = RT_NULL;

// rt_align(RT_ALIGN_SIZE)
// static char thread1_stack[1024];// 线程1栈空间
// static struct rt_thread thread1;// 线程1句柄

// /*线程1入口函数*/
// static void rt_thread1_entry(void *parameter)
// {
//     static rt_uint8_t count = 0;

//     while(1)
//     {
//         if(count <= 100)
//         {
//             count++;
//         }
//         else
//             return;

//         /* count 每计数 10 次，就释放一次信号量 */
//          if(0 == (count % 10))
//         {
//             rt_kprintf("t1 release a dynamic semaphore.\n");
//             rt_sem_release(dynamic_sem);
//         }
//     }
// }

// rt_align(RT_ALIGN_SIZE)
// static char thread2_stack[1024];// 线程2栈空间
// static struct rt_thread thread2;// 线程2句柄

// /*线程2入口函数*/
// static void rt_thread2_entry(void *parameter)
// {
//     static rt_err_t result;
//     static rt_uint8_t number = 0;
//     while(1)
//     {
//         /* 永久方式等待信号量，获取到信号量，则执行 number 自加的操作 */
//         result = rt_sem_take(dynamic_sem, RT_WAITING_FOREVER);
//         if (result != RT_EOK)
//         {
//             rt_kprintf("t2 take a dynamic semaphore, failed.\n");
//             rt_sem_delete(dynamic_sem);
//             return;
//         }
//         else
//         {
//             number++;
//             rt_kprintf("t2 take a dynamic semaphore. number = %d\n" ,number);
//         }
//     }
// }

// /* 信号量示例的初始化 */
// int semaphore_sample(void)
// {
//     /* 创建一个动态信号量，初始值是 0 */
//     dynamic_sem = rt_sem_create("dsem", 0, RT_IPC_FLAG_PRIO);
//     if (dynamic_sem == RT_NULL)
//     {
//         rt_kprintf("create dynamic semaphore failed.\n");
//         return -1;
//     }
//     else
//     {
//         rt_kprintf("create done. dynamic semaphore value = 0.\n");
//     }

//     /* 创建线程1，并启动 */
//     rt_thread_init(&thread1,
//                    "thread1",
//                    rt_thread1_entry,
//                    RT_NULL,
//                    &thread1_stack[0],
//                    sizeof(thread1_stack),
//                    THREAD_PRIORITY, THREAD_TIMESLICE);
//     rt_thread_startup(&thread1);

//     /* 创建线程2，并启动 */
//     rt_thread_init(&thread2,
//                    "thread2",
//                    rt_thread2_entry,
//                    RT_NULL,
//                    &thread2_stack[0],
//                    sizeof(thread2_stack),
//                    THREAD_PRIORITY-1, THREAD_TIMESLICE);
//     rt_thread_startup(&thread2);

//     return 0;
// }
// /* 导出到 msh 命令列表中 */
// MSH_CMD_EXPORT(semaphore_sample, semaphore sample);

/*===========================================main函数===============================================*/

int main(void)
{
    rt_pin_mode(GPIO_LED_R, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_KEY0, PIN_MODE_INPUT_PULLUP);

    while (1)
    {
        rt_pin_write(GPIO_LED_R, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(GPIO_LED_R, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

