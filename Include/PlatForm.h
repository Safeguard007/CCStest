#ifndef PLATFORM_H
#define PLATFORM_H

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "IQmathLib.h"
#include "DSP28x_Project.h"

#define DOF_V10   1
#define PI       (3.1415926)

///////////////////////////////////SPI FLASH定义区///////////////////////////////////
#define Enable_Reset              0x66                         //启用复位地址
#define Reset_Dev                 0x99                         //复位装置地址
#define Read_Data                 0x03                         //读取数据
#define Read_Status_Reg2          0x35                         //读取状态寄存器1
#define Read_Status_Reg1          0x05                         //读取状态寄存器2
#define Read_Status_Reg3          0x15                         //读取状态寄存器3
#define Enter_4B_Addr_Mode        0xB7
#define Write_Enable              0x06                         //写使能
#define Chip_Erase1               0xC7                         //芯片擦除
#define Sector_Erase              0x20                         //4K扇区擦除
#define Page_Program              0x02                         //页编程

#define Range_Addr                0x0000                       //用户设定运动范围FLASH存储首地址
#define Length_Addr               0x1000                       //用户设定各轴有效长度FLASH存储首地址


///////////////////////////////////LED灯控制定义//////////////////////////////////////
#ifdef DOF_V10
  	#define LED1_H     (GpioDataRegs.GPBSET.bit.GPIO53=1)      //设置GPIO53为高电平
    #define LED1_L     (GpioDataRegs.GPBCLEAR.bit.GPIO53=1)    //设置GPIO53为低电平
	#define LED2_H     (GpioDataRegs.GPASET.bit.GPIO15=1)      //设置GPIO60为高电平
    #define LED2_L     (GpioDataRegs.GPACLEAR.bit.GPIO15=1)    //设置GPIO60为低电平
	#define LED3_H     (GpioDataRegs.GPBSET.bit.GPIO34=1)      //设置GPIO61为高电平
    #define LED3_L     (GpioDataRegs.GPBCLEAR.bit.GPIO34=1)    //设置GPIO61为低电平

	#define GPIO1_OUT1     (GpioDataRegs.GPASET.bit.GPIO4=1)      //设置GPIO4为高电平
    #define GPIO1_OUT0     (GpioDataRegs.GPACLEAR.bit.GPIO4=1)    //设置GPIO4为低电平
	#define GPIO2_OUT1     (GpioDataRegs.GPASET.bit.GPIO5=1)      //设置GPIO5为高电平
    #define GPIO2_OUT0     (GpioDataRegs.GPACLEAR.bit.GPIO5=1)    //设置GPIO5为低电平
	#define GPIO3_OUT1     (GpioDataRegs.GPASET.bit.GPIO6=1)      //设置GPIO6为高电平
    #define GPIO3_OUT0     (GpioDataRegs.GPACLEAR.bit.GPIO6=1)    //设置GPIO6为低电平
	#define GPIO4_OUT1     (GpioDataRegs.GPASET.bit.GPIO7=1)      //设置GPIO7为高电平
    #define GPIO4_OUT0    (GpioDataRegs.GPACLEAR.bit.GPIO7=1)     //设置GPIO7为低电平
	#define GPIO5_OUT1     (GpioDataRegs.GPASET.bit.GPIO26=1)     //设置GPIO4为高电平
    #define GPIO5_OUT0     (GpioDataRegs.GPACLEAR.bit.GPIO26=1)    //设置GPIO4为低电平
	#define GPIO6_OUT1     (GpioDataRegs.GPASET.bit.GPIO27=1)      //设置GPIO5为高电平
    #define GPIO6_OUT0     (GpioDataRegs.GPACLEAR.bit.GPIO27=1)    //设置GPIO5为低电平
	#define GPIO7_OUT1     (GpioDataRegs.GPBSET.bit.GPIO32=1)      //设置GPIO6为高电平
    #define GPIO7_OUT0     (GpioDataRegs.GPBCLEAR.bit.GPIO32=1)    //设置GPIO6为低电平
	#define GPIO8_OUT1     (GpioDataRegs.GPBSET.bit.GPIO33=1)      //设置GPIO7为高电平
    #define GPIO8_OUT0    (GpioDataRegs.GPBCLEAR.bit.GPIO33=1)     //设置GPIO7为低电平
	#define GPIO9_OUT1     (GpioDataRegs.GPBSET.bit.GPIO48=1)     //设置GPIO4为高电平
    #define GPIO9_OUT0     (GpioDataRegs.GPBCLEAR.bit.GPIO48=1)    //设置GPIO4为低电平
	#define GPIO10_OUT1     (GpioDataRegs.GPBSET.bit.GPIO49=1)      //设置GPIO5为高电平
    #define GPIO10_OUT0     (GpioDataRegs.GPBCLEAR.bit.GPIO49=1)    //设置GPIO5为低电平
	#define GPIO11_OUT1     (GpioDataRegs.GPBSET.bit.GPIO50=1)      //设置GPIO6为高电平
    #define GPIO11_OUT0     (GpioDataRegs.GPBCLEAR.bit.GPIO50=1)    //设置GPIO6为低电平
	#define GPIO12_OUT1     (GpioDataRegs.GPBSET.bit.GPIO51=1)      //设置GPIO7为高电平
    #define GPIO12_OUT0    (GpioDataRegs.GPBCLEAR.bit.GPIO51=1)     //设置GPIO7为低电平

	#define SENSOR0     (GpioDataRegs.GPADAT.bit.GPIO0)     //设置GPIO0为高电平
	#define SENSOR1     (GpioDataRegs.GPADAT.bit.GPIO1)     //设置GPIO1为高电平
	#define SENSOR2     (GpioDataRegs.GPADAT.bit.GPIO2)     //设置GPIO2为高电平
	#define SENSOR3     (GpioDataRegs.GPADAT.bit.GPIO3)     //设置GPIO3为高电平
	#define SENSOR4     (GpioDataRegs.GPADAT.bit.GPIO11)     //设置GPIO0为高电平
	#define SENSOR5     (GpioDataRegs.GPADAT.bit.GPIO12)     //设置GPIO1为高电平
	#define SENSOR6     (GpioDataRegs.GPADAT.bit.GPIO13)     //设置GPIO2为高电平
	#define SENSOR7     (GpioDataRegs.GPADAT.bit.GPIO14)     //设置GPIO3为高电平
	#define SENSOR8     (GpioDataRegs.GPADAT.bit.GPIO22)     //设置GPIO0为高电平
	#define SENSOR9     (GpioDataRegs.GPADAT.bit.GPIO23)     //设置GPIO1为高电平
	#define SENSOR10    (GpioDataRegs.GPADAT.bit.GPIO24)     //设置GPIO2为高电平
	#define SENSOR11    (GpioDataRegs.GPADAT.bit.GPIO25)     //设置GPIO3为高电平

	#define XINT1       (GpioDataRegs.GPADAT.bit.GPIO8)     //设置GPIO0为高电平
	#define XINT2       (GpioDataRegs.GPADAT.bit.GPIO9)     //设置GPIO1为高电平
	#define XINT3       (GpioDataRegs.GPADAT.bit.GPIO10)     //设置GPIO2为高电平

