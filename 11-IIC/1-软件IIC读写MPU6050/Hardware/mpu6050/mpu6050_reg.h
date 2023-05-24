# ifndef _MPU6050_REG_H
# define _MPU6050_REG_H

# define MPU6050_SMPLRT_DIV         0x19        // 采样率分频
# define MPU6050_CONFIG             0x1A        // 配置寄存器
# define MPU6050_GYRO_CONFIG        0x1B        // 陀螺仪配置寄存器
# define MPU6050_ACCEL_CONFIG       0x1C        // 加速度计计数器

/*加速度*/
# define MPU6050_ACCEL_XOUT_H       0x3B
# define MPU6050_ACCEL_XOUT_L       0x3C
# define MPU6050_ACCEL_YOUT_H       0x3D
# define MPU6050_ACCEL_YOUT_L       0x3E
# define MPU6050_ACCEL_ZOUT_H       0x3F
# define MPU6050_ACCEL_ZOUT_L       0x40
# define MPU6050_TEMP_OUT_H         0x41
# define MPU6050_TEMP_OUT_L         0x42
/*陀螺仪*/
# define MPU6050_GYRO_XOUT_H        0x43
# define MPU6050_GYRO_XOUT_L        0x44
# define MPU6050_GYRO_YOUT_H        0x45
# define MPU6050_GYRO_YOUT_L        0x46
# define MPU6050_GYRO_ZOUT_H        0x47
# define MPU6050_GYRO_ZOUT_L        0x48

# define MPU6050_PWR_WGMT_1         0x6B        // 电源管理寄存器1
# define MPU6050_PWR_WGMT_2         0x6C        // 电源管理寄存器2
# define MPU6050_WHO_AM_I           0x75        // 查看ID号

# endif /*MPU6050_REG_H*/
