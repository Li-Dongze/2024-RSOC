#include <rtthread.h>
#include <rtdevice.h>
#include <drv_spi.h>
#include <drv_gpio.h>


static int spi_attach(void)
{
    //挂载SPI设备
    return rt_hw_spi_device_attach("spi1", "spi10", GET_PIN(A, 4));
    //struct rt_spi_device *spi_device = RT_NULL;
  	//rt_spi_bus_attach_device_cspin(spi_device, "spi20", "spi2",GET_PIN(B, 12), RT_NULL));
}
INIT_DEVICE_EXPORT(spi_attach);


#define PAW3395_SPI_DEVICE_NAME     "spi10"

static int spi_paw3395_sample(void)
{
    struct rt_spi_device *spi_dev_paw3395;
    char name[RT_NAME_MAX];
    rt_uint8_t w25x_read_id = 0x90;
    rt_uint8_t id[5] = {0};

    /* 查找 spi 设备获取设备句柄 */
    spi_dev_paw3395 = (struct rt_spi_device *)rt_device_find(PAW3395_SPI_DEVICE_NAME);
    if (!spi_dev_paw3395)
    {
        rt_kprintf("spi sample run failed! can't find spi10 device!\n");
        return RT_ERROR;
    }
    rt_kprintf("spi sample run success!\n");

    /* 配置spi设备 */
    struct rt_spi_configuration cfg;
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
    cfg.max_hz = 1 * 1000 * 1000;
    rt_spi_configure(spi_dev_paw3395, &cfg);

    /* 读取设备ID */
    rt_uint8_t sendBuff1 = 0x00 | 0x80;
    rt_uint8_t recvBuff1 = 0;
    rt_spi_send_then_recv(spi_dev_paw3395, &sendBuff1, 1, &recvBuff1, 1);
    rt_kprintf("PAW3395 ID = 0x%x", (int)recvBuff1);

    return RT_EOK;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(spi_paw3395_sample, spi paw3395 sample);