#endif

////////////////////////////////////通信协议定义//////////////////////////////////////
//接收数据信息定义//
#define Cmd_Rx_Head       '$'      //接收的数据头
#define Cmd_Rx_End         0x0D    //接收的数据结束位
#define Cmd_Rx_Type       'H'      //接收的设备类型位，H代表机器人


#define Rx_Head_OK         0       //数据命令头状态在状态寄存器的位置
#define Rx_Long_OK         1       //数据命令长度状态在状态寄存器的位置
#define Rx_Type_OK         2       //数据命令对象状态在状态寄存器的位置
#define Rx_Num_OK          3       //数据命令类型状态在状态寄存器的位置
#define Rx_Buff_OK         4       //数据命令缓存区状态在状态寄存器的位置
#define Rx_Check_OK        5       //数据命令校验和状态在状态寄存器的位置
#define Rx_End_OK          6       //数据命令结束位状态在状态寄存器的位置
#define Rx_Message         7       //数据接收状态在状态寄存器的位置

#define Cmd_Max_Long      99       //接收数据的最大允许长度

//回复格式宏定义//
#define Cmd_Head_Bit       0       //头
#define Cmd_Long_Bit       1       //串口状态寄存器的长度值位
#define Cmd_Long_Num       2       //长度的个数
#define Cmd_Type_Bit       3       //数据类型位
#define Cmd_Fun_Bit        4       //数据功能位
#define Cmd_Buff_Bit       5       //数据信息位
#define Cmd_Check_Bit      6       //系统发送校验和起始位
 
