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

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <drv_lcd.h>
#include <drv_gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <drv_lcd.h>
#include <time.h>
#define PIN_KEY0 GET_PIN(C, 0)
#define PIN_KEY1 GET_PIN(C, 1)
#define PIN_KEY2 GET_PIN(C, 4)
#define PIN_KEY3 GET_PIN(C, 5)
#define PIN_LED_R GET_PIN(F, 12)
#define DBG_TAG "main"
#define DBG_LVL         DBG_LOG
#include <rtdbg.h>
#define SNAKESIZE 100//蛇的身体最大节数
#define MAPWIDTH 240 //宽度
#define MAPHEIGHT 240//高度
volatile int key = 3;
int score = 0;
struct {
    int x;
    int y;
}food;
struct {
    int speed;
    int len;
    int x[SNAKESIZE];
    int y[SNAKESIZE];
}snake;
void drawMap()
{
    //打印上下边框
    for (int i = 0; i <= MAPWIDTH/16+4; i++)
    {
        //将光标移动依次到(i,0)处打印上边框
        lcd_show_string(i*12,0,16,"#");
        //将光标移动依次到(i,MAPHEIGHT)处打印下边框
        lcd_show_string(i*12,MAPHEIGHT-16,16,"#");
    }
    //打印左右边框
    for (int i = 1; i < MAPHEIGHT/16; i++)
    {
        //将光标移动依次到(0,i)处打印左边框
        lcd_show_string(0,i*16,16,"#");
        //将光标移动依次到(MAPWIDTH, i)处打印左边框
        lcd_show_string(MAPHEIGHT-16,i*16,16,"#");
    }
    //随机生成初始食物
    while (1)
    {
        srand((unsigned int)time(NULL));
        food.x = rand() % (MAPWIDTH/16)*16+16 ;
        food.y = rand() % (MAPHEIGHT/16)*16+16;
        if (food.x % 2 == 0){
            if(food.x>16 && food.x<MAPWIDTH-16 && food.y>16 &&food.y<MAPHEIGHT-16)break;
        }
    }
    lcd_show_string(food.x, food.y,16,"*");
    //初始化蛇的属性
    snake.len = 3;
    snake.speed = 16;
    //在屏幕中间生成蛇头
    snake.x[0] = 160;//x坐标为偶数
    snake.y[0] = 160;
    //打印蛇头
    lcd_show_string(snake.x[0], snake.y[0],16,"@");
    //生成初始的蛇身
    for (int i = 1; i < snake.len; i++)
    {
        //蛇身的打印，纵坐标不变，横坐标为上一节蛇身的坐标值+16
        snake.x[i] = (snake.x[i - 1] + 16);
        snake.y[i] = snake.y[i - 1];
        lcd_show_string(snake.x[i], snake.y[i],16,"#");
    }
    return;
}
void handleFood()
{
    srand(time(RT_NULL));
    lcd_show_string(snake.x[0], snake.y[0],16,"@");
    lcd_show_string(snake.x[snake.len - 1], snake.y[snake.len - 1],16," ");
    int tailx = snake.x[snake.len-1];
    int taily = snake.y[snake.len-1];
    for(int i = snake.len - 1; i > 0; i--){
       snake.x[i] = snake.x[i-1];
       snake.y[i] = snake.y[i-1];
   }
    if (snake.x[0] == food.x && snake.y[0] == food.y)//蛇头碰到食物
    {
        snake.x[snake.len] = tailx;
        snake.y[snake.len] = taily;
        lcd_show_string(tailx, taily,16,"#");
        snake.len++;//吃到食物，蛇身长度加1
        score += 10;//每个食物得10分
        //新生成一个合法食物
        while (1)
        {
            int sameRegion = 0;
            food.x = rand() % (MAPWIDTH/16)*16+16 ;
            food.y = rand() % (MAPHEIGHT/16)*16 + 16;
            //生成的食物横坐标的奇偶必须和初试时蛇头所在坐标的奇偶一致，因为一个字符占两个字节位置，不一致
            //会导致吃食物的时候只吃到一半
            //检查是否食物生成到边上
            if(food.x % 2 == 0 && food.x>16 && food.x<MAPWIDTH-16 && food.y>16 &&food.y<MAPHEIGHT-16)
            {
                //检查是否食物与蛇身体重合
                for (int i = 0; i < snake.len; i++)
                {
                    if (snake.x[i] == food.x && snake.y[i] == food.y)
                    {
                        sameRegion = 1;
                        break;
                    }
                }
            }
            else {
                sameRegion = 1;
            }
            if(!sameRegion){
                break;
            }
        }
        lcd_show_string(food.x, food.y,16,"*");
    }
    rt_kprintf("new cycle!");
    int pre_key = key ;//记录前一个按键的方向
   //判断蛇头应该往哪个方向移动
   switch (pre_key)
   {
   case 3:
       snake.x[0] -= snake.speed;//往左
       break;
   case 4:
       snake.x[0] += snake.speed;//往右
       break;
   case 1:
       snake.y[0]=snake.y[0]-snake.speed;//往上
       break;
   case 2:
       snake.y[0]=snake.y[0]+snake.speed;//往下
       break;
   }
 return;
}
void whereHead(){
    rt_kprintf("x:%d ;",snake.x[0]);
    rt_kprintf("y:%d\n",snake.y[0]);
}
rt_bool_t snakeStatus()
{
    whereHead();
    //蛇头碰到上下边界，游戏结束
    if (snake.y[0] <= 0|| snake.y[0] >= MAPHEIGHT-16)
        return RT_ERROR;
    //蛇头碰到左右边界，游戏结束
    if (snake.x[0] <= 0 || snake.x[0] >= MAPWIDTH-16)
        return RT_ERROR;
    //蛇头碰到蛇身，游戏结束
    for (int i = 1; i < snake.len; i++)
    {
        if (snake.x[i] == snake.x[0] && snake.y[i] == snake.y[0])
            return RT_ERROR;
    }
    return RT_EOK;
}
void keyDown(void *args)
{
    rt_kprintf("key %d \r\n",(int)args);
    key = (int)args;
   }
int main(void)
{
    drawMap();
    rt_pin_mode(PIN_KEY0, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(PIN_KEY1, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(PIN_KEY2, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(PIN_KEY3, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(PIN_KEY0, PIN_IRQ_MODE_FALLING, keyDown, (void*)3);
    rt_pin_attach_irq(PIN_KEY1, PIN_IRQ_MODE_FALLING, keyDown, (void*)2);
    rt_pin_attach_irq(PIN_KEY2, PIN_IRQ_MODE_FALLING, keyDown, (void*)4);
    rt_pin_attach_irq(PIN_KEY3, PIN_IRQ_MODE_FALLING, keyDown, (void*)1);
    rt_pin_irq_enable(PIN_KEY0, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(PIN_KEY1, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(PIN_KEY2, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(PIN_KEY3, PIN_IRQ_ENABLE);
    while (1)
    {
        if (snakeStatus())
            break;
        handleFood();
        rt_thread_mdelay(300);
    }
    lcd_show_string(MAPWIDTH / 2-32, MAPHEIGHT / 2,16,"Game Over!");
    lcd_show_string(MAPWIDTH / 2-32, MAPHEIGHT / 2+16,16,"Score:");
    lcd_show_num(MAPWIDTH / 2+16, MAPHEIGHT / 2+16,score,2, 16);
    rt_thread_mdelay(5000);
    return 0;
}