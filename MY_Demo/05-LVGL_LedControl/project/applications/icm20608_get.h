#ifndef __ICM20608_GET_H__
#define __ICM20608_GET_H__

#include <rtthread.h>
#include "icm20608.h"
#include <math.h>

typedef struct{
		float AX;
		float AY;
		float AZ;
		float GX;
		float GY;
		float GZ;
}param_imu;
 
typedef struct{
		float Pitch;
		float Roll;
		float Yaw;
}param_Angle;

#define Mohony_Kp      20.00f
#define Mohony_Ki      0.001f
#define cycle_T        0.005f      //200Hz
#define half_T         0.0025f
#define pi             3.1415926f


extern icm20608_device_t dev;
extern param_imu imu_data;
extern param_Angle imu_Angle;
extern rt_int16_t Ax, Ay, Az, Gx, Gy, Gz;


extern void timer_icm20608(void);










#endif
