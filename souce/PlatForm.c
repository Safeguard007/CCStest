#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP28x_Project.h" 
#include "PlatForm.h"
#include "control.h"
#include "math.h"
#include "DSP2833x_GlobalPrototypes.h"

/***********************全局变量定义区**************************/
#pragma DATA_SECTION(SCIA_Data, "ZONE7DATA");
        SCI_Data_TypeDef SCIA_Data;                     //串口A数据定义
#pragma DATA_SECTION(SCIC_Data, "ZONE7DATA");
        SCI_Data_TypeDef SCIC_Data;                     //串口C数据定义

#pragma DATA_SECTION(SCIA_Tx_Message, "ZONE7DATA");
        SCI_TX_Type SCIA_Tx_Message;                    //串口A数据发送定义
#pragma DATA_SECTION(SCIC_Tx_Message, "ZONE7DATA");
        SCI_TX_Type SCIC_Tx_Message;                    //串口C数据发送定义

#pragma DATA_SECTION(SCI_CMD_Message,"ZONE7DATA");
        SCI_Cmd_TypeDef  *SCI_CMD_Message;              //根据通信协议结构体强制转换信息定义
#pragma DATA_SECTION(SCI_CMD_Message,"ZONE7DATA");
        SCI_Cmd_TypeDef SCI_CMD_Message1;               //根据通信协议结构体强制转换信息定义（用于提取辅助功能位数据）

#pragma DATA_SECTION(Cmd_Tx_Long,"ZONE7DATA");
        int Cmd_Tx_Long;                                //中断发送模式下发送字符串的长度值定义

#pragma DATA_SECTION(Auxiliary_Fun,"ZONE7DATA");
        unsigned char  Auxiliary_Fun;                   //串口处理函数中辅助功能位（根据通信协议设定）
#pragma DATA_SECTION(Answer_Flag,"ZONE7DATA");
        unsigned char Answer_Flag;                      //用于信息存储时串口指令回复标志（用于FLASH初始化时只对信息存储不需信息回复）
#pragma DATA_SECTION(Execute_Flag,"ZONE7DATA");
        unsigned char Execute_Flag;                     //指令执行标志位（用于在接收校验码错误的指令情况下，只对指令进行处理而不执行）
#pragma DATA_SECTION(AC,"ZONE7DATA");
        unsigned int AC;                     //AC串口标志位
#pragma DATA_SECTION(User_Range, "ZONE7DATA");
        Robot_RANGE_Type * User_Range;                  //运动范围定义
#pragma DATA_SECTION(User_Range_Buff, "ZONE7DATA");
        float User_Range_Buff[12];                      //用户设定运动范围数据缓冲区定义
#pragma DATA_SECTION(User_Range_Str, "ZONE7DATA");
        unsigned char User_Range_Str[72];               //用户设定运动范围字符串存储
#pragma DATA_SECTION(RAMCS, "ZONE7DATA");
        unsigned char RAMCS[10];               //ceshi RAM zhuanyong
#pragma DATA_SECTION(CESHI, "ZONE7DATA");
        unsigned char CESHI[100] ;              //CESHI
#pragma DATA_SECTION(CESHIR, "ZONE7DATA");
        unsigned char CESHIR[100] ;              //CESHIR
#pragma DATA_SECTION(CESHIF, "ZONE7DATA");
        unsigned int CESHIF[100] ;              //CESHIF

#pragma DATA_SECTION(Robot_Run_Reg,"ZONE7DATA");
        ROBOT_STATUS_REGS_TypeDef Robot_Run_Reg;        //定义一个系统各轴电机运行信息的寄存器

#pragma DATA_SECTION(SCARA_Run_Theta,"ZONE7DATA");
        THETA_JOINT_Type SCARA_Run_Theta;               //关节空间坐标定义（弧度制）

#pragma DATA_SECTION(Trajetory_points,"ZONE7DATA");
        FPGA_Run_Info_Type Trajetory_points;            //FPGA控制电机参数定义

#pragma DATA_SECTION(Motor_Run_points,"ZONE7DATA");
        Motor_Run_Info_Type Motor_Run_points;           //轨迹规划电机参数定义

/***********************全局变量电机控制地址区**************************/
Uint16 * test = (Uint16 *)0x100195;                     //使能地址
Uint16 * BJ123 = (Uint16 *)0x100182;                 //J1.J2.J3报警地址
Uint16 * BJ456 = (Uint16 *)0x100184;                   //J4.J5.J6报警地址
//X轴电机
Uint16 * FreqX_ADD = (Uint16 *)0x100000;                //一轴电机频率寄存器地址
Uint16 * FreqX_ADD1 = (Uint16 *)0x100191;
Uint16 * NumX_ADD = (Uint16 *)0x100001;                 //一轴电机PWM脉冲个数寄存器地址1
Uint16 * NumX_ADD1 = (Uint16 *)0x100185;                //一轴电机PWM脉冲个数寄存器地址2
Uint16 * DirX_ADD = (Uint16 *)0x100002;                 //一轴电机方向寄存器地址
Uint16 * DIRVER_ENX_ADD = (Uint16 *)0x100003;           //一轴电机驱动器信息写入寄存器地址
Uint16 * PulsX_Warn_ADD = (Uint16 *)0x100004;           //脉冲错误报警寄存器地址
Uint16 * PulsX_Bias_ADD = (Uint16 *)0x100005;           //脉冲偏差寄存器地址
Uint16 * AbsX_Reset_ADD = (Uint16 *)0x100006;           //绝对值编码器清零指令寄存器地址
Uint16 * AbsX_Encoder1_ADD = (Uint16 *)0x100007;        //绝对值位置使能寄存器地址
Uint16 * AbsX_Encoder2_ADD = (Uint16 *)0x100008;
Uint16 * AbsX_Encoder3_ADD = (Uint16 *)0x100009;
Uint16 * AbsX_Encoder4_ADD = (Uint16 *)0x10000a;
Uint16 * AbsX_Encoder5_ADD = (Uint16 *)0x10000f;
Uint16 * AbsX_Encoder6_ADD = (Uint16 *)0x10000c;
Uint16 * AbsX_Encoder7_ADD = (Uint16 *)0x10000d;
Uint16 * AbsX_Encoder8_ADD = (Uint16 *)0x10000e;

//Y轴电机
Uint16 * FreqY_ADD = (Uint16 *)0x100040;                //电机频率寄存器地址
Uint16 * FreqY_ADD1 = (Uint16 *)0x100192;
Uint16 * NumY_ADD = (Uint16 *)0x100041;                 //电机PWM脉冲个数寄存器地址1
Uint16 * NumY_ADD1 = (Uint16 *)0x100186;                //电机PWM脉冲个数寄存器地址2
Uint16 * DirY_ADD = (Uint16 *)0x100042;                 //电机方向寄存器地址
Uint16 * DIRVER_ENY_ADD = (Uint16 *)0x100043;           //电机驱动器信息写入寄存器地址
Uint16 * PulsY_Warn_ADD = (Uint16 *)0x100044;           //脉冲错误报警寄存器地址
Uint16 * PulsY_Bias_ADD = (Uint16 *)0x100045;           //脉冲偏差寄存器地址
Uint16 * AbsY_Reset_ADD = (Uint16 *)0x100046;           //绝对值编码器清零指令寄存器地址
Uint16 * AbsY_Encoder1_ADD = (Uint16 *)0x100047;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsY_Encoder2_ADD = (Uint16 *)0x100048;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsY_Encoder3_ADD = (Uint16 *)0x100049;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsY_Encoder4_ADD = (Uint16 *)0x10004a;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsY_Encoder5_ADD = (Uint16 *)0x10004f;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsY_Encoder6_ADD = (Uint16 *)0x10004c;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsY_Encoder7_ADD = (Uint16 *)0x10004d;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsY_Encoder8_ADD = (Uint16 *)0x10004e;        //绝对值编码器位置信息寄存器地址