////////////////////////////电机参数宏定义区/////////////////////////////
//电机运行控制函数参数
#define  X         (0x01)
#define  Y         (0x02)
#define  Z         (0x03)
#define  R         (0x04)
#define  XY        (0x05)
#define  ZR        (0x06)
#define  XYZR      (0x07)

//电机X的寄存器地址
#define  Motor_REG_MASK                  (0x0001)
#define  Motor_X_Clock_REG               (0x1100)
#define  Motor_X_CW_REG                  (0x1200)
#define  Motor_X_OE_REG                  (0x1300)
#define  Motor_X_Counter_REG             (0x1400)
#define  Motor_X_Capture_Mode_REG        (0x1500)
#define  Motor_X_Run_Counter_REG         (0x1600)

//电机Y的寄存器地址
#define  Motor_Y_Clock_REG               (0x2100)
#define  Motor_Y_CW_REG                  (0x2200)
#define  Motor_Y_OE_REG                  (0x2300)
#define  Motor_Y_Counter_REG             (0x2400)
#define  Motor_Y_Capture_Mode_REG        (0x2500)
#define  Motor_Y_Run_Counter_REG         (0x2600)

//电机Z的寄存器地址
#define  Motor_Z_Clock_REG               (0x3100)
#define  Motor_Z_CW_REG                  (0x3200)
#define  Motor_Z_OE_REG                  (0x3300)
#define  Motor_Z_Counter_REG             (0x3400)
#define  Motor_Z_Capture_Mode_REG        (0x3500)
#define  Motor_Z_Run_Counter_REG         (0x3600)

//电机R的寄存器地址
#define  Motor_R_Clock_REG               (0x4100)
#define  Motor_R_CW_REG                  (0x4200)
#define  Motor_R_OE_REG                  (0x4300)
#define  Motor_R_Counter_REG             (0x4400)
#define  Motor_R_Capture_Mode_REG        (0x4500)
//#define  Motor_R_Run_Counter_REG       (0x4600)
#define  Motor_R_Origin                  (0x4600)

#define  Motor_Run                       (0x0001)
#define  Motor_Stop                 	 (0x0000)

/////////////////////////////传感器定义区///////////////////////////////////
#define  Motor_X_Run_Left             	 (0x0001)
#define  Motor_X_Run_Right            	 (0x0000)

#define  Motor_Y_Run_Left             	 (0x0001)
#define  Motor_Y_Run_Right            	 (0x0000)

#define  Motor_Z_Run_Down             	 (0x0001)
#define  Motor_Z_Run_Up            	     (0x0000)

#define  Motor_R_Run_Left             	 (0x0001)
#define  Motor_R_Run_Right            	 (0x0000)

#define  Motor_Cap_Mode             	 (0x0001)
#define  Motor_Qep_Mode             	 (0x0000)

#define  Motor_Status_REG           	 (0x0100)

#define  Motor_X_Status_Mask        	 (0x0003)
#define  Motor_X_Left_ON            	 (0x0002)
#define  Motor_X_Right_ON           	 (0x0001)
#define  Motor_X_Run                	 (0x0003)
#define  Motor_X_Stop               	 (0x0000)

#define  Motor_Y_Status_Mask             (0x000C)
#define  Motor_Y_Left_ON                 (0x0008)
#define  Motor_Y_Right_ON                (0x0004)
#define  Motor_Y_Run                     (0x000C)
#define  Motor_Y_Stop                    (0x0000)

#define  Motor_Z_Status_Mask        	 (0x0030)   //2016.8.10
//#define  Motor_Z_Left_ON            	 (0x0010)
#define  Motor_Z_Left_ON            	 (0x0020)   //2016.8.10
//#define  Motor_Z_Right_ON           	 (0x0020)
#define  Motor_Z_Right_ON           	 (0x0010)
#define  Motor_Z_Run                	 (0x0030)
#define  Motor_Z_Stop               	 (0x0000)

