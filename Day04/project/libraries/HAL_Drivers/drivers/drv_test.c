#include <rtthread.h>
#include <rtdevice.h>

// #define DRV_DEBUG
#define LOG_TAG "drv.test"
#include <drv_log.h>

#if defined(BSP_USING_TEST)

static rt_err_t dev_test_init(rt_device_t dev) {
    LOG_I("test dev init");
    return RT_EOK;
}
static rt_err_t dev_test_open(rt_device_t dev, rt_uint16_t oflag) {
    LOG_I("test dev open flag = %d", oflag);
    return RT_EOK;
}
static rt_err_t dev_test_close(rt_device_t dev) {
    LOG_I("test dev close");
    return RT_EOK;
}
static rt_ssize_t dev_test_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size) {
    LOG_I("tese dev read pos = %d, size = %d", pos, size);
    return RT_EOK;
}
static rt_ssize_t drv_test_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size) {
    LOG_I("tese dev write pos = %d, size = %d", pos, size);
    return RT_EOK;
}
static rt_err_t drv_test_control(rt_device_t dev, int cmd, void *args) {
    LOG_I("test dev control cmd %d", cmd);
    return RT_EOK;
}
int rt_drv_test_init(void)
{
    rt_device_t test_dev = rt_device_create(RT_Device_Class_Char, 0);
    if (!test_dev) {
        LOG_E("test dev create failed.");
        return -RT_ERROR;
    }
    test_dev->init = dev_test_init;
    test_dev->open = dev_test_open;
    test_dev->close = dev_test_close;
    test_dev->read = dev_test_read;
    test_dev->write = drv_test_write;
    test_dev->control = drv_test_control;
    if (rt_device_register(test_dev, "test_dev", RT_DEVICE_FLAG_RDWR) != RT_EOK) {
        LOG_E("test dev register failed.");
        return -RT_ERROR;
    }
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_drv_test_init); // 内核启动前进行组件初始化

#endif