//Z轴电机
Uint16 * FreqZ_ADD = (Uint16 *)0x100080;                //电机频率寄存器地址
Uint16 * FreqZ_ADD1 = (Uint16 *)0x100193;
Uint16 * NumZ_ADD = (Uint16 *)0x100081;                 //电机PWM脉冲个数寄存器地址1
Uint16 * NumZ_ADD1 = (Uint16 *)0x100187;                //电机PWM脉冲个数寄存器地址2
Uint16 * DirZ_ADD = (Uint16 *)0x100082;                 //电机方向寄存器地址
Uint16 * DIRVER_ENZ_ADD = (Uint16 *)0x100083;           //电机驱动器信息写入寄存器地址
Uint16 * PulsZ_Warn_ADD = (Uint16 *)0x100084;           //脉冲错误报警寄存器地址
Uint16 * PulsZ_Bias_ADD = (Uint16 *)0x100085;           //脉冲偏差寄存器地址
Uint16 * AbsZ_Reset_ADD = (Uint16 *)0x100086;           //绝对值编码器清零指令寄存器地址
Uint16 * AbsZ_Encoder1_ADD = (Uint16 *)0x100087;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsZ_Encoder2_ADD = (Uint16 *)0x100088;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsZ_Encoder3_ADD = (Uint16 *)0x100089;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsZ_Encoder4_ADD = (Uint16 *)0x10008a;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsZ_Encoder5_ADD = (Uint16 *)0x10008f;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsZ_Encoder6_ADD = (Uint16 *)0x10008c;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsZ_Encoder7_ADD = (Uint16 *)0x10008d;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsZ_Encoder8_ADD = (Uint16 *)0x10008e;        //绝对值编码器位置信息寄存器地址

//R轴电机
Uint16 * FreqR_ADD = (Uint16 *)0x1000C0;                //电机频率寄存器地址
Uint16 * FreqR_ADD1 = (Uint16 *)0x100194;
Uint16 * NumR_ADD = (Uint16 *)0x1000C1;                 //电机PWM脉冲个数寄存器地址1
Uint16 * NumR_ADD1 = (Uint16 *)0x100188;                //电机PWM脉冲个数寄存器地址2
Uint16 * DirR_ADD = (Uint16 *)0x1000C2;                 //电机方向寄存器地址
Uint16 * DIRVER_ENR_ADD = (Uint16 *)0x1000C3;           //电机驱动器信息写入寄存器地址
Uint16 * PulsR_Warn_ADD = (Uint16 *)0x1000C4;           //脉冲错误报警寄存器地址
Uint16 * PulsR_Bias_ADD = (Uint16 *)0x1000C5;           //脉冲偏差寄存器地址
Uint16 * AbsR_Reset_ADD = (Uint16 *)0x1000C6;           //绝对值编码器清零指令寄存器地址
Uint16 * AbsR_Encoder1_ADD = (Uint16 *)0x1000C7;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsR_Encoder2_ADD = (Uint16 *)0x1000C8;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsR_Encoder3_ADD = (Uint16 *)0x1000C9;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsR_Encoder4_ADD = (Uint16 *)0x1000Ca;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsR_Encoder5_ADD = (Uint16 *)0x1000Cf;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsR_Encoder6_ADD = (Uint16 *)0x1000Cc;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsR_Encoder7_ADD = (Uint16 *)0x1000Cd;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsR_Encoder8_ADD = (Uint16 *)0x1000Ce;        //绝对值编码器位置信息寄存器地址
//B轴电机
Uint16 * FreqB_ADD = (Uint16 *)0x100100;                //电机频率寄存器地址
Uint16 * FreqB_ADD1 = (Uint16 *)0x100195;
Uint16 * NumB_ADD = (Uint16 *)0x100101;                 //电机PWM脉冲个数寄存器地址1
Uint16 * NumB_ADD1 = (Uint16 *)0x100189;                //电机PWM脉冲个数寄存器地址2
Uint16 * DirB_ADD = (Uint16 *)0x100102;                 //电机方向寄存器地址
Uint16 * DIRVER_ENB_ADD = (Uint16 *)0x100103;           //电机驱动器信息写入寄存器地址
Uint16 * PulsB_Warn_ADD = (Uint16 *)0x100104;           //脉冲错误报警寄存器地址
Uint16 * PulsB_Bias_ADD = (Uint16 *)0x100105;           //脉冲偏差寄存器地址
Uint16 * AbsB_Reset_ADD = (Uint16 *)0x100106;           //绝对值编码器清零指令寄存器地址
Uint16 * AbsB_Encoder1_ADD = (Uint16 *)0x100107;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsB_Encoder2_ADD = (Uint16 *)0x100108;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsB_Encoder3_ADD = (Uint16 *)0x100109;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsB_Encoder4_ADD = (Uint16 *)0x10010a;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsB_Encoder5_ADD = (Uint16 *)0x10010f;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsB_Encoder6_ADD = (Uint16 *)0x10010c;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsB_Encoder7_ADD = (Uint16 *)0x10010d;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsB_Encoder8_ADD = (Uint16 *)0x10010e;        //绝对值编码器位置信息寄存器地址