#define  Motor_R_Status_Mask             (0x00C0)
#define  Motor_R_Left_ON                 (0x0040)
#define  Motor_R_Right_ON                (0x0080)
#define  Motor_R_Run                     (0x00C0)
#define  Motor_R_Stop                    (0x0000)
#define  Motor_R_Origin_On               (0x0001)
#define  Motor_R_Origin_OFF              (0x0000)

///////////////////机器人机械运动范围定义区（根据机械本体定义）///////////////////
#define max_x    140.00                  //X轴可运行最大角度
#define min_x   -140.00                  //X轴可运行最小角度
#define max_y    135.00                  //Y轴可运行最大角度
#define min_y   -135.00                  //Y轴可运行最小角度
#define max_z    100.00                  //Z轴可运行最大距离
#define min_z    0.00                    //Z轴可运行最小距离
#define max_r    360.00                  //R轴可运行最大角度
#define min_r   -360.00                  //R轴可运行最小角度

/******************************************结构体定义区域*******************************************/
//数据接收通信格式定义
typedef struct
    {
     unsigned char Cmd_Head;             //头
     unsigned char Cmd_Long[2];          //数据长度
     unsigned char Cmd_Type;             //设备类型
     unsigned char Cmd_Fun;              //功能位
     unsigned char Cmd_Buff[99];         //坐标值
     unsigned char Cmd_Check[4];         //校验和
     unsigned char Cmd_End;              //尾
    }SCI_Cmd_TypeDef;

//数据发送格式定义
typedef struct
    {
     unsigned char Cmd_Head;             //头
     unsigned char Cmd_Long[2];          //数据长度
     unsigned char Cmd_Type;             //设备类型
     unsigned char Cmd_Fun;              //功能位
     unsigned char Cmd_Buff;             //坐标值
     unsigned char Cmd_Check[4];         //校验和
     unsigned char Cmd_End;              //尾
    }SCI_TX_Type;

//串口数据定义
typedef struct
    {
	 unsigned char Tx_Flag;              //发送标志位
	 unsigned char Tx_Counter;           //发送数据计数
	 unsigned char Tx_Buff[99];          //发送缓存区
	 unsigned char Rx_FLag;              //接收标志位
	 unsigned char Rx_Status;            //接收状态
	 unsigned char Rx_Counter;           //接收数据计数
	 unsigned char Rx_Counter_T;         //转换成以零为首计数的形式
	 unsigned char Rx_Message_Long;      //接收数据包的长度，从长度高位到结束位
	 unsigned char Rx_Buff[99];          //接收缓存区
	 unsigned char Temp;
	 int           Check_Value;
	 unsigned char Check_Buff[4];
    }SCI_Data_TypeDef;

//运动范围格式定义
typedef struct
    {
     float Max_XS;                        //一轴最大角度
     float Min_XS;                        //一轴最小角度
     float Max_YL;                        //二轴最大角度
     float Min_YL;                        //二轴最小角度
     float Max_ZU;                        //三轴最大角度
     float Min_ZU;                        //三轴最小角度
     float Max_RR;                        //四轴最大角度
     float Min_RR;                        //四轴最小角度
     float Max_BB;                        //五轴最大角度
     float Min_BB;                        //五轴最小角度
     float Max_TT;                        //六轴最大角度
     float Min_TT;                        //六轴最小角度
    }Robot_RANGE_Type;

//各轴的运行范围结构体定义（用于SCARA机器人参数存储与计算）
typedef struct
    {
     float Max_x;
     float Min_x;
     float Max_y;
     float Min_y;
     float Max_z;
     float Min_z;
     float Max_r;
     float Min_r;
    }AXIS_RANGE_Type;
//运动范围格式定义
typedef struct
    {
     float Arm_XS;                       //一轴有效长度
     float Arm_YL;                       //二轴有效长度
     float Arm_ZU;                       //三轴有效长度
     float Arm_RR;                       //四轴有效长度
     float Arm_BB;                       //五轴有效长度
     float Arm_TT;                       //六轴有效长度
    }DH_Parameters_Type;

