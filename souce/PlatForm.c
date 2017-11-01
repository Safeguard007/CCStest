#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP28x_Project.h" 
#include "PlatForm.h"
#include "control.h"
#include "math.h"
#include "DSP2833x_GlobalPrototypes.h"

/***********************ȫ�ֱ���������**************************/
#pragma DATA_SECTION(SCIA_Data, "ZONE7DATA");
        SCI_Data_TypeDef SCIA_Data;                     //����A���ݶ���
#pragma DATA_SECTION(SCIC_Data, "ZONE7DATA");
        SCI_Data_TypeDef SCIC_Data;                     //����C���ݶ���

#pragma DATA_SECTION(SCIA_Tx_Message, "ZONE7DATA");
        SCI_TX_Type SCIA_Tx_Message;                    //����A���ݷ��Ͷ���
#pragma DATA_SECTION(SCIC_Tx_Message, "ZONE7DATA");
        SCI_TX_Type SCIC_Tx_Message;                    //����C���ݷ��Ͷ���

#pragma DATA_SECTION(SCI_CMD_Message,"ZONE7DATA");
        SCI_Cmd_TypeDef  *SCI_CMD_Message;              //����ͨ��Э��ṹ��ǿ��ת����Ϣ����
#pragma DATA_SECTION(SCI_CMD_Message,"ZONE7DATA");
        SCI_Cmd_TypeDef SCI_CMD_Message1;               //����ͨ��Э��ṹ��ǿ��ת����Ϣ���壨������ȡ��������λ���ݣ�

#pragma DATA_SECTION(Cmd_Tx_Long,"ZONE7DATA");
        int Cmd_Tx_Long;                                //�жϷ���ģʽ�·����ַ����ĳ���ֵ����

#pragma DATA_SECTION(Auxiliary_Fun,"ZONE7DATA");
        unsigned char  Auxiliary_Fun;                   //���ڴ������и�������λ������ͨ��Э���趨��
#pragma DATA_SECTION(Answer_Flag,"ZONE7DATA");
        unsigned char Answer_Flag;                      //������Ϣ�洢ʱ����ָ��ظ���־������FLASH��ʼ��ʱֻ����Ϣ�洢������Ϣ�ظ���
#pragma DATA_SECTION(Execute_Flag,"ZONE7DATA");
        unsigned char Execute_Flag;                     //ָ��ִ�б�־λ�������ڽ���У��������ָ������£�ֻ��ָ����д������ִ�У�
#pragma DATA_SECTION(AC,"ZONE7DATA");
        unsigned int AC;                     //AC���ڱ�־λ
#pragma DATA_SECTION(User_Range, "ZONE7DATA");
        Robot_RANGE_Type * User_Range;                  //�˶���Χ����
#pragma DATA_SECTION(User_Range_Buff, "ZONE7DATA");
        float User_Range_Buff[12];                      //�û��趨�˶���Χ���ݻ���������
#pragma DATA_SECTION(User_Range_Str, "ZONE7DATA");
        unsigned char User_Range_Str[72];               //�û��趨�˶���Χ�ַ����洢
#pragma DATA_SECTION(RAMCS, "ZONE7DATA");
        unsigned char RAMCS[10];               //ceshi RAM zhuanyong
#pragma DATA_SECTION(CESHI, "ZONE7DATA");
        unsigned char CESHI[100] ;              //CESHI
#pragma DATA_SECTION(CESHIR, "ZONE7DATA");
        unsigned char CESHIR[100] ;              //CESHIR
#pragma DATA_SECTION(CESHIF, "ZONE7DATA");
        unsigned int CESHIF[100] ;              //CESHIF

#pragma DATA_SECTION(Robot_Run_Reg,"ZONE7DATA");
        ROBOT_STATUS_REGS_TypeDef Robot_Run_Reg;        //����һ��ϵͳ������������Ϣ�ļĴ���

#pragma DATA_SECTION(SCARA_Run_Theta,"ZONE7DATA");
        THETA_JOINT_Type SCARA_Run_Theta;               //�ؽڿռ����궨�壨�����ƣ�

#pragma DATA_SECTION(Trajetory_points,"ZONE7DATA");
        FPGA_Run_Info_Type Trajetory_points;            //FPGA���Ƶ����������

#pragma DATA_SECTION(Motor_Run_points,"ZONE7DATA");
        Motor_Run_Info_Type Motor_Run_points;           //�켣�滮�����������

/***********************ȫ�ֱ���������Ƶ�ַ��**************************/
Uint16 * test = (Uint16 *)0x100195;                     //ʹ�ܵ�ַ
Uint16 * BJ123 = (Uint16 *)0x100182;                 //J1.J2.J3������ַ
Uint16 * BJ456 = (Uint16 *)0x100184;                   //J4.J5.J6������ַ
//X����
Uint16 * FreqX_ADD = (Uint16 *)0x100000;                //һ����Ƶ�ʼĴ�����ַ
Uint16 * FreqX_ADD1 = (Uint16 *)0x100191;
Uint16 * NumX_ADD = (Uint16 *)0x100001;                 //һ����PWM��������Ĵ�����ַ1
Uint16 * NumX_ADD1 = (Uint16 *)0x100185;                //һ����PWM��������Ĵ�����ַ2
Uint16 * DirX_ADD = (Uint16 *)0x100002;                 //һ��������Ĵ�����ַ
Uint16 * DIRVER_ENX_ADD = (Uint16 *)0x100003;           //һ������������Ϣд��Ĵ�����ַ
Uint16 * PulsX_Warn_ADD = (Uint16 *)0x100004;           //������󱨾��Ĵ�����ַ
Uint16 * PulsX_Bias_ADD = (Uint16 *)0x100005;           //����ƫ��Ĵ�����ַ
Uint16 * AbsX_Reset_ADD = (Uint16 *)0x100006;           //����ֵ����������ָ��Ĵ�����ַ
Uint16 * AbsX_Encoder1_ADD = (Uint16 *)0x100007;        //����ֵλ��ʹ�ܼĴ�����ַ
Uint16 * AbsX_Encoder2_ADD = (Uint16 *)0x100008;
Uint16 * AbsX_Encoder3_ADD = (Uint16 *)0x100009;
Uint16 * AbsX_Encoder4_ADD = (Uint16 *)0x10000a;
Uint16 * AbsX_Encoder5_ADD = (Uint16 *)0x10000f;
Uint16 * AbsX_Encoder6_ADD = (Uint16 *)0x10000c;
Uint16 * AbsX_Encoder7_ADD = (Uint16 *)0x10000d;
Uint16 * AbsX_Encoder8_ADD = (Uint16 *)0x10000e;

