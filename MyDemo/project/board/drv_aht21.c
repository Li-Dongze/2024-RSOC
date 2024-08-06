#define LOG_TAG "drvAHT21"
#define LOG_LVL LOG_LVL_DBG
#include "ulog.h"

#include "drv_aht21.h"
#include <rtthread.h>
#include <rtdevice.h>

#define AHT21_I2C_BUS_NAME "i2c1"
#define AHT21_I2C_ADDR 0x38

static struct rt_i2c_bus_device * dev;

uint8_t ReadBuf[7] = {0};
uint8_t SendBuf[3] = {0};

int InitAHT21(){
    uint16_t Tem;

    dev = (struct rt_i2c_bus_device *)rt_device_find(AHT21_I2C_BUS_NAME);
    if (dev == RT_NULL)
    {
        LOG_E("can't find test dev.");
        return -RT_ERROR;
    }

    rt_i2c_master_recv(dev, AHT21_I2C_ADDR, 0, ReadBuf, 1);
    LOG_D("ReadBuf[0] = 0x%x", ReadBuf[0]);

    Tem = My_AHT21GetTemperature();
    LOG_D("Temperature = %d.%02d", Tem/100, Tem%100);

    return 0;
}

// main函数初始化前运行设备初始化
INIT_DEVICE_EXPORT(InitAHT21);

uint16_t My_AHT21GetTemperature(void){
    // 发送获取温湿度信息的命令
    SendBuf[0] = 0xAC;
    SendBuf[1] = 0x33;
    SendBuf[2] = 0x00;    
    rt_i2c_master_send(dev, AHT21_I2C_ADDR, 0, SendBuf, 3);

    // 延时80ms，采集数据
    rt_thread_mdelay(80);

    rt_i2c_master_recv(dev, AHT21_I2C_ADDR, 0, ReadBuf, 7);
    LOG_HEX("ReadBuf", 16, ReadBuf, 7);

    uint64_t temperature = ReadBuf[3] & 0x0f;
    temperature = (temperature << 8) | ReadBuf[4];
    temperature = (temperature << 8) | ReadBuf[5];
    
    temperature = temperature * 20000 / (1<<20) - 5000;

    return temperature;
}