//FPGA控制电机运行信息格式定义
typedef struct
    {
     unsigned char Axis;                 //电机运行的轴数

     unsigned char Dir_X;                //X轴电机运行方向
     unsigned long Freq_X;               //X轴电机运行速度
     unsigned long Num_X;                //X轴电机运行脉冲数

     unsigned char Dir_Y;                //Y轴电机运行方向
     unsigned long Freq_Y;               //Y轴电机运行速度
     unsigned long Num_Y;                //Y轴电机运行脉冲数

     unsigned char Dir_Z;                //Z轴电机运行方向
     unsigned long Freq_Z;               //Z轴电机运行速度
     unsigned long Num_Z;                //Z轴电机运行脉冲数

     unsigned char Dir_R;                //R轴电机运行方向
     unsigned long Freq_R;               //R轴电机运行速度
     unsigned long Num_R;                //R轴电机运行脉冲数

     unsigned int  Run_Index;            //插补序号
    }FPGA_Run_Info_Type;

//轨迹规划电机运行的信息格式定义
typedef struct
    {
   	 unsigned char Axis;                 //电机运行的轴数

   	 unsigned char Dir_X;                //X轴运动方向
   	 float         Vel_X;                //X轴运动速度
     float         Ang_X;                //X轴运动角度

   	 unsigned char Dir_Y;                //Y轴运动方向
   	 float         Vel_Y;                //Y轴运动速度
   	 float         Ang_Y;                //Y轴运动角度

   	 unsigned char Dir_Z;                //Z轴运动方向
   	 float         Vel_Z;                //Z轴运动速度
   	 float         Ang_Z;                //Z轴运动角度

   	 unsigned char Dir_R;                //R轴运动方向
   	 float         Vel_R;                //R轴运动速度
   	 float         Ang_R;                //R轴运动角度

   	 unsigned int  Run_Index;            //插补序号
    }Motor_Run_Info_Type;

typedef struct
    {
     unsigned int XS_Angle;
     unsigned int YL_Angle;
     unsigned int ZU_Angle;
     unsigned int RR_Angle;
     unsigned int BB_Angle;
     unsigned int TT_Angle;
    }THETA_TypeDef;

//电机运行状态格式定义
typedef struct
    {
     unsigned char Robot_Rx_CMD_Reg;     //系统运行的命令 不包括查询命令
     unsigned char Robot_BK_Reg;         //系统各个电机的刹车状态
     unsigned char Robot_Run_Reg;        //0x00 代表系统运动中  0x01代表系统为空闲状态 0x02代表系统异常结束
     unsigned int  Robot_Cal_Reg;        //各轴运动空间计算空间范围状态，是否在空间范围内
     unsigned int  Robot_Motor_Reg;      //各个电机的运动状态
     THETA_TypeDef Robot_Theta_Reg;
    }ROBOT_STATUS_REGS_TypeDef;

//SCARA机器人算法相关参数
typedef struct
    {
     float arm_one;                      //大臂长度
     float arm_two;                      //小臂长度
     AXIS_RANGE_Type axis_range;         //运动范围
    }SCARA_ARM_Type;

//直角坐标格式定义（均为角度和距离值）
typedef struct
    {
     float Descartes_X;                  //X轴直角坐标（角度）
     float Descartes_Y;                  //Y轴直角坐标（角度）
     float Descartes_Z;                  //Z轴直角坐标（角度）
     float Descartes_R;                  //R轴直角坐标（角度）
    }Descartes_Point_Type;

//直角坐标格式定义（均为角度和距离值）
typedef struct
    {
     float Descartes_XS;                 //X轴直角坐标（角度）
     float Descartes_YL;                 //Y轴直角坐标（角度）
     float Descartes_ZU;                 //Z轴直角坐标（角度）
     float Descartes_RR;                 //R轴直角坐标（角度）
     float Descartes_BB;                 //B轴直角坐标（角度）
     float Descartes_TT;                 //T轴直角坐标（角度）
    }Robot_Descartes_Point_Type;