//Y����
Uint16 * FreqY_ADD = (Uint16 *)0x100040;                //���Ƶ�ʼĴ�����ַ
Uint16 * FreqY_ADD1 = (Uint16 *)0x100192;
Uint16 * NumY_ADD = (Uint16 *)0x100041;                 //���PWM��������Ĵ�����ַ1
Uint16 * NumY_ADD1 = (Uint16 *)0x100186;                //���PWM��������Ĵ�����ַ2
Uint16 * DirY_ADD = (Uint16 *)0x100042;                 //�������Ĵ�����ַ
Uint16 * DIRVER_ENY_ADD = (Uint16 *)0x100043;           //�����������Ϣд��Ĵ�����ַ
Uint16 * PulsY_Warn_ADD = (Uint16 *)0x100044;           //������󱨾��Ĵ�����ַ
Uint16 * PulsY_Bias_ADD = (Uint16 *)0x100045;           //����ƫ��Ĵ�����ַ
Uint16 * AbsY_Reset_ADD = (Uint16 *)0x100046;           //����ֵ����������ָ��Ĵ�����ַ
Uint16 * AbsY_Encoder1_ADD = (Uint16 *)0x100047;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsY_Encoder2_ADD = (Uint16 *)0x100048;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsY_Encoder3_ADD = (Uint16 *)0x100049;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsY_Encoder4_ADD = (Uint16 *)0x10004a;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsY_Encoder5_ADD = (Uint16 *)0x10004f;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsY_Encoder6_ADD = (Uint16 *)0x10004c;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsY_Encoder7_ADD = (Uint16 *)0x10004d;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsY_Encoder8_ADD = (Uint16 *)0x10004e;        //����ֵ������λ����Ϣ�Ĵ�����ַ

//Z����
Uint16 * FreqZ_ADD = (Uint16 *)0x100080;                //���Ƶ�ʼĴ�����ַ
Uint16 * FreqZ_ADD1 = (Uint16 *)0x100193;
Uint16 * NumZ_ADD = (Uint16 *)0x100081;                 //���PWM��������Ĵ�����ַ1
Uint16 * NumZ_ADD1 = (Uint16 *)0x100187;                //���PWM��������Ĵ�����ַ2
Uint16 * DirZ_ADD = (Uint16 *)0x100082;                 //�������Ĵ�����ַ
Uint16 * DIRVER_ENZ_ADD = (Uint16 *)0x100083;           //�����������Ϣд��Ĵ�����ַ
Uint16 * PulsZ_Warn_ADD = (Uint16 *)0x100084;           //������󱨾��Ĵ�����ַ
Uint16 * PulsZ_Bias_ADD = (Uint16 *)0x100085;           //����ƫ��Ĵ�����ַ
Uint16 * AbsZ_Reset_ADD = (Uint16 *)0x100086;           //����ֵ����������ָ��Ĵ�����ַ
Uint16 * AbsZ_Encoder1_ADD = (Uint16 *)0x100087;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsZ_Encoder2_ADD = (Uint16 *)0x100088;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsZ_Encoder3_ADD = (Uint16 *)0x100089;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsZ_Encoder4_ADD = (Uint16 *)0x10008a;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsZ_Encoder5_ADD = (Uint16 *)0x10008f;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsZ_Encoder6_ADD = (Uint16 *)0x10008c;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsZ_Encoder7_ADD = (Uint16 *)0x10008d;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsZ_Encoder8_ADD = (Uint16 *)0x10008e;        //����ֵ������λ����Ϣ�Ĵ�����ַ

//R����
Uint16 * FreqR_ADD = (Uint16 *)0x1000C0;                //���Ƶ�ʼĴ�����ַ
Uint16 * FreqR_ADD1 = (Uint16 *)0x100194;
Uint16 * NumR_ADD = (Uint16 *)0x1000C1;                 //���PWM��������Ĵ�����ַ1
Uint16 * NumR_ADD1 = (Uint16 *)0x100188;                //���PWM��������Ĵ�����ַ2
Uint16 * DirR_ADD = (Uint16 *)0x1000C2;                 //�������Ĵ�����ַ
Uint16 * DIRVER_ENR_ADD = (Uint16 *)0x1000C3;           //�����������Ϣд��Ĵ�����ַ
Uint16 * PulsR_Warn_ADD = (Uint16 *)0x1000C4;           //������󱨾��Ĵ�����ַ
Uint16 * PulsR_Bias_ADD = (Uint16 *)0x1000C5;           //����ƫ��Ĵ�����ַ
Uint16 * AbsR_Reset_ADD = (Uint16 *)0x1000C6;           //����ֵ����������ָ��Ĵ�����ַ
Uint16 * AbsR_Encoder1_ADD = (Uint16 *)0x1000C7;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsR_Encoder2_ADD = (Uint16 *)0x1000C8;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsR_Encoder3_ADD = (Uint16 *)0x1000C9;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsR_Encoder4_ADD = (Uint16 *)0x1000Ca;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsR_Encoder5_ADD = (Uint16 *)0x1000Cf;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsR_Encoder6_ADD = (Uint16 *)0x1000Cc;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsR_Encoder7_ADD = (Uint16 *)0x1000Cd;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsR_Encoder8_ADD = (Uint16 *)0x1000Ce;        //����ֵ������λ����Ϣ�Ĵ�����ַ
//B����
Uint16 * FreqB_ADD = (Uint16 *)0x100100;                //���Ƶ�ʼĴ�����ַ
Uint16 * FreqB_ADD1 = (Uint16 *)0x100195;
Uint16 * NumB_ADD = (Uint16 *)0x100101;                 //���PWM��������Ĵ�����ַ1
Uint16 * NumB_ADD1 = (Uint16 *)0x100189;                //���PWM��������Ĵ�����ַ2
Uint16 * DirB_ADD = (Uint16 *)0x100102;                 //�������Ĵ�����ַ
Uint16 * DIRVER_ENB_ADD = (Uint16 *)0x100103;           //�����������Ϣд��Ĵ�����ַ
Uint16 * PulsB_Warn_ADD = (Uint16 *)0x100104;           //������󱨾��Ĵ�����ַ
Uint16 * PulsB_Bias_ADD = (Uint16 *)0x100105;           //����ƫ��Ĵ�����ַ
Uint16 * AbsB_Reset_ADD = (Uint16 *)0x100106;           //����ֵ����������ָ��Ĵ�����ַ
Uint16 * AbsB_Encoder1_ADD = (Uint16 *)0x100107;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsB_Encoder2_ADD = (Uint16 *)0x100108;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsB_Encoder3_ADD = (Uint16 *)0x100109;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsB_Encoder4_ADD = (Uint16 *)0x10010a;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsB_Encoder5_ADD = (Uint16 *)0x10010f;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsB_Encoder6_ADD = (Uint16 *)0x10010c;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsB_Encoder7_ADD = (Uint16 *)0x10010d;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsB_Encoder8_ADD = (Uint16 *)0x10010e;        //����ֵ������λ����Ϣ�Ĵ�����ַ

