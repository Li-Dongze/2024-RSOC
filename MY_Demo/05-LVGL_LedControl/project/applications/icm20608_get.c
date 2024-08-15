#include "icm20608_get.h"

icm20608_device_t dev = RT_NULL;

/*========================================================姿态解算算法================================================================*/
 
rt_int16_t Ax, Ay, Az, Gx, Gy, Gz;
param_imu imu_data;
param_Angle imu_Angle;
 
float q[4] = {1.0,0.0,0.0,0.0};
float exInt = 0.0,eyInt = 0.0,ezInt = 0.0;
 
float fast_sqrt(float x)
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long *) &y;
	i = 0x5f3759df - (i>>1);
	y = *(float *) &i;
	y = y * (1.5f-(halfx * y * y));
	return y;
}
 
void IMU_GetValues(void)
{
	// /* 读 取 三 轴 加 速 度 */
    // icm20608_get_accel(dev, &Ax, &Ay, &Az);

    // /* 读 取 三 轴 陀 螺 仪 */
    // icm20608_get_gyro(dev, &Gx, &Gy, &Gz);

	//Full Scale +-16 g
	imu_data.AX = ((float)Ax)*32/65536;
	imu_data.AY = ((float)Ay)*32/65536;
	imu_data.AZ = ((float)Az)*32/65536;
	//Full Scale +-2000 degree/s
	imu_data.GX = ((float)Gx)*4000/65536/180*pi;
	imu_data.GY = ((float)Gy)*4000/65536/180*pi;
	imu_data.GZ = ((float)Gz)*4000/65536/180*pi;
}
 
void IMU_AHRSupdate(param_imu* imu_temp)
{
	float ax,ay,az;
	float gx,gy,gz;
	float vx,vy,vz;
	float ex,ey,ez;
	ax = imu_temp->AX;
	ay = imu_temp->AY;
	az = imu_temp->AZ;
	gx = imu_temp->GX;
	gy = imu_temp->GY;
	gz = imu_temp->GZ;
	float q0 = q[0];
	float q1 = q[1];
	float q2 = q[2];
	float q3 = q[3];
	float norm = fast_sqrt(ax*ax+ay*ay+az*az);
	ax = ax * norm;
	ay = ay * norm;
	az = az * norm;
	vx = 2 * (q1*q3 - q0*q2);
	vy = 2 * (q2*q3 + q0*q1);
	vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;
	ex = ay*vz - az*vy;
	ey = az*vx - ax*vz;
	ez = ax*vy - ay*vx;
	exInt += Mohony_Ki * ex;
	eyInt += Mohony_Ki * ey;
	ezInt += Mohony_Ki * ez;
	gx += Mohony_Kp * ex + exInt;
	gy += Mohony_Kp * ey + eyInt;
	gz += Mohony_Kp * ez + ezInt;
	q0 += (-q1*gx-q2*gy-q3*gz) * half_T;
	q1 += ( q0*gx+q2*gz-q3*gy) * half_T;
	q2 += ( q0*gy-q1*gz+q3*gx) * half_T;
	q3 += ( q0*gz+q1*gy-q2*gx) * half_T;
	norm = fast_sqrt(q0*q0+q1*q1+q2*q2+q3*q3);
	q[0] = q0 * norm;
	q[1] = q1 * norm;
	q[2] = q2 * norm;
	q[3] = q3 * norm;
}
 
void IMU_getEuleranAngles(void)
{
	IMU_GetValues();
	IMU_AHRSupdate(&imu_data);
	imu_Angle.Pitch = asin(-2*q[1]*q[3]+2*q[0]*q[2])*180/pi;
	imu_Angle.Roll  = atan2(2*q[2]*q[3]+2*q[0]*q[1],-2*q[1]*q[1]-2*q[2]*q[2]+1)*180/pi;
	//If "imu_data.GZ" is too small, it is considered to be noise interference.(1 degree/s)
	if((imu_data.GZ*180/pi > 1.0f) || (imu_data.GZ*180/pi < -1.0f))
	{
		imu_Angle.Yaw  += imu_data.GZ*cycle_T*4*180/pi;
	}
}

/*================================================================================================================================*/

/* 定时器1回调函数 */
void timer5ms_icm20608GetAngle(void *parameter)
{
    IMU_getEuleranAngles();
	//rt_kprintf("roll: %.2f, pitch: %.2f, yaw: %.2f\n", imu_Angle.Roll, imu_Angle.Pitch, imu_Angle.Yaw);
}

/* 定时器的控制块 */
static rt_timer_t timer1;

void timer_icm20608(void)
{
    /* 创建定时器 1  周期定时器 */
    timer1 = rt_timer_create("timer1", timer5ms_icm20608GetAngle,
                             RT_NULL, 5,
                             RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);

    /* 启动定时器 1 */
    if (timer1 != RT_NULL) rt_timer_start(timer1);
}


int icm20608_start(void)
{
    const char *i2c_bus_name = "i2c2";
    rt_err_t result;

    rt_int16_t accel_x, accel_y, accel_z;

    rt_int16_t gyros_x, gyros_y, gyros_z;

    int count = 0;

    /* 初 始 化 icm20608 传 感 器 */
    dev = icm20608_init(i2c_bus_name);
    if (dev == RT_NULL)
    {
        rt_kprintf("The sensor initializes failure\n");
        return 0;
    }
    else
    {
        rt_kprintf("The sensor initializes success\n");
    }

    /* 对 icm20608 进 行 零 值 校 准： 采 样 10 次， 求 取 平 均 值 作 为 零 值 */
    result = icm20608_calib_level(dev, 10);
    if (result == RT_EOK)
    {
        rt_kprintf("The sensor calibrates success\n");
        rt_kprintf("accel_offset: X%6d Y%6d Z%6d\n", dev->accel_offset.x, dev->accel_offset.y, dev->accel_offset.z);
        rt_kprintf("gyro_offset : X%6d Y%6d Z%6d\n", dev->gyro_offset.x, dev->gyro_offset.y, dev->gyro_offset.z);
    }
    else
    {
        rt_kprintf("The sensor calibrates failure\n");
        icm20608_deinit(dev);
        return 0;
    }

    return 1;
}
INIT_DEVICE_EXPORT(icm20608_start);