//关节空间坐标 当前坐标和上一个坐标值
typedef struct
    {
     float theta_x_pre;
     float theta_y_pre;
     float theta_z_pre;
     float theta_r_pre;

     float theta_x_now;
     float theta_y_now;
     float theta_z_now;
     float theta_r_now;
    }THETA_JOINT_Type;

//笛卡尔坐标 当前坐标和上一个坐标值
typedef struct
    {
     float x_pre;
     float y_pre;
     float z_pre;
     float r_pre;

     float x_now;
     float y_now;
     float z_now;
     float r_now;
    }POSE_DECARE_Type;
//////////////////////////////////28335系统函数声明区域//////////////////////////////////
extern void P_Led_Init(void);                    //LED初始化
extern void P_Gpio_Init(void);                   //GPIO初始化
extern void P_UartA_Init(void);                  //串口A初始化
extern void P_UartC_Init(void);                  //串口C初始化
extern void Spi_FIFO_Init(void);                 //SPI FiFO初始化
extern void Spi_Init(void);                      //SPI初始化
extern void P_Board_Init(void);                  //系统配置信息初始化

extern void SCIA_Data_Int(void);                 //串口A数据初始化
extern void SCIC_Data_Int(void);                 //串口C数据初始化
extern unsigned char SCIA_Tx(unsigned char*Send_Buff,unsigned int Send_Long);       //串口A数据发送
extern unsigned char SCIC_Tx(unsigned char*Send_Buff,unsigned int Send_Long);       //串口C数据发送

extern void Spi_Send(Uint16 txdata);             //SPI数据发送
extern Uint16 Spi_Rece(void);                    //SPI数据接收
extern void w25q256_reset(void);                 //w25q256 Flash芯片复位
extern Uint16 w25q256_read_reg1(void);           //读取FLASH寄存器1
extern Uint16 w25q256_read_reg2(void);           //读取FLASH寄存器2
extern Uint16 w25q256_read_reg3(void);           //读取FLASH寄存器3
extern void w25q256_set_4addr(void);             //设置成4字节地址模式
extern void w25q256_init(void);                  //w25q256 Flash芯片初始化
extern Uint32 w25q256_readid(void);              //读取Flash ID
extern void w25q256_write_enable(void);          //FLASH写使能
extern Uint16 w25q256_test_busy(void);           //FLASH检测忙
extern void w25q256_erase_chip(void);            //FLASH芯片擦除
extern void w25q256_erase_sector(Uint32 addr);   //FLASH擦除扇区4K
extern void w25q256_read(Uint16 *tar_data, Uint32 addr, Uint32 n); //addr地址开始连续读N个字节
extern void w25q256_write(Uint16 *sou_data, Uint32 addr, Uint16 n);//向addr地址开始连续写N个字节

extern unsigned char Str_To_Int(unsigned char *Str);                                //字符串转换长度函数
extern unsigned int Check_Char_To_Int(unsigned char *Str);                          //校验和字符串转换成校验和数值函数
extern unsigned int Get_Check_Num(unsigned char *Str,unsigned char Check_Long);     //计算校验和函数
extern unsigned char Check_Int_To_Char(unsigned char Check_Int,unsigned char *Str); //校验和转换成字符串函数

extern void Motor_X_Set(unsigned long Freq, unsigned char Dir, unsigned long Num);    //X电机参数设置函数
extern void Motor_Y_Set(unsigned long Freq, unsigned char Dir, unsigned long Num);    //Y电机参数设置函数
extern void Motor_Z_Set(unsigned long Freq, unsigned char Dir, unsigned long Num);    //Z电机参数设置函数
extern void Motor_R_Set(unsigned long Freq, unsigned char Dir, unsigned long Num);    //R电机参数设置函数
extern void Motor_B_Set(unsigned long Freq, unsigned char Dir, unsigned long Num);    //Z电机参数设置函数
extern void Motor_T_Set(unsigned long Freq, unsigned char Dir, unsigned long Num);    //R电机参数设置函数

