#include <board.h>
#include <rtthread.h>
#include <drv_gpio.h>
#include "aht10.h"

// AHT挂载的总线名字
#define AHT10_I2C_BUS "i2c3"

// AHT设备指针
aht10_device_t Dev = RT_NULL;

// AHT测试样例
int AHT10_Init(void)
{
    // 初始化设备
    Dev = aht10_init(AHT10_I2C_BUS);
    if (Dev == RT_NULL)
    {
        rt_kprintf("AHT10_init Fail");
        return 0;
    }
    return 1;
}
INIT_DEVICE_EXPORT(AHT10_Init);

