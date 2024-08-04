# Day05-软件包和组件

## 软件包

定义：具有特定的功能，用来完成特定任务的一个程序或一组程序。可以粗略地把他理解为帮助我们完成了底层驱动的编写，我们只需要使用里面提供的API就好了。

功能：能够帮助我们更快的进行应用开发。

### 应用：阿里云上云

1. 开启板上外设AHT32

2. `pkgs –update`，更新软件包

3. 阿里云搭建

	平台：[https://www.aliyun.com/product/iot/iot_instc_public_cn](https://www.aliyun.com/product/iot/iot_instc_public_cn)

	进入后进行注册（如果你是新账户的话）并登录，然后选择管理控制台

	![image-20240725184110285](C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/image-20240725184110285.png)

	在管理控制台下选择公共实例

	![image-20240725184217401](C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/image-20240725184217401.png)

	点击创建产品

	<img src="C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/image-20240725184400238.png" alt="image-20240725184400238" style="zoom:50%;" />

	按要求输出，产品名称可以随意填写

	![image-20240725184517799](C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/image-20240725184517799.png)

	然后返回，点击设备，创建设备

	![image-20240725184835993](C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/image-20240725184835993.png)

	创建完成后可以新建一个物模型变量

	![image-20240725185053198](C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/image-20240725185053198.png)

	![image-20240725185216703](C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/image-20240725185216703.png)

	然后点击发布上线，然后就可以在功能定义这里看到刚刚定义的功能了。记得在Topic类列表中修改自定义user/get的权限改为订阅和发布，这样子我们才能通过这个Topic进行测试。

	![image-20240725185630684](C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/image-20240725185630684.png)

4. menuconfig中开启RW007

	打开RW007

	![MQTT配置1](C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/MQTT配置1.png)

	在软件包中找到阿里云的软件包

	![MQTT配置2](C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/MQTT配置2.png)

	使能后需要修改里面的一些参数

	![MQTT配置3](C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/MQTT配置3.png)

	在阿里云中找到这些参数并修改进去

	![image-20240725192141241](C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/image-20240725192141241.png)

	![image-20240725192218149](C:/Users/LDZ/Desktop/2024-RSOC/2024-RSOC/Day05/test/RSOC/Pictures/image-20240725192218149.png)

	然后再打开ENV末尾的使能样例，告诉我们如何使用。

5. 添加示例

	```c
	/*
	 *  NOTE: About demo topic of /${productKey}/${deviceName}/user/get
	 *
	 *  The demo device has been configured in IoT console (https://iot.console.aliyun.com)
	 *  so that its /${productKey}/${deviceName}/user/get can both be subscribed and published
	 *
	 *  We design this to completely demonstrate publish & subscribe process, in this way
	 *  MQTT client can receive original packet sent by itself
	 *
	 *  For new devices created by yourself, pub/sub privilege also requires being granted
	 *  to its /${productKey}/${deviceName}/user/get for successfully running whole example
	 */
	
	void mqtt_example_main(void *parameter)
	{
	    void *pclient = NULL;
	    int res = 0;
	    int loop_cnt = 0;
	    iotx_mqtt_param_t mqtt_params;
	
	    HAL_GetProductKey(DEMO_PRODUCT_KEY);
	    HAL_GetDeviceName(DEMO_DEVICE_NAME);
	    HAL_GetDeviceSecret(DEMO_DEVICE_SECRET);
	
	    EXAMPLE_TRACE("mqtt example");
	
	    /* Initialize MQTT parameter */
	    /*
	     * Note:
	     *
	     * If you did NOT set value for members of mqtt_params, SDK will use their default values
	     * If you wish to customize some parameter, just un-comment value assigning expressions below
	     *
	     **/
	    memset(&mqtt_params, 0x0, sizeof(mqtt_params));
	
	    /**
	     *
	     *  MQTT connect hostname string
	     *
	     *  MQTT server's hostname can be customized here
	     *
	     *  default value is ${productKey}.iot-as-mqtt.cn-shanghai.aliyuncs.com
	     */
	    /* mqtt_params.host = "something.iot-as-mqtt.cn-shanghai.aliyuncs.com"; */
	
	    /**
	     *
	     *  MQTT connect port number
	     *
	     *  TCP/TLS port which can be 443 or 1883 or 80 or etc, you can customize it here
	     *
	     *  default value is 1883 in TCP case, and 443 in TLS case
	     */
	    /* mqtt_params.port = 1883; */
	
	    /**
	     *
	     * MQTT request timeout interval
	     *
	     * MQTT message request timeout for waiting ACK in MQTT Protocol
	     *
	     * default value is 2000ms.
	     */
	    /* mqtt_params.request_timeout_ms = 2000; */
	
	    /**
	     *
	     * MQTT clean session flag
	     *
	     * If CleanSession is set to 0, the Server MUST resume communications with the Client based on state from
	     * the current Session (as identified by the Client identifier).
	     *
	     * If CleanSession is set to 1, the Client and Server MUST discard any previous Session and Start a new one.
	     *
	     * default value is 0.
	     */
	    /* mqtt_params.clean_session = 0; */
	
	    /**
	     *
	     * MQTT keepAlive interval
	     *
	     * KeepAlive is the maximum time interval that is permitted to elapse between the point at which
	     * the Client finishes transmitting one Control Packet and the point it starts sending the next.
	     *
	     * default value is 60000.
	     */
	    /* mqtt_params.keepalive_interval_ms = 60000; */
	
	    /**
	     *
	     * MQTT write buffer size
	     *
	     * Write buffer is allocated to place upstream MQTT messages, MQTT client will be limitted
	     * to send packet no longer than this to Cloud
	     *
	     * default value is 1024.
	     *
	     */
	    /* mqtt_params.write_buf_size = 1024; */
	
	    /**
	     *
	     * MQTT read buffer size
	     *
	     * Write buffer is allocated to place downstream MQTT messages, MQTT client will be limitted
	     * to recv packet no longer than this from Cloud
	     *
	     * default value is 1024.
	     *
	     */
	    /* mqtt_params.read_buf_size = 1024; */
	
	    /**
	     *
	     * MQTT event callback function
	     *
	     * Event callback function will be called by SDK when it want to notify user what is happening inside itself
	     *
	     * default value is NULL, which means PUB/SUB event won't be exposed.
	     *
	     */
	    mqtt_params.handle_event.h_fp = example_event_handle;
	
	    pclient = IOT_MQTT_Construct(&mqtt_params);
	    if (NULL == pclient)
	    {
	        EXAMPLE_TRACE("MQTT construct failed");
	        return;
	    }
	
	    res = example_subscribe(pclient);
	    if (res < 0)
	    {
	        IOT_MQTT_Destroy(&pclient);
	        return;
	    }
	
	    while (1)
	    {
	        if (0 == loop_cnt % 20)
	        {
	            example_publish(pclient);
	        }
	
	        IOT_MQTT_Yield(pclient, 200);
	
	        loop_cnt += 1;
	    }
	}
	
	#define THREAD_PRIORITY 25
	#define THREAD_STACK_SIZE 4096
	#define THREAD_TIMESLICE 5
	
	rt_thread_t MQTT_Thread;
	
	void MQTT_Creat_Thread(void)
	{
	    // 创建线程
	    MQTT_Thread = rt_thread_create("MQTT_Thread", mqtt_example_main, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	    // 创建成功就启动
	    if (MQTT_Thread != RT_NULL)
	    {
	        rt_thread_startup(MQTT_Thread);
	    }
	    else
	    {
	        rt_kprintf("MQTT_Thread_Thread Create Fail");
	    }
	}
	// 导出Shell命令
	MSH_CMD_EXPORT(MQTT_Creat_Thread, This Function will creat a MQTT thread.);
	
	```

	## 组件

	在 RT-Thread DFS 中，文件系统有统一的根目录，使用 `/` 来表示。

	![目录结构图](https://www.rt-thread.org/document/site/rt-thread-version/rt-thread-standard/programming-manual/filesystem/figures/fs-dir.png)

	

	![DFS 层次架构图](https://www.rt-thread.org/document/site/rt-thread-version/rt-thread-standard/programming-manual/filesystem/figures/fs-layer.png)

	### 文件系统种类

	| 类型  |                             特点                             |
	| ----- | :----------------------------------------------------------: |
	| FatFS | FatFS 是专为小型嵌入式设备开发的一个兼容微软 FAT 格式的文件系统，采用ANSI C编写，具有良好的硬件无关性以及可移植性，是 RT-Thread 中最常用的文件系统类型。我们今天使用到的elm_fat就是这个类型。 |
	| RomFS | 传统型的 RomFS 文件系统是一种简单的、紧凑的、只读的文件系统，不支持动态擦写保存，按顺序存放数据，因而支持应用程序以 XIP(execute In Place，片内运行) 方式运行，在系统运行时, 节省 RAM 空间。我们一般拿其作为挂载根目录的文件系统 |
	| DevFS | 即设备文件系统，在 RT-Thread 操作系统中开启该功能后，可以将系统中的设备在 `/dev` 文件夹下虚拟成文件，使得设备可以按照文件的操作方式使用 read、write 等接口进行操作。 |
	| UFFS  | UFFS 是 Ultra-low-cost Flash File System（超低功耗的闪存文件系统）的简称。它是国人开发的、专为嵌入式设备等小内存环境中使用 Nand Flash 的开源文件系统。与嵌入式中常使用的 Yaffs 文件系统相比具有资源占用少、启动速度快、免费等优势。 |
	| NFS   | NFS 网络文件系统（Network File System）是一项在不同机器、不同操作系统之间通过网络共享文件的技术。在操作系统的开发调试阶段，可以利用该技术在主机上建立基于 NFS 的根文件系统，挂载到嵌入式设备上，可以很方便地修改根文件系统的内容。 |

	### POSIX接口层

	POSIX 表示可移植操作系统接口（Portable Operating System Interface of UNIX，缩写 POSIX），POSIX 标准定义了操作系统应该为应用程序提供的接口标准，是 IEEE 为要在各种 UNIX 操作系统上运行的软件而定义的一系列 API 标准的总称。

	> 文件描述符：`file descriptor`（fd），每一个文件描述符会与一个打开文件相对应，同时，不同的文件描述符也可能指向同一个文件。可以简单理解为它可以帮助我们找到我们需要的文件。
	> ![image-20240724224727730](C:\Users\Zero\AppData\Roaming\Typora\typora-user-images\image-20240724224727730.png)

	在文件系统中它提供了四个重要的接口：

	![文件管理常用函数](https://www.rt-thread.org/document/site/rt-thread-version/rt-thread-standard/programming-manual/filesystem/figures/fs-mg.png)

	还有一些其他常用的API：

	| API                                             | 描述         |
	| ----------------------------------------------- | ------------ |
	| int `rename`(const char *old, const char *new); | 文件重命名   |
	| int `stat`(const char *file, struct stat *buf); | 获取文件状态 |
	| int `unlink`(const char *pathname);             | 删除文件     |

	### 目录管理

	除了文件的管理之外我们还需要对目录进行管理，管理使用的API：

	![目录管理常用函数](https://www.rt-thread.org/document/site/rt-thread-version/rt-thread-standard/programming-manual/filesystem/figures/fs-dir-mg.png)

