extern long long int Motor_X_Abs_Read();         //X轴读编码器函数
extern long long int Motor_Y_Abs_Read();         //Y轴读编码器函数
extern long long int Motor_Z_Abs_Read();         //Z轴读编码器函数
extern long long int Motor_R_Abs_Read();         //R轴读编码器函数
extern long long int Motor_B_Abs_Read();         //Z轴读编码器函数
extern long long int Motor_T_Abs_Read();         //R轴读编码器函数
extern unsigned int Motor_Return_State ();       //返回电机状态函数
extern void Motor_Set_EN (unsigned int Motor_EN);
extern void Motor_X_AbsReset_Set();
extern void Motor_Y_AbsReset_Set();
extern void Motor_Z_AbsReset_Set();
extern void Motor_R_AbsReset_Set();
extern void Motor_B_AbsReset_Set();
extern void Motor_T_AbsReset_Set();
extern int BJ_X_Read();
extern int BJ_Y_Read();
extern int BJ_Z_Read();
extern int BJ_R_Read();
extern int BJ_B_Read();
extern int BJ_T_Read();
extern void delay_loop();                                                           //延时5毫秒
extern void Delay(void);                                                            //833纳秒
extern void My_Nop(void);                                                           //大概延时100纳秒
extern void Delay_s(unsigned char Delay_Time);                                      //延时1秒
extern void Delay_ms(unsigned char Delay_Time);                                     //延时1毫秒

////////////////////////////////全局变量声明区域///////////////////////////////////
extern SCI_Data_TypeDef   SCIA_Data;                 //串口A数据定义
extern SCI_Data_TypeDef   SCIC_Data;                 //串口C数据定义
extern SCI_TX_Type  SCIA_Tx_Message;                 //串口A数据发送
extern SCI_TX_Type  SCIC_Tx_Message;                 //串口C数据发送
extern ROBOT_STATUS_REGS_TypeDef Robot_Run_Reg;      //各轴电机运行信息的寄存器
extern Robot_RANGE_Type * User_Range;                //用户设定运动范围定义
extern float  User_Range_Buff[12];                   //运动范围数据缓冲区定义
extern unsigned char User_Range_Str[72];             //接收用户设定运动范围字符串存储
extern unsigned char  RAMCS[10];                       //RAMceshi
extern DH_Parameters_Type * Robot_DH;                //臂长定义
extern float  Robot_DH_Buff[6];                      //臂长缓冲区定义
extern unsigned char Robot_DH_Str[30];               //接收DH参数字符串
extern float Speed_Percent;                          //整体运行速度比例
extern unsigned char Speed_Percent_Str[3];           //整体运行速度比例字符串
extern unsigned char CESHI[100] ;
extern unsigned char CESHIR[100] ;
extern unsigned int CESHIF[100] ;
extern THETA_JOINT_Type SCARA_Run_Theta;             //SCARA关节空间坐标定义
extern FPGA_Run_Info_Type Trajetory_points;          //直角坐标运动运动参数
extern Motor_Run_Info_Type Motor_Run_points;         //轨迹规划电机参数定义
extern unsigned char  Auxiliary_Fun;                 //串口处理函数中辅助功能位
extern SCI_Cmd_TypeDef *SCI_CMD_Message;             //串口处理后的数据
extern SCI_Cmd_TypeDef SCI_CMD_Message1;             //串口处理后的数据
extern int Cmd_Tx_Long;                              //中断发送长度
extern unsigned char Execute_Flag;                   //指令执行标志位
extern unsigned int AC;
extern SCARA_ARM_Type SCARA_DH;                      //SCARA机器人DH参数
extern POSE_DECARE_Type SCARA_Decare;                //运动坐标转换笛卡尔信息
extern unsigned char Answer_Flag;                    //用于信息存储时串口指令回复标志
extern Robot_Descartes_Point_Type Now_Point;         //测试位置点定义