Uint16 * FreqT_ADD = (Uint16 *)0x100140;                //电机频率寄存器地址
Uint16 * FreqT_ADD1 = (Uint16 *)0x100196;
Uint16 * NumT_ADD = (Uint16 *)0x100141;                 //电机PWM脉冲个数寄存器地址1
Uint16 * NumT_ADD1 = (Uint16 *)0x100190;                //电机PWM脉冲个数寄存器地址2
Uint16 * DirT_ADD = (Uint16 *)0x100142;                 //电机方向寄存器地址
Uint16 * DIRVER_ENT_ADD = (Uint16 *)0x100143;           //电机驱动器信息写入寄存器地址
Uint16 * PulsT_Warn_ADD = (Uint16 *)0x100144;           //脉冲错误报警寄存器地址
Uint16 * PulsT_Bias_ADD = (Uint16 *)0x100145;           //脉冲偏差寄存器地址
Uint16 * AbsT_Reset_ADD = (Uint16 *)0x100146;           //绝对值编码器清零指令寄存器地址
Uint16 * AbsT_Encoder1_ADD = (Uint16 *)0x100147;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsT_Encoder2_ADD = (Uint16 *)0x100148;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsT_Encoder3_ADD = (Uint16 *)0x100149;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsT_Encoder4_ADD = (Uint16 *)0x10014a;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsT_Encoder5_ADD = (Uint16 *)0x10014f;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsT_Encoder6_ADD = (Uint16 *)0x10014c;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsT_Encoder7_ADD = (Uint16 *)0x10014d;        //绝对值编码器位置信息寄存器地址
Uint16 * AbsT_Encoder8_ADD = (Uint16 *)0x10014e;        //绝对值编码器位置信息寄存器地址
//公共信息部分
Uint16 * EN_ADD = (Uint16 *)0x100180;                   //电机使能寄存器地址
Uint16 * State_ADD = (Uint16 *)0x100181;                //电机运行状态寄存器地址
Uint16 * SN = (Uint16 *)0x100198;
Uint16 * ACC1 = (Uint16 *)0x100199;                      //加速度
Uint16 * ACC2 = (Uint16 *)0x100012;
Uint16 * ACC3 = (Uint16 *)0x100013;
Uint16 * ACC4 = (Uint16 *)0x100014;
Uint16 * ACC5 = (Uint16 *)0x100015;
Uint16 * ACC6 = (Uint16 *)0x100016;
/*******************************************28335系统初始化区域*************************************************/
/********************28335系统初始化区域************************/
/************************************************************
* 函数名称：P_Gpio_Init()
* 创建日期：2016.5.13
* 创    建：王震霖/九安医疗设备开发一室
* 描    述：管脚定义
* 参    数：
* 返 回 值：
* 全局变量：
*-----------------------------------------------------------
-----------------------------------------------------------*
* 版本信息
* 版本.           日期             创建               描述
*************************************************************/
void P_Gpio_Init(void)
{
    EALLOW;
    #ifdef DOF_V10
///////////////////////LED灯管脚配置///////////////////////////
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;      //设置GPIO53为通用的I/O  CPU_RUN
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = 1;       //配置GPIO53为通用输出口

    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;      //设置GPIO15为通用的I/O  CPU_RUN
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;       //配置GPIO15为通用输出口

    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;      //设置GPIO34为通用的I/O  CPU_RUN
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;       //配置GPIO34为通用输出口

///////////////////////中断IO管脚配置///////////////////////////
/*
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;      //设置GPIO8为通用的I/O
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;       //配置GPIO8为通用输入口
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO8 = 0;     //GPIO时钟和系统时钟一样且支持GPIO
    GpioIntRegs.GPIOXNMISEL.bit.GPIOSEL = 8; //NMI中断选择GPIO
    XIntruptRegs.XNMICR.bit.POLARITY = 0;    //触发模式为下降沿触发
    XIntruptRegs.XNMICR.bit.ENABLE = 1;      //使能中断

    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;      //设置GPIO9为通用的I/O
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;       //配置GPIO9为通用输入口
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 0;
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 9;
    XIntruptRegs.XINT1CR.bit.POLARITY = 0;
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;      //设置GPIO10为通用的I/O
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;       //配置GPIO10为通用输入口
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO10 = 0;
    GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 10;
    XIntruptRegs.XINT2CR.bit.POLARITY = 0;
    XIntruptRegs.XINT2CR.bit.ENABLE = 1;
*/
///////////////////////输入电路管脚配置///////////////////////////
     GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;      //设置GPIO0为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;       //配置GPIO0为通用输入口
     GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;      //设置GPIO1为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;       //配置GPIO1为通用输入口
     GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;      //设置GPIO2为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;       //配置GPIO2为通用输入口
     GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;      //设置GPIO3为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO3= 0;       //配置GPIO3为通用输入口
     GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;      //设置GPIO0为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;       //配置GPIO0为通用输入口
     GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;      //设置GPIO1为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;       //配置GPIO1为通用输入口
     GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;      //设置GPIO2为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;       //配置GPIO2为通用输入口
     GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;      //设置GPIO3为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO14= 0;       //配置GPIO3为通用输入口
     GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;

     GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;      //设置GPIO0为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;       //配置GPIO0为通用输入口
     GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;

     GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;      //设置GPIO1为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;       //配置GPIO1为通用输入口
     GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;

     GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;      //设置GPIO2为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;       //配置GPIO2为通用输入口
     GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;

     GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;      //设置GPIO3为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO25= 0;       //配置GPIO3为通用输入口
     GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;

///////////////////////使能管脚配置///////////////////////////
     GpioCtrlRegs.GPBMUX2.bit.GPIO59= 0;      //设置GPIO59为通用的I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO59 = 1;       //配置GPIO59为通用输出口

     GpioCtrlRegs.GPBMUX2.bit.GPIO60= 0;      //设置GPIO60为通用的I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1;       //配置GPIO60为通用输出口

     GpioCtrlRegs.GPBMUX2.bit.GPIO61= 0;      //设置GPIO61为通用的I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;       //配置GPIO61为通用输出口
///////////////////////输出电路管脚配置///////////////////////////
     GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;      //设置GPIO4为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;       //配置GPIO4为通用输出口

     GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;      //设置GPIO5为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;       //配置GPIO5为通用输出口

     GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;      //设置GPIO6为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;       //配置GPIO6为通用输出口

     GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;      //设置GPIO7为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO7= 1;       //配置GPIO7为通用输出口

     GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;      //设置GPIO4为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO26 = 1;       //配置GPIO4为通用输出口

     GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;      //设置GPIO5为通用的I/O
     GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;       //配置GPIO5为通用输出口

     GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;      //设置GPIO6为通用的I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;       //配置GPIO6为通用输出口

     GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;      //设置GPIO7为通用的I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO33= 1;       //配置GPIO7为通用输出口

     GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;      //设置GPIO4为通用的I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;       //配置GPIO4为通用输出口

     GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;      //设置GPIO5为通用的I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1;       //配置GPIO5为通用输出口

     GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;      //设置GPIO6为通用的I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;       //配置GPIO6为通用输出口

     GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;      //设置GPIO7为通用的I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO51= 1;       //配置GPIO7为通用输出口
//////////////////////SCIA引脚配置/////////////////////////////
    GpioCtrlRegs.GPBPUD.bit.GPIO35 = 0;       //使能GPIO35（SCITXDA）内部上拉功能
    GpioCtrlRegs.GPBPUD.bit.GPIO36 = 0;       //使能GPIO36（SCIRXDA）内部上拉功能
    GpioCtrlRegs.GPBQSEL1.bit.GPIO35 = 3;     //管脚定义为异步输出
    GpioCtrlRegs.GPBQSEL1.bit.GPIO36 = 3;     //管脚定义为异步输入
    GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 1;      //配置GPIO35  为 SCITXDA引脚
    GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 1;      //配置GPIO36  为 SCIRXDA引脚

//////////////////////SCIC引脚配置/////////////////////////////
    GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0;       //使能GPIO62（SCIRXDC）内部上拉功能
    GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;       //使能GPIO63（SCITXDC）内部上拉功能
    GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = 3;     //管脚定义为异步输入
    GpioCtrlRegs.GPBQSEL2.bit.GPIO63 = 3;     //管脚定义为异步输出
    GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 1;      //配置GPIO62  为 SCIRXDA引脚
    GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 1;      //配置GPIO63  为 SCITXDA引脚

////////////////////////////////spi引脚配置////////////////////////////////
    GpioCtrlRegs.GPBPUD.bit.GPIO54 = 0;       // 内部上拉GPIO54 (SPISIMOA)
    GpioCtrlRegs.GPBPUD.bit.GPIO55 = 0;       // 内部上拉GPIO55 (SPISOMIA)
    GpioCtrlRegs.GPBPUD.bit.GPIO56 = 0;       // 内部上拉GPIO56 (SPICLKA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3;     // 异步输出GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3;     // 异步输出GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3;     // 异步输出GPIO18 (SPICLKA)
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1;      // 配置功能为GPIO54 as SPISIMOA
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1;      // 配置功能为GPIO55 as SPISOMIA
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1;      // 配置功能为GPIO56 as SPICLKA

////////////////////////////////flash引脚配置////////////////////////////////
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0x00;   //引脚功能选择为通用GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0x01;    //GPIO方向设置输出
    GpioDataRegs.GPBSET.bit.GPIO58 = 0x01;    //输出高，FLASH复位引脚低电平复位
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0x00;   //引脚功能选择为通用GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO57 = 0x01;    //GPIO方向设置输出
    GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;    //输出高，FLASH复位引脚低电平复位
	#endif
    EDIS;
}
/************************************************************
* 函数名称：P_Led_Init
* 输入参数：无
* 输出参数：无
* 功       能：LED灯初始化，在初始状态时LED灯为亮
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/	
void P_Led_Init(void)
{
  	EALLOW;
	#ifdef DOF_V10

	LED1_L;             //初始为低电平，灯亮
	LED2_L;             //初始为低电平，灯亮
	LED3_L;             //初始为低电平，灯亮

	GpioDataRegs.GPBSET.bit.GPIO59=1;
	GpioDataRegs.GPBSET.bit.GPIO60=1;
	GpioDataRegs.GPBSET.bit.GPIO61=1;
/*
	GpioDataRegs.GPBCLEAR.bit.GPIO59=1;
	GpioDataRegs.GPBCLEAR.bit.GPIO60=1;
	GpioDataRegs.GPBCLEAR.bit.GPIO61=1;
*/
	GPIO1_OUT0;             //GPO初始化输出为低电平
	GPIO2_OUT0;             //GPO初始化输出为低电平
	GPIO3_OUT0;             //GPO初始化输出为低电平
	GPIO4_OUT0;             //GPO初始化输出为低电平
	GPIO5_OUT0;             //GPO初始化输出为低电平
	GPIO6_OUT0;             //GPO初始化输出为低电平
	GPIO7_OUT0;             //GPO初始化输出为低电平
	GPIO8_OUT0;             //GPO初始化输出为低电平
	GPIO9_OUT0;             //GPO初始化输出为低电平
	GPIO10_OUT0;             //GPO初始化输出为低电平
	GPIO11_OUT0;             //GPO初始化输出为低电平
	GPIO12_OUT0;             //GPO初始化输出为低电平
	#endif
    EDIS;
}
/************************************************************
* 函数名称：P_UartA_Init
* 输入参数：无
* 输出参数：无
* 功       能：串口A初始化
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void P_UartA_Init(void)
{
	EALLOW;

	SciaRegs.SCICCR.bit.STOPBITS=0;        //1位停止位
	SciaRegs.SCICCR.bit.PARITYENA=0;       //禁止极性功能
	SciaRegs.SCICCR.bit.LOOPBKENA=0;       //禁止回送测试模式功能
	SciaRegs.SCICCR.bit.ADDRIDLE_MODE=0;   //空闲线模式
	SciaRegs.SCICCR.bit.SCICHAR=7;         //8位数据位

	SciaRegs.SCIHBAUD = 0x0001;
    SciaRegs.SCILBAUD = 0x00E7;            //波特率为9600
	
	SciaRegs.SCICTL1.bit.TXENA=1;          //SCIA模块的发送使能
	SciaRegs.SCICTL1.bit.RXENA=1;          //SCIA模块的接收使能
	SciaRegs.SCICTL2.bit.RXBKINTENA=1;     //SCIA模块接收中断使能
	SciaRegs.SCICTL2.bit.TXINTENA=1;       //SCIA模块发送中断使能
	SciaRegs.SCICTL1.bit.SWRESET=1;        //重启SCI


	EDIS;
}
/************************************************************
* 函数名称：P_UartC_Init
* 输入参数：无
* 输出参数：无
* 功       能：串口C初始化
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void P_UartC_Init(void)
{
    EALLOW;
	ScicRegs.SCICCR.all = 0x0007;          //1位停止位，禁止极性功能，禁止回送测试模式功能，空闲线模式，8位数据位
	ScicRegs.SCICTL1.all = 0x0003;         //SCIC模块接收/发送使能
	ScicRegs.SCICTL2.bit.TXINTENA  = 1;    //SCIC模块发送中断使能
	ScicRegs.SCICTL2.bit.RXBKINTENA = 1;   //SCIC模块接收中断使能
	ScicRegs.SCIHBAUD = 0x0001;
	ScicRegs.SCILBAUD = 0x00E7;            //波特率为9600
	ScicRegs.SCICTL1.bit.SWRESET = 0x01;   //重启SCI
	EDIS;
}

/************************************************************
* 函数名称：spi_fifo_init()
* 输入参数：无
* 输出参数：无
* 功       能：SPI fifo初始化
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Spi_FIFO_Init(void)
{
	EALLOW;
    SpiaRegs.SPIFFTX.all=0xE040;
    SpiaRegs.SPIFFRX.all=0x204f;
    SpiaRegs.SPIFFCT.all=0x0;
    EDIS;
}

/************************************************************
* 函数名称：Spi_Init
* 输入参数：无
* 输出参数：无
* 功       能：SPI初始化
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Spi_Init(void)
{
	EALLOW;
	SpiaRegs.SPICCR.all =0x000F;	             // Reset on, rising edge, 16-bit char bits
	SpiaRegs.SPICTL.all =0x0006;    		     // Enable master mode, normal phase,
                                                 // enable talk, and SPI int disabled.
	SpiaRegs.SPIBRR =0x007F;
    SpiaRegs.SPICCR.all =0x009F;		         // Relinquish SPI from Reset
    SpiaRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission
////////////////////////////////SPI配置寄存器CCR////////////////////////////////
	SpiaRegs.SPICCR.bit.SPISWRESET = 0x0;        //SPI复位
	SpiaRegs.SPICCR.bit.CLKPOLARITY = 0x00;	     //设置时钟极性， 0为数据在上升沿输出且在下降沿输入，1为数据在下降沿输出且在上升沿输入
	SpiaRegs.SPICCR.bit.SPILBK = 0x0;	         //自测模式设置 ，0为禁止自测模式，1为自测模式使能
	SpiaRegs.SPICCR.bit.SPICHAR = 0X07;	         //数据传输宽度设置0~15
////////////////////////////////SPI配置寄存器CTL////////////////////////////////
	SpiaRegs.SPICTL.bit.OVERRUNINTENA = 0x0;     //接收数据溢出中断使能，1-使能，0-禁止
	SpiaRegs.SPICTL.bit.CLK_PHASE = 0x01;        //设置时钟相位，0-正常，1-SPICLK信号延时半个周期
	SpiaRegs.SPICTL.bit.MASTER_SLAVE = 0x01;     //SPI主从模式选择，0-从机，1-主机
	SpiaRegs.SPICTL.bit.TALK = 0x01;             //SPI主从发送使能，0-禁止发送，1-使能发送，保证使能SPISTE引脚
	SpiaRegs.SPICTL.bit.SPIINTENA = 0x00;	     //SPI中断使能，0-禁止中断，1-使能中断
////////////////////////////////SPI波特率寄存器BRR////////////////////////////////
	SpiaRegs.SPIBRR = 0x0063;                    //SPIBRR =0,1,2时，波特率=SPICLK/4 SPIBRR =3~127时，波特率=SPICLK/（SPIBRR+1）
	SpiaRegs.SPICCR.bit.SPISWRESET = 0x1;        //准备开始发送和接收数据
    SpiaRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission
    EDIS;
}
/************************************************************
* 函数名称：P_Board_Init
* 输入参数：无
* 输出参数：无
* 功       能：系统初始化
* 备       注：包括IO引脚，功能和中断的初始化
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void P_Board_Init(void)
{
    InitSysCtrl();                       //系统时钟初始化
	DINT;                                //关闭系统中断
	IER = 0x0000;                        //禁止CPU中断
	IFR = 0x0000;                        //清除CPU中断标志
	InitPieCtrl();                       //初始化PIE控制寄存器
	InitPieVectTable();                  //初始化PIE中断向量表
    MemCopy(&RamfuncsLoadStart,&RamfuncsLoadEnd,&RamfuncsRunStart);  //flash烧写时需要
    InitFlash();                         //flash烧写时需要
	EnableInterrupts();                  //中断初始化
    P_Gpio_Init();                       //GPIO初始化
    InitXintf16Gpio();                   //外扩RAM I/O初始化
	P_Led_Init();                        //LED 初始化
	InitXintf();                         //外扩RAM初始化
	P_UartA_Init();	                     //串口A功能初始化
	P_UartC_Init();                      //串口C功能初始化
	Spi_Init();                          //SPI初始化
	Spi_FIFO_Init();                     //SPI FIFO初始化
	w25q256_init();                      //Flash初始化

	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
	PieCtrlRegs.PIEIER9.bit.INTx1=1;     // PIE Group 9, INT1  SCIA的中断
	PieCtrlRegs.PIEIER9.bit.INTx2=1;     // PIE Group 9, INT2

	PieCtrlRegs.PIEIER8.bit.INTx5=1;     // PIE Group 8, INT5  SCIC的中断
	PieCtrlRegs.PIEIER8.bit.INTx6=1;     // PIE Group 8, INT6

	PieCtrlRegs.PIEIER1.bit.INTx4=1;     // PIE Group 1, INT4      外部中断
	PieCtrlRegs.PIEIER1.bit.INTx5=1;     // PIE Group 1, INT5
	IER|= M_INT1;
	IER|= M_INT8;
	IER|= M_INT9;
	IER = 0x181;                         //开CPU中断
    EINT;                                //开全局中断
    ERTM;                                //开全局实时中断
}
/************************************************************
* 函数名称：Str_To_Int
* 输入参数：数据接收长度字符串
* 输出参数：长度数据
* 功       能：针对接收到的长度字符串转换成长度数据
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
unsigned char Str_To_Int(unsigned char *Str)
{
    unsigned char Str_Int=0x00, i, j;
    unsigned char Str_Buff[] = "0123456789ABCDEF";
    unsigned char Str_Cov_Buff[2] = {0x00,0x00};

    for(j=0;j<2;j++)                     //将接收长度字符串转换成数值
    {
   	    for(i=0;i<16;i++)
   		{
     		if(Str_Buff[i] == Str[j])
     		{
     			Str_Cov_Buff[j] = i;
     		}
   		}
    }
    Str_Int = Str_Cov_Buff[0] * 10 + Str_Cov_Buff[1];   //根据对应位置定义计算长度值
	return Str_Int;
}
/************************************************************
* 函数名称：Get_Check_Num
* 输入参数：校验和计算字符串，字符串长度
* 输出参数：检验和数值
* 功       能：计算校验和
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
unsigned int Get_Check_Num(unsigned char *Str,unsigned char Check_Long)
{
	unsigned int Check_Num = 0x00;
	unsigned char i;
	for(i=0;i<Check_Long;i++)
	{
		Check_Num += *Str++;
	}
	return Check_Num;
}
/************************************************************
* 函数名称：Check_Char_To_Int
* 输入参数：校验和字符串
* 输出参数：检验和数值
* 功       能：接收到的校验和字符串转换成校验和数值
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
unsigned int Check_Char_To_Int(unsigned char *Str)
{
    unsigned int Check_Int = 0x00, i, j;
    unsigned char Str_Buff[] = "0123456789ABCDEF";
    unsigned char Str_Cov_Buff[4] = {0x00,0x00,0x00,0x00};

    for(j=0;j<4;j++)
    {
   	    for(i=0;i<16;i++)
   	    {
            if(Str_Buff[i] == Str[j])
		    {
			    Str_Cov_Buff[j] = i;
		    }
   	    }
    }
    for(i=0;i<4;i++)
    {
	    Check_Int = (Check_Int<<4) | (Str_Cov_Buff[i]);
    }
    return Check_Int;
}
/************************************************************
* 函数名称：Check_Int_To_Char
* 输入参数：校验和数值
* 输出参数：检验和字符串
* 功       能：将校验和转换为字符串
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
unsigned char Check_Int_To_Char(unsigned char Check_Int,unsigned char *Str)
{
    unsigned char Str_Buff[] = "0123456789ABCDEF";

    Str[0] = Str_Buff[((Check_Int >> 12) & 0x000F)];
    Str[1] = Str_Buff[((Check_Int >> 8) & 0x000F)];
    Str[2] = Str_Buff[((Check_Int >> 4) & 0x000F)];
    Str[3] = Str_Buff[((Check_Int) & 0x000F)];
    return 1;
}
/************************************************************
* 函数名称：SCIA_Data_Int
* 输入参数：无
* 输出参数：无
* 功       能：SCIA数据初始化
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void SCIA_Data_Int(void)
{
    unsigned char *Spr;
	unsigned char i = 0;

	Spr = &SCIA_Data.Tx_Flag;     //指针起始位为Tx_Flag
	for(i=0;i<211;i++)            //将寄存器里的所有位都赋值为0
	{
		*Spr++ = 0x00;
	}
}
/************************************************************
* 函数名称：SCIC_Data_Int
* 输入参数：无
* 输出参数：无
* 功       能：SCIC数据初始化
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void SCIC_Data_Int(void)
{
    unsigned char *Spr;
	unsigned char i = 0;

	Spr = &SCIC_Data.Tx_Flag;      //指针起始位为Tx_Flag
	for(i=0;i<211;i++)             //将寄存器里的所有位都赋值为0
	{
		*Spr++ = 0x00;
	}
}
/************************************************************
* 函数名称：SCIA_Tx
* 输入参数：发送字符串数据，发送字符串长度
* 输出参数：无
* 功       能：串口A数据查询发送
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
unsigned char SCIA_Tx(unsigned char *Send_Buff,unsigned int Send_Long)
{
    unsigned char i;
    unsigned int j;

    for(i=0;i<Send_Long;i++)
    {
        SciaRegs.SCITXBUF = Send_Buff[i];        //发送字符串赋值给发送寄存器
        while(SciaRegs.SCICTL2.bit.TXRDY != 1)   //判断发送标志位是否为1
        {
        	;
        }
	    for(j=0;j<10000;j++)
	    {
	    	;
	    }
    }
    for(j=0;j<10000;j++)
    {
    	;
    }
    return 1;
}
/************************************************************
* 函数名称：SCIC_Tx
* 输入参数：发送字符串数据，发送字符串长度
* 输出参数：无
* 功       能：串口C数据查询发送
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
unsigned char SCIC_Tx(unsigned char*Send_Buff,unsigned int Send_Long)
{
    unsigned char i;
    unsigned int j;
    for(i=0;i<Send_Long;i++)
    {
        ScicRegs.SCITXBUF = Send_Buff[i];        //发送字符串赋值给发送寄存器
        while(ScicRegs.SCICTL2.bit.TXRDY != 1)   //判断发送标志位是否为1
        {
        	;
        }
	    for(j=0;j<10000;j++)
	    {
	    	;
	    }
    }
    for(j=0;j<10000;j++)
    {
    	;
    }
    return 1;
}

/************************************************************
* 函数名称：Motor_X_Set
* 输入参数：运行频率，运行方向，脉冲数
* 输出参数：无
* 功       能：设置电机参数，写入寄存器，并使能OE
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Motor_X_Set(unsigned long Freq, unsigned char Dir, unsigned long Num)
{
	*EN_ADD = 0;                        //电机使能赋值为0
	*ACC1 = 0x000a;
   	*FreqX_ADD = Freq>>16;              //设置频率
   	*FreqX_ADD1 = Freq;
   	*NumX_ADD1 = Num;
	*NumX_ADD = Num>>16;                //设置脉冲数
    *DirX_ADD = Dir;                    //设置运行方向
    *DIRVER_ENX_ADD = 0x0001;           //设置驱动器信息写入寄存器
}
/************************************************************
* 函数名称：Motor_Y_Set
* 输入参数：运行频率，运行方向，脉冲数
* 输出参数：无
* 功       能：设置电机参数，写入寄存器，并使能OE
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Motor_Y_Set(unsigned long Freq, unsigned char Dir, unsigned long Num)
{
	*EN_ADD = 0;
	*ACC2 = 0x000a;
   	*FreqY_ADD = Freq>>16;              //设置频率
   	*FreqY_ADD1 = Freq;
   	*NumY_ADD = Num>>16;                //设置运行的脉冲数
   	*NumY_ADD1 = Num;
    *DirY_ADD = Dir;                    //设置运行方向
    *DIRVER_ENY_ADD = 0x0001;           //设置驱动器信息写入寄存器
}
/************************************************************
* 函数名称：Motor_Z_Set
* 输入参数：运行频率，运行方向，脉冲数
* 输出参数：无
* 功       能：设置电机参数，写入寄存器，并使能OE
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Motor_Z_Set(unsigned long Freq, unsigned char Dir, unsigned long Num)
{
	*EN_ADD = 0;
	*ACC3 = 0x000a;
   	*FreqZ_ADD = Freq>>16;              //设置频率
   	*FreqZ_ADD1 = Freq;
    *DirZ_ADD = Dir;                    //设置运行方向
    *NumZ_ADD = Num>>16;                //设置运行的脉冲数
    *NumZ_ADD1 = Num;
    *DIRVER_ENZ_ADD = 0x0001;           //设置驱动器信息写入寄存器
}
/************************************************************
* 函数名称：Motor_R_Set
* 输入参数：运行频率，运行方向，脉冲数
* 输出参数：无
* 功       能：设置电机参数，写入寄存器，并使能OE
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Motor_R_Set(unsigned long Freq, unsigned char Dir, unsigned long Num)
{
	*EN_ADD = 0;
	*ACC4 = 0x000a;
   	*FreqR_ADD = Freq>>16;              //设置频率
   	*FreqR_ADD1 = Freq;
    *DirR_ADD = Dir;                    //设置运行方向
    *NumR_ADD = Num>>16;                //设置运行的脉冲数
    *NumR_ADD1 = Num;
    *DIRVER_ENR_ADD = 0x0001;           //设置驱动器信息写入寄存器
}
/************************************************************
* 函数名称：Motor_B_Set
* 输入参数：运行频率，运行方向，脉冲数
* 输出参数：无
* 功       能：设置电机参数，写入寄存器，并使能OE
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Motor_B_Set(unsigned long Freq, unsigned char Dir, unsigned long Num)
{
	*EN_ADD = 0;
	*ACC5 = 0x000a;
   	*FreqB_ADD = Freq>>16;              //设置频率
   	*FreqB_ADD1 = Freq;
    *DirB_ADD = Dir;                    //设置运行方向
    *NumB_ADD = Num>>16;                //设置运行的脉冲数
    *NumB_ADD1 = Num;
    *DIRVER_ENB_ADD = 0x0001;           //设置驱动器信息写入寄存器
}
/************************************************************
* 函数名称：Motor_T_Set
* 输入参数：运行频率，运行方向，脉冲数
* 输出参数：无
* 功       能：设置电机参数，写入寄存器，并使能OE
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Motor_T_Set(unsigned long Freq, unsigned char Dir, unsigned long Num)
{
	*EN_ADD = 0;
	*ACC6 = 0x000a;
   	*FreqT_ADD = Freq>>16;              //设置频率
   	*FreqT_ADD1 = Freq;
    *DirT_ADD = Dir;                    //设置运行方向
    *NumT_ADD = Num>>16;                //设置运行的脉冲数
    *NumT_ADD1 = Num;
    *DIRVER_ENT_ADD = 0x0001;           //设置驱动器信息写入寄存器
}
/************************************************************
* 函数名称：BJ_X_Read()
* 创建日期：2016.10.11
* 创       建：王朔/九安医疗设备开发一室
* 描       述：X轴电机报警信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
int BJ_X_Read()
{
	int A;
	int B;
	A = * BJ123;
	B = 0X7;
	A = A&B;
	return A;
}
/************************************************************
* 函数名称：BJ_Y_Read()
* 创建日期：2016.10.11
* 创       建：王朔/九安医疗设备开发一室
* 描       述：Y轴电机报警信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
int BJ_Y_Read()
{
	int A;
	int B;
	A =  * BJ123;
	B = 0X38;
	A = A&B;
	A = A>>3;
	return A;
}
/************************************************************
* 函数名称：BJ_Z_Read()
* 创建日期：2016.10.11
* 创       建：王朔/九安医疗设备开发一室
* 描       述：Z轴电机报警信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
int BJ_Z_Read()
{
	int A;
	int B;
	A = * BJ123;
	B = 0X160;
	A = A&B;
	A = A>>6;
	return A;
}
/************************************************************
* 函数名称：BJ_R_Read()
* 创建日期：2016.10.11
* 创       建：王朔/九安医疗设备开发一室
* 描       述：R轴电机报警信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
int BJ_R_Read()
{
	int A;
	int B;
	A = * BJ456;
	B = 0X7;
	A = A&B;
	return A;
}

/************************************************************
* 函数名称：BJ_B_Read()
* 创建日期：2016.10.11
* 创       建：王朔/九安医疗设备开发一室
* 描       述：B轴电机报警信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
int BJ_B_Read()
{
	int A;
	int B;
	A =  * BJ456;
	B = 0X38;
	A = A&B;
	A = A>>3;
	return A;
}
/************************************************************
* 函数名称：BJ_T_Read()
* 创建日期：2016.10.11
* 创       建：王朔/九安医疗设备开发一室
* 描       述：T轴电机报警信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
int BJ_T_Read()
{
	int A;
	int B;
	A = * BJ456;
	B = 0X160;
	A = A&B;
	A = A>>6;
	return A;
}
/************************************************************
* 函数名称：Motor_X_Abs_Read()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：X轴电机绝对值编码器使能和信息寄存器信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
long long int Motor_X_Abs_Read()
{
	volatile  long long int A;     //绝对值编码器位置信息寄存器
	volatile  long long int B;
	volatile  long long int C;

	while(1)
	{
	    A = * AbsX_Encoder2_ADD;
	    Delay_ms(5);
	    if(A == * AbsX_Encoder2_ADD)
	    {
	    	break;
	    }
	}
	while(1)
	{
	    A = * AbsX_Encoder1_ADD;
	    Delay_ms(55);
	    if(A == * AbsX_Encoder1_ADD)
	    {
	     	break;
	    }
	}
	A = 0;
	B = 0;
	B = * AbsX_Encoder8_ADD;
    A = B<<5;
	B = * AbsX_Encoder7_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsX_Encoder6_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsX_Encoder5_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsX_Encoder4_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsX_Encoder3_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsX_Encoder2_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsX_Encoder1_ADD;
	A = A|B;
	C = A;
	B = A>>32;
	B = B&0X01;
	if(B == 0)
	{
		A = C;
	}
	if(B == 1)
	{
	    C = ~C+1;
	    A = C&0XFFFFFFFF;
	    A = 0-A;
	}
	return A;
}

/************************************************************
* 函数名称：Motor_Y_Abs_Read()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：Y轴电机绝对值编码器使能和信息寄存器信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*-----------------------------------------------------------
-----------------------------------------------------------*
* 版本信息
* 版本.           日期             创建               描述
* v.1           2016.08.26
*************************************************************/
long long int Motor_Y_Abs_Read()
{
	volatile  long long int A;     //绝对值编码器位置信息寄存器
	volatile  long long int B;
	volatile  long long int C;

	while(1)
	{
	    A = * AbsY_Encoder2_ADD;
	    Delay_ms(5);
	    if(A == * AbsY_Encoder2_ADD)
	    {
	    	break;
	    }
	}
	while(1)
	{
	    A = * AbsY_Encoder1_ADD;
	    Delay_ms(55);
	    if(A == * AbsY_Encoder1_ADD)
	    {
	     	break;
	    }
	}
	A = 0;
	B = 0;
	B = * AbsY_Encoder8_ADD;
    A = B<<5;
	B = * AbsY_Encoder7_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsY_Encoder6_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsY_Encoder5_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsY_Encoder4_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsY_Encoder3_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsY_Encoder2_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsY_Encoder1_ADD;
	A = A|B;
	C = A;
	B = A>>32;
	B = B&0X01;
	if(B == 0)
	{
		A = C;
	}
	if(B == 1)
	{
	    C = ~C+1;
	    A = C&0XFFFFFFFF;
	    A = 0-A;
	}
	return A;
}
/************************************************************
* 函数名称：Motor_Z_Abs_Read()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：Z轴电机绝对值编码器使能和信息寄存器信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*-----------------------------------------------------------
-----------------------------------------------------------*
* 版本信息
* 版本.           日期             创建               描述
* v.1           2016.08.26
*************************************************************/
long long int Motor_Z_Abs_Read()
{
	volatile  long long int B;
	volatile  long long int A;     //绝对值编码器位置信息寄存器
	volatile  long long int C;

	while(1)
	{
	    A=* AbsZ_Encoder2_ADD;
	    Delay_ms(1);
	    if(A==* AbsZ_Encoder2_ADD)
	    {
	    	break;
	    }
	}
	while(1)
	{
	    A=* AbsZ_Encoder1_ADD;
	   	Delay_ms(1);
	   	if(A==* AbsZ_Encoder1_ADD)
	   	{
	   	    break;
	   	}
	}
	A=0;
	B=0;
    B = * AbsZ_Encoder8_ADD;
    A=B<<5;
	B = * AbsZ_Encoder7_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsZ_Encoder6_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsZ_Encoder5_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsZ_Encoder4_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsZ_Encoder3_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsZ_Encoder2_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsZ_Encoder1_ADD;
	A=A|B;
	C = A;
	B = A>>32;
	B = B&0X01;
	if(B == 0)
	{
        A = C;
	}
	if(B == 1)
	{
	 	C = ~C+1;
	    A = C&0XFFFFFFFF;
	    A = 0-A;
	}
	return A;
}
/************************************************************
* 函数名称：Motor_R_Abs_Read()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：R轴电机绝对值编码器使能和信息寄存器信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*-----------------------------------------------------------
-----------------------------------------------------------*
* 版本信息
* 版本.           日期             创建               描述
* v.1           2016.08.26
*************************************************************/
long long int Motor_R_Abs_Read()
{
	volatile  long long int B;
	volatile  long long int A;     //绝对值编码器位置信息寄存器
	volatile  long long int C;

	while(1)
	{
	    A=* AbsR_Encoder2_ADD;
	    Delay_ms(1);
	    if(A==* AbsR_Encoder2_ADD)
	    {
	    	break;
	    }
	}
	while(1)
	{
	    A=* AbsR_Encoder1_ADD;
	   	Delay_ms(1);
	   	if(A==* AbsR_Encoder1_ADD)
	   	{
	   	    break;
	   	}
	}
	A=0;
	B=0;
    B = * AbsR_Encoder8_ADD;
    A=B<<5;
	B = * AbsR_Encoder7_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsR_Encoder6_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsR_Encoder5_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsR_Encoder4_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsR_Encoder3_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsR_Encoder2_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsR_Encoder1_ADD;
	A=A|B;
	C = A;
	B = A>>32;
	B = B&0X01;
	if(B == 0)
	{
        A = C;
	}
	if(B == 1)
	{
	 	C = ~C+1;
	    A = C&0XFFFFFFFF;
	    A = 0-A;
	}
	return A;
}
/************************************************************
* 函数名称：Motor_B_Abs_Read()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：B轴电机绝对值编码器使能和信息寄存器信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*-----------------------------------------------------------
-----------------------------------------------------------*
* 版本信息
* 版本.           日期             创建               描述
* v.1           2016.08.26
*************************************************************/
long long int Motor_B_Abs_Read()
{
	volatile  long long int B;
	volatile  long long int A;     //绝对值编码器位置信息寄存器
	volatile  long long int C;

	while(1)
	{
	    A=* AbsB_Encoder2_ADD;
	    Delay_ms(1);
	    if(A==* AbsB_Encoder2_ADD)
	    {
	    	break;
	    }
	}
	while(1)
	{
	    A=* AbsB_Encoder1_ADD;
	   	Delay_ms(1);
	   	if(A==* AbsB_Encoder1_ADD)
	   	{
	   	    break;
	   	}
	}
	A=0;
	B=0;
    B = * AbsB_Encoder8_ADD;
    A=B<<5;
	B = * AbsB_Encoder7_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsB_Encoder6_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsB_Encoder5_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsB_Encoder4_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsB_Encoder3_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsB_Encoder2_ADD;
	A=A|B;
	A=A<<5;
	B = * AbsB_Encoder1_ADD;
	A=A|B;
	C = A;
	B = A>>32;
	B = B&0X01;
	if(B == 0)
	{
        A = C;
	}
	if(B == 1)
	{
	 	C = ~C+1;
	    A = C&0XFFFFFFFF;
	    A = 0-A;
	}
	return A;
}
/************************************************************
* 函数名称：Motor_T_Abs_Read()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：T轴电机绝对值编码器使能和信息寄存器信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*-----------------------------------------------------------
-----------------------------------------------------------*
* 版本信息
* 版本.           日期             创建               描述
* v.1           2016.07.18
*************************************************************/
long long int Motor_T_Abs_Read()
{
	volatile  long long int A;     //绝对值编码器位置信息寄存器
	volatile  long long int B;
	volatile  long long int C;

	while(1)
	{
	    A = * AbsT_Encoder2_ADD;
	    Delay_ms(5);
	    if(A == * AbsT_Encoder2_ADD)
	    {
	    	break;
	    }
	}
	while(1)
	{
	    A = * AbsT_Encoder1_ADD;
	    Delay_ms(55);
	    if(A == * AbsT_Encoder1_ADD)
	    {
	     	break;
	    }
	}
	A = 0;
	B = 0;
	B = * AbsT_Encoder8_ADD;
    A = B<<5;
	B = * AbsT_Encoder7_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsT_Encoder6_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsT_Encoder5_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsT_Encoder4_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsT_Encoder3_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsT_Encoder2_ADD;
	A = A|B;
	A = A<<5;
	B = * AbsT_Encoder1_ADD;
	A = A|B;
	C = A;
	B = A>>32;
	B = B&0X01;
	if(B == 0)
	{
		A = C;
	}
	if(B == 1)
	{
	    C = ~C+1;
	    A = C&0XFFFFFFFF;
	    A = 0-A;
	}
	return A;
}
/************************************************************
* 函数名称：Motor_X_AbsReset_Read()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：设置X轴电机绝对值编码器清零寄存器
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
void Motor_X_AbsReset_Set()
{
	*AbsX_Reset_ADD = 1;
	Delay_ms(200);
	*AbsX_Reset_ADD = 0;
}
/************************************************************
* 函数名称：Motor_Y_AbsReset_Read()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：Y轴电机绝对值编码器清零寄存器信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
void Motor_Y_AbsReset_Set()
{
	*AbsY_Reset_ADD = 1;
	Delay_ms(200);
	*AbsY_Reset_ADD = 0;
}
/************************************************************
* 函数名称：Motor_Z_AbsReset_Read()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：Z轴电机绝对值编码器清零寄存器信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
void Motor_Z_AbsReset_Set()
{
	*AbsZ_Reset_ADD = 1;
	Delay_ms(200);
	*AbsZ_Reset_ADD = 0;
}
/************************************************************
* 函数名称：Motor_R_AbsReset_Read()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：R轴电机绝对值编码器清零寄存器信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
void Motor_R_AbsReset_Set()
{
	*AbsR_Reset_ADD = 1;
	Delay_ms(200);
	*AbsR_Reset_ADD = 0;
}
/************************************************************
* 函数名称：Motor_B_AbsReset_Read()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：B轴电机绝对值编码器清零寄存器信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
void Motor_B_AbsReset_Set()
{
	*AbsB_Reset_ADD = 1;
	Delay_ms(200);
	*AbsB_Reset_ADD = 0;
}
/************************************************************
* 函数名称：Motor_T_AbsReset_Read()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：T轴电机绝对值编码器清零寄存器信息读取
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
void Motor_T_AbsReset_Set()
{
	*AbsT_Reset_ADD = 1;
	Delay_ms(200);
	*AbsT_Reset_ADD = 0;
}
/************************************************************
* 函数名称：Motor_Return_State ()
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：返回电机状态信息
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
unsigned int Motor_Return_State ()
{
	volatile unsigned int Motor_State;        //电机状态

	Motor_State = *State_ADD;
	return Motor_State;                      //返回电机状态信息
}
/************************************************************
* 函数名称：Motor_Set_EN (unsigned int Motor_EN)
* 创建日期：2016.7.18
* 创       建：王朔/九安医疗设备开发一室
* 描       述：电机使能信息写入
* 参       数：
* 返 回 值：
* 全局变量：
*************************************************************/
void Motor_Set_EN (unsigned int Motor_EN)
{
   	*EN_ADD = Motor_EN;                   //写入电机使能信息X 0001   Y0010    Z0100   R1000
}
/************************************************************
* 函数名称：delay_loop
* 输入参数：无
* 输出参数：无
* 功       能：延时5毫秒左右的时间 示波器测试过
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void delay_loop()
{
    unsigned short   i;
    for (i=0; i<60000; i++)
    {

    }
}
/************************************************************
* 函数名称：Delay
* 输入参数：无
* 输出参数：无
* 功       能：大概延时833纳秒
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Delay(void)
{
    unsigned short   i;
    for (i = 5; i >0; i--);
}
/************************************************************
* 函数名称：My_Nop
* 输入参数：无
* 输出参数：无
* 功       能：大概延时100纳秒
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void My_Nop(void)
{
    unsigned short  i;
    for (i = 400; i >0; i--);
}
/************************************************************
* 函数名称：Delay_s
* 输入参数：延时值
* 输出参数：无
* 功       能：单位为1秒的延时函数
* 备       注：调用delay_loop 组成，Delay_Time为延时值
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Delay_s(unsigned char Delay_Time)
{
    unsigned char i, j;
    for(j=0;j<Delay_Time;j++)
    {
        for(i=0;i<50;i++)
        {
            delay_loop();
        }
    }
}
/************************************************************
* 函数名称：Delay_ms
* 输入参数：延时值
* 输出参数：无
* 功       能：单位为1毫秒的延时函数
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Delay_ms(unsigned char Delay_Time)
{
    unsigned char i, j;
    for(j=0;j<Delay_Time;j++)
    {
        for(i=0;i<50;i++)
        {
            for(i = 0; i < 12000; i++)
            {
            }
        }
    }
}