Uint16 * FreqT_ADD = (Uint16 *)0x100140;                //���Ƶ�ʼĴ�����ַ
Uint16 * FreqT_ADD1 = (Uint16 *)0x100196;
Uint16 * NumT_ADD = (Uint16 *)0x100141;                 //���PWM��������Ĵ�����ַ1
Uint16 * NumT_ADD1 = (Uint16 *)0x100190;                //���PWM��������Ĵ�����ַ2
Uint16 * DirT_ADD = (Uint16 *)0x100142;                 //�������Ĵ�����ַ
Uint16 * DIRVER_ENT_ADD = (Uint16 *)0x100143;           //�����������Ϣд��Ĵ�����ַ
Uint16 * PulsT_Warn_ADD = (Uint16 *)0x100144;           //������󱨾��Ĵ�����ַ
Uint16 * PulsT_Bias_ADD = (Uint16 *)0x100145;           //����ƫ��Ĵ�����ַ
Uint16 * AbsT_Reset_ADD = (Uint16 *)0x100146;           //����ֵ����������ָ��Ĵ�����ַ
Uint16 * AbsT_Encoder1_ADD = (Uint16 *)0x100147;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsT_Encoder2_ADD = (Uint16 *)0x100148;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsT_Encoder3_ADD = (Uint16 *)0x100149;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsT_Encoder4_ADD = (Uint16 *)0x10014a;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsT_Encoder5_ADD = (Uint16 *)0x10014f;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsT_Encoder6_ADD = (Uint16 *)0x10014c;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsT_Encoder7_ADD = (Uint16 *)0x10014d;        //����ֵ������λ����Ϣ�Ĵ�����ַ
Uint16 * AbsT_Encoder8_ADD = (Uint16 *)0x10014e;        //����ֵ������λ����Ϣ�Ĵ�����ַ
//������Ϣ����
Uint16 * EN_ADD = (Uint16 *)0x100180;                   //���ʹ�ܼĴ�����ַ
Uint16 * State_ADD = (Uint16 *)0x100181;                //�������״̬�Ĵ�����ַ
Uint16 * SN = (Uint16 *)0x100198;
Uint16 * ACC1 = (Uint16 *)0x100199;                      //���ٶ�
Uint16 * ACC2 = (Uint16 *)0x100012;
Uint16 * ACC3 = (Uint16 *)0x100013;
Uint16 * ACC4 = (Uint16 *)0x100014;
Uint16 * ACC5 = (Uint16 *)0x100015;
Uint16 * ACC6 = (Uint16 *)0x100016;
/*******************************************28335ϵͳ��ʼ������*************************************************/
/********************28335ϵͳ��ʼ������************************/
/************************************************************
* �������ƣ�P_Gpio_Init()
* �������ڣ�2016.5.13
* ��    ����������/�Ű�ҽ���豸����һ��
* ��    �����ܽŶ���
* ��    ����
* �� �� ֵ��
* ȫ�ֱ�����
*-----------------------------------------------------------
-----------------------------------------------------------*
* �汾��Ϣ
* �汾.           ����             ����               ����
*************************************************************/
void P_Gpio_Init(void)
{
    EALLOW;
    #ifdef DOF_V10
///////////////////////LED�ƹܽ�����///////////////////////////
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;      //����GPIO53Ϊͨ�õ�I/O  CPU_RUN
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = 1;       //����GPIO53Ϊͨ�������

    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;      //����GPIO15Ϊͨ�õ�I/O  CPU_RUN
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;       //����GPIO15Ϊͨ�������

    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;      //����GPIO34Ϊͨ�õ�I/O  CPU_RUN
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;       //����GPIO34Ϊͨ�������

///////////////////////�ж�IO�ܽ�����///////////////////////////
/*
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;      //����GPIO8Ϊͨ�õ�I/O
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;       //����GPIO8Ϊͨ�������
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO8 = 0;     //GPIOʱ�Ӻ�ϵͳʱ��һ����֧��GPIO
    GpioIntRegs.GPIOXNMISEL.bit.GPIOSEL = 8; //NMI�ж�ѡ��GPIO
    XIntruptRegs.XNMICR.bit.POLARITY = 0;    //����ģʽΪ�½��ش���
    XIntruptRegs.XNMICR.bit.ENABLE = 1;      //ʹ���ж�

    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;      //����GPIO9Ϊͨ�õ�I/O
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;       //����GPIO9Ϊͨ�������
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 0;
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 9;
    XIntruptRegs.XINT1CR.bit.POLARITY = 0;
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;      //����GPIO10Ϊͨ�õ�I/O
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;       //����GPIO10Ϊͨ�������
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO10 = 0;
    GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 10;
    XIntruptRegs.XINT2CR.bit.POLARITY = 0;
    XIntruptRegs.XINT2CR.bit.ENABLE = 1;
*/
///////////////////////�����·�ܽ�����///////////////////////////
     GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;      //����GPIO0Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;       //����GPIO0Ϊͨ�������
     GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;      //����GPIO1Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;       //����GPIO1Ϊͨ�������
     GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;      //����GPIO2Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;       //����GPIO2Ϊͨ�������
     GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;      //����GPIO3Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO3= 0;       //����GPIO3Ϊͨ�������
     GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;      //����GPIO0Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;       //����GPIO0Ϊͨ�������
     GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;      //����GPIO1Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;       //����GPIO1Ϊͨ�������
     GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;      //����GPIO2Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;       //����GPIO2Ϊͨ�������
     GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;

     GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;      //����GPIO3Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO14= 0;       //����GPIO3Ϊͨ�������
     GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;

     GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;      //����GPIO0Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;       //����GPIO0Ϊͨ�������
     GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;

     GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;      //����GPIO1Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;       //����GPIO1Ϊͨ�������
     GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;

     GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;      //����GPIO2Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;       //����GPIO2Ϊͨ�������
     GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;

     GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;      //����GPIO3Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO25= 0;       //����GPIO3Ϊͨ�������
     GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;

///////////////////////ʹ�ܹܽ�����///////////////////////////
     GpioCtrlRegs.GPBMUX2.bit.GPIO59= 0;      //����GPIO59Ϊͨ�õ�I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO59 = 1;       //����GPIO59Ϊͨ�������

     GpioCtrlRegs.GPBMUX2.bit.GPIO60= 0;      //����GPIO60Ϊͨ�õ�I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1;       //����GPIO60Ϊͨ�������

     GpioCtrlRegs.GPBMUX2.bit.GPIO61= 0;      //����GPIO61Ϊͨ�õ�I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;       //����GPIO61Ϊͨ�������
///////////////////////�����·�ܽ�����///////////////////////////
     GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;      //����GPIO4Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;       //����GPIO4Ϊͨ�������

     GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;      //����GPIO5Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;       //����GPIO5Ϊͨ�������

     GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;      //����GPIO6Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;       //����GPIO6Ϊͨ�������

     GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;      //����GPIO7Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO7= 1;       //����GPIO7Ϊͨ�������

     GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;      //����GPIO4Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO26 = 1;       //����GPIO4Ϊͨ�������

     GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;      //����GPIO5Ϊͨ�õ�I/O
     GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;       //����GPIO5Ϊͨ�������

     GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;      //����GPIO6Ϊͨ�õ�I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;       //����GPIO6Ϊͨ�������

     GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;      //����GPIO7Ϊͨ�õ�I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO33= 1;       //����GPIO7Ϊͨ�������

     GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;      //����GPIO4Ϊͨ�õ�I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;       //����GPIO4Ϊͨ�������

     GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;      //����GPIO5Ϊͨ�õ�I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1;       //����GPIO5Ϊͨ�������

     GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;      //����GPIO6Ϊͨ�õ�I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;       //����GPIO6Ϊͨ�������

     GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;      //����GPIO7Ϊͨ�õ�I/O
     GpioCtrlRegs.GPBDIR.bit.GPIO51= 1;       //����GPIO7Ϊͨ�������
//////////////////////SCIA��������/////////////////////////////
    GpioCtrlRegs.GPBPUD.bit.GPIO35 = 0;       //ʹ��GPIO35��SCITXDA���ڲ���������
    GpioCtrlRegs.GPBPUD.bit.GPIO36 = 0;       //ʹ��GPIO36��SCIRXDA���ڲ���������
    GpioCtrlRegs.GPBQSEL1.bit.GPIO35 = 3;     //�ܽŶ���Ϊ�첽���
    GpioCtrlRegs.GPBQSEL1.bit.GPIO36 = 3;     //�ܽŶ���Ϊ�첽����
    GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 1;      //����GPIO35  Ϊ SCITXDA����
    GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 1;      //����GPIO36  Ϊ SCIRXDA����

//////////////////////SCIC��������/////////////////////////////
    GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0;       //ʹ��GPIO62��SCIRXDC���ڲ���������
    GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;       //ʹ��GPIO63��SCITXDC���ڲ���������
    GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = 3;     //�ܽŶ���Ϊ�첽����
    GpioCtrlRegs.GPBQSEL2.bit.GPIO63 = 3;     //�ܽŶ���Ϊ�첽���
    GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 1;      //����GPIO62  Ϊ SCIRXDA����
    GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 1;      //����GPIO63  Ϊ SCITXDA����

////////////////////////////////spi��������////////////////////////////////
    GpioCtrlRegs.GPBPUD.bit.GPIO54 = 0;       // �ڲ�����GPIO54 (SPISIMOA)
    GpioCtrlRegs.GPBPUD.bit.GPIO55 = 0;       // �ڲ�����GPIO55 (SPISOMIA)
    GpioCtrlRegs.GPBPUD.bit.GPIO56 = 0;       // �ڲ�����GPIO56 (SPICLKA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3;     // �첽���GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3;     // �첽���GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3;     // �첽���GPIO18 (SPICLKA)
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1;      // ���ù���ΪGPIO54 as SPISIMOA
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1;      // ���ù���ΪGPIO55 as SPISOMIA
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1;      // ���ù���ΪGPIO56 as SPICLKA

////////////////////////////////flash��������////////////////////////////////
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0x00;   //���Ź���ѡ��Ϊͨ��GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0x01;    //GPIO�����������
    GpioDataRegs.GPBSET.bit.GPIO58 = 0x01;    //����ߣ�FLASH��λ���ŵ͵�ƽ��λ
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0x00;   //���Ź���ѡ��Ϊͨ��GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO57 = 0x01;    //GPIO�����������
    GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;    //����ߣ�FLASH��λ���ŵ͵�ƽ��λ
	#endif
    EDIS;
}
/************************************************************
* �������ƣ�P_Led_Init
* �����������
* �����������
* ��       �ܣ�LED�Ƴ�ʼ�����ڳ�ʼ״̬ʱLED��Ϊ��
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/	
void P_Led_Init(void)
{
  	EALLOW;
	#ifdef DOF_V10

	LED1_L;             //��ʼΪ�͵�ƽ������
	LED2_L;             //��ʼΪ�͵�ƽ������
	LED3_L;             //��ʼΪ�͵�ƽ������

	GpioDataRegs.GPBSET.bit.GPIO59=1;
	GpioDataRegs.GPBSET.bit.GPIO60=1;
	GpioDataRegs.GPBSET.bit.GPIO61=1;
/*
	GpioDataRegs.GPBCLEAR.bit.GPIO59=1;
	GpioDataRegs.GPBCLEAR.bit.GPIO60=1;
	GpioDataRegs.GPBCLEAR.bit.GPIO61=1;
*/
	GPIO1_OUT0;             //GPO��ʼ�����Ϊ�͵�ƽ
	GPIO2_OUT0;             //GPO��ʼ�����Ϊ�͵�ƽ
	GPIO3_OUT0;             //GPO��ʼ�����Ϊ�͵�ƽ
	GPIO4_OUT0;             //GPO��ʼ�����Ϊ�͵�ƽ
	GPIO5_OUT0;             //GPO��ʼ�����Ϊ�͵�ƽ
	GPIO6_OUT0;             //GPO��ʼ�����Ϊ�͵�ƽ
	GPIO7_OUT0;             //GPO��ʼ�����Ϊ�͵�ƽ
	GPIO8_OUT0;             //GPO��ʼ�����Ϊ�͵�ƽ
	GPIO9_OUT0;             //GPO��ʼ�����Ϊ�͵�ƽ
	GPIO10_OUT0;             //GPO��ʼ�����Ϊ�͵�ƽ
	GPIO11_OUT0;             //GPO��ʼ�����Ϊ�͵�ƽ
	GPIO12_OUT0;             //GPO��ʼ�����Ϊ�͵�ƽ
	#endif
    EDIS;
}
/************************************************************
* �������ƣ�P_UartA_Init
* �����������
* �����������
* ��       �ܣ�����A��ʼ��
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void P_UartA_Init(void)
{
	EALLOW;

	SciaRegs.SCICCR.bit.STOPBITS=0;        //1λֹͣλ
	SciaRegs.SCICCR.bit.PARITYENA=0;       //��ֹ���Թ���
	SciaRegs.SCICCR.bit.LOOPBKENA=0;       //��ֹ���Ͳ���ģʽ����
	SciaRegs.SCICCR.bit.ADDRIDLE_MODE=0;   //������ģʽ
	SciaRegs.SCICCR.bit.SCICHAR=7;         //8λ����λ

	SciaRegs.SCIHBAUD = 0x0001;
    SciaRegs.SCILBAUD = 0x00E7;            //������Ϊ9600
	
	SciaRegs.SCICTL1.bit.TXENA=1;          //SCIAģ��ķ���ʹ��
	SciaRegs.SCICTL1.bit.RXENA=1;          //SCIAģ��Ľ���ʹ��
	SciaRegs.SCICTL2.bit.RXBKINTENA=1;     //SCIAģ������ж�ʹ��
	SciaRegs.SCICTL2.bit.TXINTENA=1;       //SCIAģ�鷢���ж�ʹ��
	SciaRegs.SCICTL1.bit.SWRESET=1;        //����SCI


	EDIS;
}
/************************************************************
* �������ƣ�P_UartC_Init
* �����������
* �����������
* ��       �ܣ�����C��ʼ��
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void P_UartC_Init(void)
{
    EALLOW;
	ScicRegs.SCICCR.all = 0x0007;          //1λֹͣλ����ֹ���Թ��ܣ���ֹ���Ͳ���ģʽ���ܣ�������ģʽ��8λ����λ
	ScicRegs.SCICTL1.all = 0x0003;         //SCICģ�����/����ʹ��
	ScicRegs.SCICTL2.bit.TXINTENA  = 1;    //SCICģ�鷢���ж�ʹ��
	ScicRegs.SCICTL2.bit.RXBKINTENA = 1;   //SCICģ������ж�ʹ��
	ScicRegs.SCIHBAUD = 0x0001;
	ScicRegs.SCILBAUD = 0x00E7;            //������Ϊ9600
	ScicRegs.SCICTL1.bit.SWRESET = 0x01;   //����SCI
	EDIS;
}

/************************************************************
* �������ƣ�spi_fifo_init()
* �����������
* �����������
* ��       �ܣ�SPI fifo��ʼ��
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
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
* �������ƣ�Spi_Init
* �����������
* �����������
* ��       �ܣ�SPI��ʼ��
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
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
////////////////////////////////SPI���üĴ���CCR////////////////////////////////
	SpiaRegs.SPICCR.bit.SPISWRESET = 0x0;        //SPI��λ
	SpiaRegs.SPICCR.bit.CLKPOLARITY = 0x00;	     //����ʱ�Ӽ��ԣ� 0Ϊ��������������������½������룬1Ϊ�������½��������������������
	SpiaRegs.SPICCR.bit.SPILBK = 0x0;	         //�Բ�ģʽ���� ��0Ϊ��ֹ�Բ�ģʽ��1Ϊ�Բ�ģʽʹ��
	SpiaRegs.SPICCR.bit.SPICHAR = 0X07;	         //���ݴ���������0~15
////////////////////////////////SPI���üĴ���CTL////////////////////////////////
	SpiaRegs.SPICTL.bit.OVERRUNINTENA = 0x0;     //������������ж�ʹ�ܣ�1-ʹ�ܣ�0-��ֹ
	SpiaRegs.SPICTL.bit.CLK_PHASE = 0x01;        //����ʱ����λ��0-������1-SPICLK�ź���ʱ�������
	SpiaRegs.SPICTL.bit.MASTER_SLAVE = 0x01;     //SPI����ģʽѡ��0-�ӻ���1-����
	SpiaRegs.SPICTL.bit.TALK = 0x01;             //SPI���ӷ���ʹ�ܣ�0-��ֹ���ͣ�1-ʹ�ܷ��ͣ���֤ʹ��SPISTE����
	SpiaRegs.SPICTL.bit.SPIINTENA = 0x00;	     //SPI�ж�ʹ�ܣ�0-��ֹ�жϣ�1-ʹ���ж�
////////////////////////////////SPI�����ʼĴ���BRR////////////////////////////////
	SpiaRegs.SPIBRR = 0x0063;                    //SPIBRR =0,1,2ʱ��������=SPICLK/4 SPIBRR =3~127ʱ��������=SPICLK/��SPIBRR+1��
	SpiaRegs.SPICCR.bit.SPISWRESET = 0x1;        //׼����ʼ���ͺͽ�������
    SpiaRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission
    EDIS;
}
/************************************************************
* �������ƣ�P_Board_Init
* �����������
* �����������
* ��       �ܣ�ϵͳ��ʼ��
* ��       ע������IO���ţ����ܺ��жϵĳ�ʼ��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void P_Board_Init(void)
{
    InitSysCtrl();                       //ϵͳʱ�ӳ�ʼ��
	DINT;                                //�ر�ϵͳ�ж�
	IER = 0x0000;                        //��ֹCPU�ж�
	IFR = 0x0000;                        //���CPU�жϱ�־
	InitPieCtrl();                       //��ʼ��PIE���ƼĴ���
	InitPieVectTable();                  //��ʼ��PIE�ж�������
    MemCopy(&RamfuncsLoadStart,&RamfuncsLoadEnd,&RamfuncsRunStart);  //flash��дʱ��Ҫ
    InitFlash();                         //flash��дʱ��Ҫ
	EnableInterrupts();                  //�жϳ�ʼ��
    P_Gpio_Init();                       //GPIO��ʼ��
    InitXintf16Gpio();                   //����RAM I/O��ʼ��
	P_Led_Init();                        //LED ��ʼ��
	InitXintf();                         //����RAM��ʼ��
	P_UartA_Init();	                     //����A���ܳ�ʼ��
	P_UartC_Init();                      //����C���ܳ�ʼ��
	Spi_Init();                          //SPI��ʼ��
	Spi_FIFO_Init();                     //SPI FIFO��ʼ��
	w25q256_init();                      //Flash��ʼ��

	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
	PieCtrlRegs.PIEIER9.bit.INTx1=1;     // PIE Group 9, INT1  SCIA���ж�
	PieCtrlRegs.PIEIER9.bit.INTx2=1;     // PIE Group 9, INT2

	PieCtrlRegs.PIEIER8.bit.INTx5=1;     // PIE Group 8, INT5  SCIC���ж�
	PieCtrlRegs.PIEIER8.bit.INTx6=1;     // PIE Group 8, INT6

	PieCtrlRegs.PIEIER1.bit.INTx4=1;     // PIE Group 1, INT4      �ⲿ�ж�
	PieCtrlRegs.PIEIER1.bit.INTx5=1;     // PIE Group 1, INT5
	IER|= M_INT1;
	IER|= M_INT8;
	IER|= M_INT9;
	IER = 0x181;                         //��CPU�ж�
    EINT;                                //��ȫ���ж�
    ERTM;                                //��ȫ��ʵʱ�ж�
}
/************************************************************
* �������ƣ�Str_To_Int
* ������������ݽ��ճ����ַ���
* �����������������
* ��       �ܣ���Խ��յ��ĳ����ַ���ת���ɳ�������
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
unsigned char Str_To_Int(unsigned char *Str)
{
    unsigned char Str_Int=0x00, i, j;
    unsigned char Str_Buff[] = "0123456789ABCDEF";
    unsigned char Str_Cov_Buff[2] = {0x00,0x00};

    for(j=0;j<2;j++)                     //�����ճ����ַ���ת������ֵ
    {
   	    for(i=0;i<16;i++)
   		{
     		if(Str_Buff[i] == Str[j])
     		{
     			Str_Cov_Buff[j] = i;
     		}
   		}
    }
    Str_Int = Str_Cov_Buff[0] * 10 + Str_Cov_Buff[1];   //���ݶ�Ӧλ�ö�����㳤��ֵ
	return Str_Int;
}
/************************************************************
* �������ƣ�Get_Check_Num
* ���������У��ͼ����ַ������ַ�������
* ����������������ֵ
* ��       �ܣ�����У���
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
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
* �������ƣ�Check_Char_To_Int
* ���������У����ַ���
* ����������������ֵ
* ��       �ܣ����յ���У����ַ���ת����У�����ֵ
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
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
* �������ƣ�Check_Int_To_Char
* ���������У�����ֵ
* ���������������ַ���
* ��       �ܣ���У���ת��Ϊ�ַ���
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
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
* �������ƣ�SCIA_Data_Int
* �����������
* �����������
* ��       �ܣ�SCIA���ݳ�ʼ��
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void SCIA_Data_Int(void)
{
    unsigned char *Spr;
	unsigned char i = 0;

	Spr = &SCIA_Data.Tx_Flag;     //ָ����ʼλΪTx_Flag
	for(i=0;i<211;i++)            //���Ĵ����������λ����ֵΪ0
	{
		*Spr++ = 0x00;
	}
}
/************************************************************
* �������ƣ�SCIC_Data_Int
* �����������
* �����������
* ��       �ܣ�SCIC���ݳ�ʼ��
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void SCIC_Data_Int(void)
{
    unsigned char *Spr;
	unsigned char i = 0;

	Spr = &SCIC_Data.Tx_Flag;      //ָ����ʼλΪTx_Flag
	for(i=0;i<211;i++)             //���Ĵ����������λ����ֵΪ0
	{
		*Spr++ = 0x00;
	}
}
/************************************************************
* �������ƣ�SCIA_Tx
* ��������������ַ������ݣ������ַ�������
* �����������
* ��       �ܣ�����A���ݲ�ѯ����
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
unsigned char SCIA_Tx(unsigned char *Send_Buff,unsigned int Send_Long)
{
    unsigned char i;
    unsigned int j;

    for(i=0;i<Send_Long;i++)
    {
        SciaRegs.SCITXBUF = Send_Buff[i];        //�����ַ�����ֵ�����ͼĴ���
        while(SciaRegs.SCICTL2.bit.TXRDY != 1)   //�жϷ��ͱ�־λ�Ƿ�Ϊ1
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
* �������ƣ�SCIC_Tx
* ��������������ַ������ݣ������ַ�������
* �����������
* ��       �ܣ�����C���ݲ�ѯ����
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
unsigned char SCIC_Tx(unsigned char*Send_Buff,unsigned int Send_Long)
{
    unsigned char i;
    unsigned int j;
    for(i=0;i<Send_Long;i++)
    {
        ScicRegs.SCITXBUF = Send_Buff[i];        //�����ַ�����ֵ�����ͼĴ���
        while(ScicRegs.SCICTL2.bit.TXRDY != 1)   //�жϷ��ͱ�־λ�Ƿ�Ϊ1
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
* �������ƣ�Motor_X_Set
* �������������Ƶ�ʣ����з���������
* �����������
* ��       �ܣ����õ��������д��Ĵ�������ʹ��OE
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void Motor_X_Set(unsigned long Freq, unsigned char Dir, unsigned long Num)
{
	*EN_ADD = 0;                        //���ʹ�ܸ�ֵΪ0
	*ACC1 = 0x000a;
   	*FreqX_ADD = Freq>>16;              //����Ƶ��
   	*FreqX_ADD1 = Freq;
   	*NumX_ADD1 = Num;
	*NumX_ADD = Num>>16;                //����������
    *DirX_ADD = Dir;                    //�������з���
    *DIRVER_ENX_ADD = 0x0001;           //������������Ϣд��Ĵ���
}
/************************************************************
* �������ƣ�Motor_Y_Set
* �������������Ƶ�ʣ����з���������
* �����������
* ��       �ܣ����õ��������д��Ĵ�������ʹ��OE
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void Motor_Y_Set(unsigned long Freq, unsigned char Dir, unsigned long Num)
{
	*EN_ADD = 0;
	*ACC2 = 0x000a;
   	*FreqY_ADD = Freq>>16;              //����Ƶ��
   	*FreqY_ADD1 = Freq;
   	*NumY_ADD = Num>>16;                //�������е�������
   	*NumY_ADD1 = Num;
    *DirY_ADD = Dir;                    //�������з���
    *DIRVER_ENY_ADD = 0x0001;           //������������Ϣд��Ĵ���
}
/************************************************************
* �������ƣ�Motor_Z_Set
* �������������Ƶ�ʣ����з���������
* �����������
* ��       �ܣ����õ��������д��Ĵ�������ʹ��OE
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void Motor_Z_Set(unsigned long Freq, unsigned char Dir, unsigned long Num)
{
	*EN_ADD = 0;
	*ACC3 = 0x000a;
   	*FreqZ_ADD = Freq>>16;              //����Ƶ��
   	*FreqZ_ADD1 = Freq;
    *DirZ_ADD = Dir;                    //�������з���
    *NumZ_ADD = Num>>16;                //�������е�������
    *NumZ_ADD1 = Num;
    *DIRVER_ENZ_ADD = 0x0001;           //������������Ϣд��Ĵ���
}
/************************************************************
* �������ƣ�Motor_R_Set
* �������������Ƶ�ʣ����з���������
* �����������
* ��       �ܣ����õ��������д��Ĵ�������ʹ��OE
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void Motor_R_Set(unsigned long Freq, unsigned char Dir, unsigned long Num)
{
	*EN_ADD = 0;
	*ACC4 = 0x000a;
   	*FreqR_ADD = Freq>>16;              //����Ƶ��
   	*FreqR_ADD1 = Freq;
    *DirR_ADD = Dir;                    //�������з���
    *NumR_ADD = Num>>16;                //�������е�������
    *NumR_ADD1 = Num;
    *DIRVER_ENR_ADD = 0x0001;           //������������Ϣд��Ĵ���
}
/************************************************************
* �������ƣ�Motor_B_Set
* �������������Ƶ�ʣ����з���������
* �����������
* ��       �ܣ����õ��������д��Ĵ�������ʹ��OE
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void Motor_B_Set(unsigned long Freq, unsigned char Dir, unsigned long Num)
{
	*EN_ADD = 0;
	*ACC5 = 0x000a;
   	*FreqB_ADD = Freq>>16;              //����Ƶ��
   	*FreqB_ADD1 = Freq;
    *DirB_ADD = Dir;                    //�������з���
    *NumB_ADD = Num>>16;                //�������е�������
    *NumB_ADD1 = Num;
    *DIRVER_ENB_ADD = 0x0001;           //������������Ϣд��Ĵ���
}
/************************************************************
* �������ƣ�Motor_T_Set
* �������������Ƶ�ʣ����з���������
* �����������
* ��       �ܣ����õ��������д��Ĵ�������ʹ��OE
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void Motor_T_Set(unsigned long Freq, unsigned char Dir, unsigned long Num)
{
	*EN_ADD = 0;
	*ACC6 = 0x000a;
   	*FreqT_ADD = Freq>>16;              //����Ƶ��
   	*FreqT_ADD1 = Freq;
    *DirT_ADD = Dir;                    //�������з���
    *NumT_ADD = Num>>16;                //�������е�������
    *NumT_ADD1 = Num;
    *DIRVER_ENT_ADD = 0x0001;           //������������Ϣд��Ĵ���
}
/************************************************************
* �������ƣ�BJ_X_Read()
* �������ڣ�2016.10.11
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����X����������Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
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
* �������ƣ�BJ_Y_Read()
* �������ڣ�2016.10.11
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����Y����������Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
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
* �������ƣ�BJ_Z_Read()
* �������ڣ�2016.10.11
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����Z����������Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
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
* �������ƣ�BJ_R_Read()
* �������ڣ�2016.10.11
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����R����������Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
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
* �������ƣ�BJ_B_Read()
* �������ڣ�2016.10.11
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����B����������Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
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
* �������ƣ�BJ_T_Read()
* �������ڣ�2016.10.11
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����T����������Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
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
* �������ƣ�Motor_X_Abs_Read()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����X��������ֵ������ʹ�ܺ���Ϣ�Ĵ�����Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*************************************************************/
long long int Motor_X_Abs_Read()
{
	volatile  long long int A;     //����ֵ������λ����Ϣ�Ĵ���
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
* �������ƣ�Motor_Y_Abs_Read()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����Y��������ֵ������ʹ�ܺ���Ϣ�Ĵ�����Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*-----------------------------------------------------------
-----------------------------------------------------------*
* �汾��Ϣ
* �汾.           ����             ����               ����
* v.1           2016.08.26
*************************************************************/
long long int Motor_Y_Abs_Read()
{
	volatile  long long int A;     //����ֵ������λ����Ϣ�Ĵ���
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
* �������ƣ�Motor_Z_Abs_Read()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����Z��������ֵ������ʹ�ܺ���Ϣ�Ĵ�����Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*-----------------------------------------------------------
-----------------------------------------------------------*
* �汾��Ϣ
* �汾.           ����             ����               ����
* v.1           2016.08.26
*************************************************************/
long long int Motor_Z_Abs_Read()
{
	volatile  long long int B;
	volatile  long long int A;     //����ֵ������λ����Ϣ�Ĵ���
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
* �������ƣ�Motor_R_Abs_Read()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����R��������ֵ������ʹ�ܺ���Ϣ�Ĵ�����Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*-----------------------------------------------------------
-----------------------------------------------------------*
* �汾��Ϣ
* �汾.           ����             ����               ����
* v.1           2016.08.26
*************************************************************/
long long int Motor_R_Abs_Read()
{
	volatile  long long int B;
	volatile  long long int A;     //����ֵ������λ����Ϣ�Ĵ���
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
* �������ƣ�Motor_B_Abs_Read()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����B��������ֵ������ʹ�ܺ���Ϣ�Ĵ�����Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*-----------------------------------------------------------
-----------------------------------------------------------*
* �汾��Ϣ
* �汾.           ����             ����               ����
* v.1           2016.08.26
*************************************************************/
long long int Motor_B_Abs_Read()
{
	volatile  long long int B;
	volatile  long long int A;     //����ֵ������λ����Ϣ�Ĵ���
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
* �������ƣ�Motor_T_Abs_Read()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����T��������ֵ������ʹ�ܺ���Ϣ�Ĵ�����Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*-----------------------------------------------------------
-----------------------------------------------------------*
* �汾��Ϣ
* �汾.           ����             ����               ����
* v.1           2016.07.18
*************************************************************/
long long int Motor_T_Abs_Read()
{
	volatile  long long int A;     //����ֵ������λ����Ϣ�Ĵ���
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
* �������ƣ�Motor_X_AbsReset_Read()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ��������X��������ֵ����������Ĵ���
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*************************************************************/
void Motor_X_AbsReset_Set()
{
	*AbsX_Reset_ADD = 1;
	Delay_ms(200);
	*AbsX_Reset_ADD = 0;
}
/************************************************************
* �������ƣ�Motor_Y_AbsReset_Read()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����Y��������ֵ����������Ĵ�����Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*************************************************************/
void Motor_Y_AbsReset_Set()
{
	*AbsY_Reset_ADD = 1;
	Delay_ms(200);
	*AbsY_Reset_ADD = 0;
}
/************************************************************
* �������ƣ�Motor_Z_AbsReset_Read()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����Z��������ֵ����������Ĵ�����Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*************************************************************/
void Motor_Z_AbsReset_Set()
{
	*AbsZ_Reset_ADD = 1;
	Delay_ms(200);
	*AbsZ_Reset_ADD = 0;
}
/************************************************************
* �������ƣ�Motor_R_AbsReset_Read()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����R��������ֵ����������Ĵ�����Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*************************************************************/
void Motor_R_AbsReset_Set()
{
	*AbsR_Reset_ADD = 1;
	Delay_ms(200);
	*AbsR_Reset_ADD = 0;
}
/************************************************************
* �������ƣ�Motor_B_AbsReset_Read()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����B��������ֵ����������Ĵ�����Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*************************************************************/
void Motor_B_AbsReset_Set()
{
	*AbsB_Reset_ADD = 1;
	Delay_ms(200);
	*AbsB_Reset_ADD = 0;
}
/************************************************************
* �������ƣ�Motor_T_AbsReset_Read()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       ����T��������ֵ����������Ĵ�����Ϣ��ȡ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*************************************************************/
void Motor_T_AbsReset_Set()
{
	*AbsT_Reset_ADD = 1;
	Delay_ms(200);
	*AbsT_Reset_ADD = 0;
}
/************************************************************
* �������ƣ�Motor_Return_State ()
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       �������ص��״̬��Ϣ
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*************************************************************/
unsigned int Motor_Return_State ()
{
	volatile unsigned int Motor_State;        //���״̬

	Motor_State = *State_ADD;
	return Motor_State;                      //���ص��״̬��Ϣ
}
/************************************************************
* �������ƣ�Motor_Set_EN (unsigned int Motor_EN)
* �������ڣ�2016.7.18
* ��       ������˷/�Ű�ҽ���豸����һ��
* ��       �������ʹ����Ϣд��
* ��       ����
* �� �� ֵ��
* ȫ�ֱ�����
*************************************************************/
void Motor_Set_EN (unsigned int Motor_EN)
{
   	*EN_ADD = Motor_EN;                   //д����ʹ����ϢX 0001   Y0010    Z0100   R1000
}
/************************************************************
* �������ƣ�delay_loop
* �����������
* �����������
* ��       �ܣ���ʱ5�������ҵ�ʱ�� ʾ�������Թ�
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void delay_loop()
{
    unsigned short   i;
    for (i=0; i<60000; i++)
    {

    }
}
/************************************************************
* �������ƣ�Delay
* �����������
* �����������
* ��       �ܣ������ʱ833����
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void Delay(void)
{
    unsigned short   i;
    for (i = 5; i >0; i--);
}
/************************************************************
* �������ƣ�My_Nop
* �����������
* �����������
* ��       �ܣ������ʱ100����
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void My_Nop(void)
{
    unsigned short  i;
    for (i = 400; i >0; i--);
}
/************************************************************
* �������ƣ�Delay_s
* �����������ʱֵ
* �����������
* ��       �ܣ���λΪ1�����ʱ����
* ��       ע������delay_loop ��ɣ�Delay_TimeΪ��ʱֵ
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
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
* �������ƣ�Delay_ms
* �����������ʱֵ
* �����������
* ��       �ܣ���λΪ1�������ʱ����
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
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