//绝对值位置使能寄存器地址
extern Uint16 * AbsX_Encoder1_ADD;
extern Uint16 * AbsX_Encoder2_ADD;
extern Uint16 * AbsX_Encoder3_ADD;
extern Uint16 * AbsX_Encoder4_ADD;
extern Uint16 * AbsX_Encoder5_ADD;
extern Uint16 * AbsX_Encoder6_ADD;
extern Uint16 * AbsX_Encoder7_ADD;
extern Uint16 * AbsX_Encoder8_ADD;
extern Uint16 * AbsY_Encoder1_ADD;
extern Uint16 * AbsY_Encoder2_ADD;
extern Uint16 * AbsY_Encoder3_ADD;
extern Uint16 * AbsY_Encoder4_ADD;
extern Uint16 * AbsY_Encoder5_ADD;
extern Uint16 * AbsY_Encoder6_ADD;
extern Uint16 * AbsY_Encoder7_ADD;
extern Uint16 * AbsY_Encoder8_ADD;
extern Uint16 * AbsZ_Encoder1_ADD;
extern Uint16 * AbsZ_Encoder2_ADD;
extern Uint16 * AbsZ_Encoder3_ADD;
extern Uint16 * AbsZ_Encoder4_ADD;
extern Uint16 * AbsZ_Encoder5_ADD;
extern Uint16 * AbsZ_Encoder6_ADD;
extern Uint16 * AbsZ_Encoder7_ADD;
extern Uint16 * AbsZ_Encoder8_ADD;
extern Uint16 * AbsR_Encoder1_ADD;
extern Uint16 * AbsR_Encoder2_ADD;
extern Uint16 * AbsR_Encoder3_ADD;
extern Uint16 * AbsR_Encoder4_ADD;
extern Uint16 * AbsR_Encoder5_ADD;
extern Uint16 * AbsR_Encoder6_ADD;
extern Uint16 * AbsR_Encoder7_ADD;
extern Uint16 * AbsR_Encoder8_ADD;
extern Uint16 * AbsB_Encoder1_ADD;
extern Uint16 * AbsB_Encoder2_ADD;
extern Uint16 * AbsB_Encoder3_ADD;
extern Uint16 * AbsB_Encoder4_ADD;
extern Uint16 * AbsB_Encoder5_ADD;
extern Uint16 * AbsB_Encoder6_ADD;
extern Uint16 * AbsB_Encoder7_ADD;
extern Uint16 * AbsB_Encoder8_ADD;
extern Uint16 * AbsT_Encoder1_ADD;
extern Uint16 * AbsT_Encoder2_ADD;
extern Uint16 * AbsT_Encoder3_ADD;
extern Uint16 * AbsT_Encoder4_ADD;
extern Uint16 * AbsT_Encoder5_ADD;
extern Uint16 * AbsT_Encoder6_ADD;
extern Uint16 * AbsT_Encoder7_ADD;
extern Uint16 * AbsT_Encoder8_ADD;
extern Uint16 * FreqX_ADD;
extern Uint16 * FreqY_ADD;
extern Uint16 * NumX_ADD;
extern Uint16 * NumY_ADD;
extern Uint16 * FreqX_ADD1;
extern Uint16 * FreqY_ADD1;
extern Uint16 * NumX_ADD1;
extern Uint16 * NumY_ADD1;

extern Uint16 * FreqZ_ADD;
extern Uint16 * FreqR_ADD;
extern Uint16 * NumZ_ADD;
extern Uint16 * NumR_ADD;
extern Uint16 * FreqZ_ADD1;
extern Uint16 * FreqR_ADD1;
extern Uint16 * NumZ_ADD1;
extern Uint16 * NumR_ADD1;

extern Uint16 * FreqB_ADD;
extern Uint16 * FreqT_ADD;
extern Uint16 * NumB_ADD;
extern Uint16 * NumT_ADD;
extern Uint16 * FreqB_ADD1;
extern Uint16 * FreqT_ADD1;
extern Uint16 * NumB_ADD1;
extern Uint16 * NumT_ADD1;
extern Uint16 * EN_ADD;
extern Uint16 * State_ADD;
extern Uint16 * SN;
extern Uint16 * test;
extern Uint16 * BJ123;
extern Uint16 * BJ456;
extern Uint16 * DIRVER_ENX_ADD;
extern Uint16 * DIRVER_ENY_ADD;
extern Uint16 * DIRVER_ENZ_ADD;
extern Uint16 * DIRVER_ENR_ADD;
extern Uint16 * DIRVER_ENB_ADD;
extern Uint16 * DIRVER_ENT_ADD;
extern Uint16 * ACC1;
extern Uint16 * ACC2;
extern Uint16 * ACC3;
extern Uint16 * ACC4;
extern Uint16 * ACC5;
extern Uint16 * ACC6;
#endif
