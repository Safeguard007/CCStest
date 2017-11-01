#ifndef PLATFORM_H
#define PLATFORM_H

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "IQmathLib.h"
#include "DSP28x_Project.h"

#define DOF_V10   1
#define PI       (3.1415926)

///////////////////////////////////SPI FLASH������///////////////////////////////////
#define Enable_Reset              0x66                         //���ø�λ��ַ
#define Reset_Dev                 0x99                         //��λװ�õ�ַ
#define Read_Data                 0x03                         //��ȡ����
#define Read_Status_Reg2          0x35                         //��ȡ״̬�Ĵ���1
#define Read_Status_Reg1          0x05                         //��ȡ״̬�Ĵ���2
#define Read_Status_Reg3          0x15                         //��ȡ״̬�Ĵ���3
#define Enter_4B_Addr_Mode        0xB7
#define Write_Enable              0x06                         //дʹ��
#define Chip_Erase1               0xC7                         //оƬ����
#define Sector_Erase              0x20                         //4K��������
#define Page_Program              0x02                         //ҳ���

#define Range_Addr                0x0000                       //�û��趨�˶���ΧFLASH�洢�׵�ַ
#define Length_Addr               0x1000                       //�û��趨������Ч����FLASH�洢�׵�ַ


///////////////////////////////////LED�ƿ��ƶ���//////////////////////////////////////
#ifdef DOF_V10
  	#define LED1_H     (GpioDataRegs.GPBSET.bit.GPIO53=1)      //����GPIO53Ϊ�ߵ�ƽ
    #define LED1_L     (GpioDataRegs.GPBCLEAR.bit.GPIO53=1)    //����GPIO53Ϊ�͵�ƽ
	#define LED2_H     (GpioDataRegs.GPASET.bit.GPIO15=1)      //����GPIO60Ϊ�ߵ�ƽ
    #define LED2_L     (GpioDataRegs.GPACLEAR.bit.GPIO15=1)    //����GPIO60Ϊ�͵�ƽ
	#define LED3_H     (GpioDataRegs.GPBSET.bit.GPIO34=1)      //����GPIO61Ϊ�ߵ�ƽ
    #define LED3_L     (GpioDataRegs.GPBCLEAR.bit.GPIO34=1)    //����GPIO61Ϊ�͵�ƽ

	#define GPIO1_OUT1     (GpioDataRegs.GPASET.bit.GPIO4=1)      //����GPIO4Ϊ�ߵ�ƽ
    #define GPIO1_OUT0     (GpioDataRegs.GPACLEAR.bit.GPIO4=1)    //����GPIO4Ϊ�͵�ƽ
	#define GPIO2_OUT1     (GpioDataRegs.GPASET.bit.GPIO5=1)      //����GPIO5Ϊ�ߵ�ƽ
    #define GPIO2_OUT0     (GpioDataRegs.GPACLEAR.bit.GPIO5=1)    //����GPIO5Ϊ�͵�ƽ
	#define GPIO3_OUT1     (GpioDataRegs.GPASET.bit.GPIO6=1)      //����GPIO6Ϊ�ߵ�ƽ
    #define GPIO3_OUT0     (GpioDataRegs.GPACLEAR.bit.GPIO6=1)    //����GPIO6Ϊ�͵�ƽ
	#define GPIO4_OUT1     (GpioDataRegs.GPASET.bit.GPIO7=1)      //����GPIO7Ϊ�ߵ�ƽ
    #define GPIO4_OUT0    (GpioDataRegs.GPACLEAR.bit.GPIO7=1)     //����GPIO7Ϊ�͵�ƽ
	#define GPIO5_OUT1     (GpioDataRegs.GPASET.bit.GPIO26=1)     //����GPIO4Ϊ�ߵ�ƽ
    #define GPIO5_OUT0     (GpioDataRegs.GPACLEAR.bit.GPIO26=1)    //����GPIO4Ϊ�͵�ƽ
	#define GPIO6_OUT1     (GpioDataRegs.GPASET.bit.GPIO27=1)      //����GPIO5Ϊ�ߵ�ƽ
    #define GPIO6_OUT0     (GpioDataRegs.GPACLEAR.bit.GPIO27=1)    //����GPIO5Ϊ�͵�ƽ
	#define GPIO7_OUT1     (GpioDataRegs.GPBSET.bit.GPIO32=1)      //����GPIO6Ϊ�ߵ�ƽ
    #define GPIO7_OUT0     (GpioDataRegs.GPBCLEAR.bit.GPIO32=1)    //����GPIO6Ϊ�͵�ƽ
	#define GPIO8_OUT1     (GpioDataRegs.GPBSET.bit.GPIO33=1)      //����GPIO7Ϊ�ߵ�ƽ
    #define GPIO8_OUT0    (GpioDataRegs.GPBCLEAR.bit.GPIO33=1)     //����GPIO7Ϊ�͵�ƽ
	#define GPIO9_OUT1     (GpioDataRegs.GPBSET.bit.GPIO48=1)     //����GPIO4Ϊ�ߵ�ƽ
    #define GPIO9_OUT0     (GpioDataRegs.GPBCLEAR.bit.GPIO48=1)    //����GPIO4Ϊ�͵�ƽ
	#define GPIO10_OUT1     (GpioDataRegs.GPBSET.bit.GPIO49=1)      //����GPIO5Ϊ�ߵ�ƽ
    #define GPIO10_OUT0     (GpioDataRegs.GPBCLEAR.bit.GPIO49=1)    //����GPIO5Ϊ�͵�ƽ
	#define GPIO11_OUT1     (GpioDataRegs.GPBSET.bit.GPIO50=1)      //����GPIO6Ϊ�ߵ�ƽ
    #define GPIO11_OUT0     (GpioDataRegs.GPBCLEAR.bit.GPIO50=1)    //����GPIO6Ϊ�͵�ƽ
	#define GPIO12_OUT1     (GpioDataRegs.GPBSET.bit.GPIO51=1)      //����GPIO7Ϊ�ߵ�ƽ
    #define GPIO12_OUT0    (GpioDataRegs.GPBCLEAR.bit.GPIO51=1)     //����GPIO7Ϊ�͵�ƽ

	#define SENSOR0     (GpioDataRegs.GPADAT.bit.GPIO0)     //����GPIO0Ϊ�ߵ�ƽ
	#define SENSOR1     (GpioDataRegs.GPADAT.bit.GPIO1)     //����GPIO1Ϊ�ߵ�ƽ
	#define SENSOR2     (GpioDataRegs.GPADAT.bit.GPIO2)     //����GPIO2Ϊ�ߵ�ƽ
	#define SENSOR3     (GpioDataRegs.GPADAT.bit.GPIO3)     //����GPIO3Ϊ�ߵ�ƽ
	#define SENSOR4     (GpioDataRegs.GPADAT.bit.GPIO11)     //����GPIO0Ϊ�ߵ�ƽ
	#define SENSOR5     (GpioDataRegs.GPADAT.bit.GPIO12)     //����GPIO1Ϊ�ߵ�ƽ
	#define SENSOR6     (GpioDataRegs.GPADAT.bit.GPIO13)     //����GPIO2Ϊ�ߵ�ƽ
	#define SENSOR7     (GpioDataRegs.GPADAT.bit.GPIO14)     //����GPIO3Ϊ�ߵ�ƽ
	#define SENSOR8     (GpioDataRegs.GPADAT.bit.GPIO22)     //����GPIO0Ϊ�ߵ�ƽ
	#define SENSOR9     (GpioDataRegs.GPADAT.bit.GPIO23)     //����GPIO1Ϊ�ߵ�ƽ
	#define SENSOR10    (GpioDataRegs.GPADAT.bit.GPIO24)     //����GPIO2Ϊ�ߵ�ƽ
	#define SENSOR11    (GpioDataRegs.GPADAT.bit.GPIO25)     //����GPIO3Ϊ�ߵ�ƽ

	#define XINT1       (GpioDataRegs.GPADAT.bit.GPIO8)     //����GPIO0Ϊ�ߵ�ƽ
	#define XINT2       (GpioDataRegs.GPADAT.bit.GPIO9)     //����GPIO1Ϊ�ߵ�ƽ
	#define XINT3       (GpioDataRegs.GPADAT.bit.GPIO10)     //����GPIO2Ϊ�ߵ�ƽ

#endif

////////////////////////////////////ͨ��Э�鶨��//////////////////////////////////////
//����������Ϣ����//
#define Cmd_Rx_Head       '$'      //���յ�����ͷ
#define Cmd_Rx_End         0x0D    //���յ����ݽ���λ
#define Cmd_Rx_Type       'H'      //���յ��豸����λ��H���������


#define Rx_Head_OK         0       //��������ͷ״̬��״̬�Ĵ�����λ��
#define Rx_Long_OK         1       //���������״̬��״̬�Ĵ�����λ��
#define Rx_Type_OK         2       //�����������״̬��״̬�Ĵ�����λ��
#define Rx_Num_OK          3       //������������״̬��״̬�Ĵ�����λ��
#define Rx_Buff_OK         4       //�����������״̬��״̬�Ĵ�����λ��
#define Rx_Check_OK        5       //��������У���״̬��״̬�Ĵ�����λ��
#define Rx_End_OK          6       //�����������λ״̬��״̬�Ĵ�����λ��
#define Rx_Message         7       //���ݽ���״̬��״̬�Ĵ�����λ��

#define Cmd_Max_Long      99       //�������ݵ����������

//�ظ���ʽ�궨��//
#define Cmd_Head_Bit       0       //ͷ
#define Cmd_Long_Bit       1       //����״̬�Ĵ����ĳ���ֵλ
#define Cmd_Long_Num       2       //���ȵĸ���
#define Cmd_Type_Bit       3       //��������λ
#define Cmd_Fun_Bit        4       //���ݹ���λ
#define Cmd_Buff_Bit       5       //������Ϣλ
#define Cmd_Check_Bit      6       //ϵͳ����У�����ʼλ
 
////////////////////////////��������궨����/////////////////////////////
//������п��ƺ�������
#define  X         (0x01)
#define  Y         (0x02)
#define  Z         (0x03)
#define  R         (0x04)
#define  XY        (0x05)
#define  ZR        (0x06)
#define  XYZR      (0x07)

//���X�ļĴ�����ַ
#define  Motor_REG_MASK                  (0x0001)
#define  Motor_X_Clock_REG               (0x1100)
#define  Motor_X_CW_REG                  (0x1200)
#define  Motor_X_OE_REG                  (0x1300)
#define  Motor_X_Counter_REG             (0x1400)
#define  Motor_X_Capture_Mode_REG        (0x1500)
#define  Motor_X_Run_Counter_REG         (0x1600)

//���Y�ļĴ�����ַ
#define  Motor_Y_Clock_REG               (0x2100)
#define  Motor_Y_CW_REG                  (0x2200)
#define  Motor_Y_OE_REG                  (0x2300)
#define  Motor_Y_Counter_REG             (0x2400)
#define  Motor_Y_Capture_Mode_REG        (0x2500)
#define  Motor_Y_Run_Counter_REG         (0x2600)

//���Z�ļĴ�����ַ
#define  Motor_Z_Clock_REG               (0x3100)
#define  Motor_Z_CW_REG                  (0x3200)
#define  Motor_Z_OE_REG                  (0x3300)
#define  Motor_Z_Counter_REG             (0x3400)
#define  Motor_Z_Capture_Mode_REG        (0x3500)
#define  Motor_Z_Run_Counter_REG         (0x3600)

//���R�ļĴ�����ַ
#define  Motor_R_Clock_REG               (0x4100)
#define  Motor_R_CW_REG                  (0x4200)
#define  Motor_R_OE_REG                  (0x4300)
#define  Motor_R_Counter_REG             (0x4400)
#define  Motor_R_Capture_Mode_REG        (0x4500)
//#define  Motor_R_Run_Counter_REG       (0x4600)
#define  Motor_R_Origin                  (0x4600)

#define  Motor_Run                       (0x0001)
#define  Motor_Stop                 	 (0x0000)

/////////////////////////////������������///////////////////////////////////
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

///////////////////�����˻�е�˶���Χ�����������ݻ�е���嶨�壩///////////////////
#define max_x    140.00                  //X����������Ƕ�
#define min_x   -140.00                  //X���������С�Ƕ�
#define max_y    135.00                  //Y����������Ƕ�
#define min_y   -135.00                  //Y���������С�Ƕ�
#define max_z    100.00                  //Z�������������
#define min_z    0.00                    //Z���������С����
#define max_r    360.00                  //R����������Ƕ�
#define min_r   -360.00                  //R���������С�Ƕ�

/******************************************�ṹ�嶨������*******************************************/
//���ݽ���ͨ�Ÿ�ʽ����
typedef struct
    {
     unsigned char Cmd_Head;             //ͷ
     unsigned char Cmd_Long[2];          //���ݳ���
     unsigned char Cmd_Type;             //�豸����
     unsigned char Cmd_Fun;              //����λ
     unsigned char Cmd_Buff[99];         //����ֵ
     unsigned char Cmd_Check[4];         //У���
     unsigned char Cmd_End;              //β
    }SCI_Cmd_TypeDef;

//���ݷ��͸�ʽ����
typedef struct
    {
     unsigned char Cmd_Head;             //ͷ
     unsigned char Cmd_Long[2];          //���ݳ���
     unsigned char Cmd_Type;             //�豸����
     unsigned char Cmd_Fun;              //����λ
     unsigned char Cmd_Buff;             //����ֵ
     unsigned char Cmd_Check[4];         //У���
     unsigned char Cmd_End;              //β
    }SCI_TX_Type;

//�������ݶ���
typedef struct
    {
	 unsigned char Tx_Flag;              //���ͱ�־λ
	 unsigned char Tx_Counter;           //�������ݼ���
	 unsigned char Tx_Buff[99];          //���ͻ�����
	 unsigned char Rx_FLag;              //���ձ�־λ
	 unsigned char Rx_Status;            //����״̬
	 unsigned char Rx_Counter;           //�������ݼ���
	 unsigned char Rx_Counter_T;         //ת��������Ϊ�׼�������ʽ
	 unsigned char Rx_Message_Long;      //�������ݰ��ĳ��ȣ��ӳ��ȸ�λ������λ
	 unsigned char Rx_Buff[99];          //���ջ�����
	 unsigned char Temp;
	 int           Check_Value;
	 unsigned char Check_Buff[4];
    }SCI_Data_TypeDef;

//�˶���Χ��ʽ����
typedef struct
    {
     float Max_XS;                        //һ�����Ƕ�
     float Min_XS;                        //һ����С�Ƕ�
     float Max_YL;                        //�������Ƕ�
     float Min_YL;                        //������С�Ƕ�
     float Max_ZU;                        //�������Ƕ�
     float Min_ZU;                        //������С�Ƕ�
     float Max_RR;                        //�������Ƕ�
     float Min_RR;                        //������С�Ƕ�
     float Max_BB;                        //�������Ƕ�
     float Min_BB;                        //������С�Ƕ�
     float Max_TT;                        //�������Ƕ�
     float Min_TT;                        //������С�Ƕ�
    }Robot_RANGE_Type;

//��������з�Χ�ṹ�嶨�壨����SCARA�����˲����洢����㣩
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
//�˶���Χ��ʽ����
typedef struct
    {
     float Arm_XS;                       //һ����Ч����
     float Arm_YL;                       //������Ч����
     float Arm_ZU;                       //������Ч����
     float Arm_RR;                       //������Ч����
     float Arm_BB;                       //������Ч����
     float Arm_TT;                       //������Ч����
    }DH_Parameters_Type;

//FPGA���Ƶ��������Ϣ��ʽ����
typedef struct
    {
     unsigned char Axis;                 //������е�����

     unsigned char Dir_X;                //X�������з���
     unsigned long Freq_X;               //X���������ٶ�
     unsigned long Num_X;                //X��������������

     unsigned char Dir_Y;                //Y�������з���
     unsigned long Freq_Y;               //Y���������ٶ�
     unsigned long Num_Y;                //Y��������������

     unsigned char Dir_Z;                //Z�������з���
     unsigned long Freq_Z;               //Z���������ٶ�
     unsigned long Num_Z;                //Z��������������

     unsigned char Dir_R;                //R�������з���
     unsigned long Freq_R;               //R���������ٶ�
     unsigned long Num_R;                //R��������������

     unsigned int  Run_Index;            //�岹���
    }FPGA_Run_Info_Type;

//�켣�滮������е���Ϣ��ʽ����
typedef struct
    {
   	 unsigned char Axis;                 //������е�����

   	 unsigned char Dir_X;                //X���˶�����
   	 float         Vel_X;                //X���˶��ٶ�
     float         Ang_X;                //X���˶��Ƕ�

   	 unsigned char Dir_Y;                //Y���˶�����
   	 float         Vel_Y;                //Y���˶��ٶ�
   	 float         Ang_Y;                //Y���˶��Ƕ�

   	 unsigned char Dir_Z;                //Z���˶�����
   	 float         Vel_Z;                //Z���˶��ٶ�
   	 float         Ang_Z;                //Z���˶��Ƕ�

   	 unsigned char Dir_R;                //R���˶�����
   	 float         Vel_R;                //R���˶��ٶ�
   	 float         Ang_R;                //R���˶��Ƕ�

   	 unsigned int  Run_Index;            //�岹���
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

//�������״̬��ʽ����
typedef struct
    {
     unsigned char Robot_Rx_CMD_Reg;     //ϵͳ���е����� ��������ѯ����
     unsigned char Robot_BK_Reg;         //ϵͳ���������ɲ��״̬
     unsigned char Robot_Run_Reg;        //0x00 ����ϵͳ�˶���  0x01����ϵͳΪ����״̬ 0x02����ϵͳ�쳣����
     unsigned int  Robot_Cal_Reg;        //�����˶��ռ����ռ䷶Χ״̬���Ƿ��ڿռ䷶Χ��
     unsigned int  Robot_Motor_Reg;      //����������˶�״̬
     THETA_TypeDef Robot_Theta_Reg;
    }ROBOT_STATUS_REGS_TypeDef;

//SCARA�������㷨��ز���
typedef struct
    {
     float arm_one;                      //��۳���
     float arm_two;                      //С�۳���
     AXIS_RANGE_Type axis_range;         //�˶���Χ
    }SCARA_ARM_Type;

//ֱ�������ʽ���壨��Ϊ�ǶȺ;���ֵ��
typedef struct
    {
     float Descartes_X;                  //X��ֱ�����꣨�Ƕȣ�
     float Descartes_Y;                  //Y��ֱ�����꣨�Ƕȣ�
     float Descartes_Z;                  //Z��ֱ�����꣨�Ƕȣ�
     float Descartes_R;                  //R��ֱ�����꣨�Ƕȣ�
    }Descartes_Point_Type;

//ֱ�������ʽ���壨��Ϊ�ǶȺ;���ֵ��
typedef struct
    {
     float Descartes_XS;                 //X��ֱ�����꣨�Ƕȣ�
     float Descartes_YL;                 //Y��ֱ�����꣨�Ƕȣ�
     float Descartes_ZU;                 //Z��ֱ�����꣨�Ƕȣ�
     float Descartes_RR;                 //R��ֱ�����꣨�Ƕȣ�
     float Descartes_BB;                 //B��ֱ�����꣨�Ƕȣ�
     float Descartes_TT;                 //T��ֱ�����꣨�Ƕȣ�
    }Robot_Descartes_Point_Type;

//�ؽڿռ����� ��ǰ�������һ������ֵ
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

//�ѿ������� ��ǰ�������һ������ֵ
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
//////////////////////////////////28335ϵͳ������������//////////////////////////////////
extern void P_Led_Init(void);                    //LED��ʼ��
extern void P_Gpio_Init(void);                   //GPIO��ʼ��
extern void P_UartA_Init(void);                  //����A��ʼ��
extern void P_UartC_Init(void);                  //����C��ʼ��
extern void Spi_FIFO_Init(void);                 //SPI FiFO��ʼ��
extern void Spi_Init(void);                      //SPI��ʼ��
extern void P_Board_Init(void);                  //ϵͳ������Ϣ��ʼ��

extern void SCIA_Data_Int(void);                 //����A���ݳ�ʼ��
extern void SCIC_Data_Int(void);                 //����C���ݳ�ʼ��
extern unsigned char SCIA_Tx(unsigned char*Send_Buff,unsigned int Send_Long);       //����A���ݷ���
extern unsigned char SCIC_Tx(unsigned char*Send_Buff,unsigned int Send_Long);       //����C���ݷ���

extern void Spi_Send(Uint16 txdata);             //SPI���ݷ���
extern Uint16 Spi_Rece(void);                    //SPI���ݽ���
extern void w25q256_reset(void);                 //w25q256 FlashоƬ��λ
extern Uint16 w25q256_read_reg1(void);           //��ȡFLASH�Ĵ���1
extern Uint16 w25q256_read_reg2(void);           //��ȡFLASH�Ĵ���2
extern Uint16 w25q256_read_reg3(void);           //��ȡFLASH�Ĵ���3
extern void w25q256_set_4addr(void);             //���ó�4�ֽڵ�ַģʽ
extern void w25q256_init(void);                  //w25q256 FlashоƬ��ʼ��
extern Uint32 w25q256_readid(void);              //��ȡFlash ID
extern void w25q256_write_enable(void);          //FLASHдʹ��
extern Uint16 w25q256_test_busy(void);           //FLASH���æ
extern void w25q256_erase_chip(void);            //FLASHоƬ����
extern void w25q256_erase_sector(Uint32 addr);   //FLASH��������4K
extern void w25q256_read(Uint16 *tar_data, Uint32 addr, Uint32 n); //addr��ַ��ʼ������N���ֽ�
extern void w25q256_write(Uint16 *sou_data, Uint32 addr, Uint16 n);//��addr��ַ��ʼ����дN���ֽ�

extern unsigned char Str_To_Int(unsigned char *Str);                                //�ַ���ת�����Ⱥ���
extern unsigned int Check_Char_To_Int(unsigned char *Str);                          //У����ַ���ת����У�����ֵ����
extern unsigned int Get_Check_Num(unsigned char *Str,unsigned char Check_Long);     //����У��ͺ���
extern unsigned char Check_Int_To_Char(unsigned char Check_Int,unsigned char *Str); //У���ת�����ַ�������

extern void Motor_X_Set(unsigned long Freq, unsigned char Dir, unsigned long Num);    //X����������ú���
extern void Motor_Y_Set(unsigned long Freq, unsigned char Dir, unsigned long Num);    //Y����������ú���
extern void Motor_Z_Set(unsigned long Freq, unsigned char Dir, unsigned long Num);    //Z����������ú���
extern void Motor_R_Set(unsigned long Freq, unsigned char Dir, unsigned long Num);    //R����������ú���
extern void Motor_B_Set(unsigned long Freq, unsigned char Dir, unsigned long Num);    //Z����������ú���
extern void Motor_T_Set(unsigned long Freq, unsigned char Dir, unsigned long Num);    //R����������ú���

extern long long int Motor_X_Abs_Read();         //X�������������
extern long long int Motor_Y_Abs_Read();         //Y�������������
extern long long int Motor_Z_Abs_Read();         //Z�������������
extern long long int Motor_R_Abs_Read();         //R�������������
extern long long int Motor_B_Abs_Read();         //Z�������������
extern long long int Motor_T_Abs_Read();         //R�������������
extern unsigned int Motor_Return_State ();       //���ص��״̬����
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
extern void delay_loop();                                                           //��ʱ5����
extern void Delay(void);                                                            //833����
extern void My_Nop(void);                                                           //�����ʱ100����
extern void Delay_s(unsigned char Delay_Time);                                      //��ʱ1��
extern void Delay_ms(unsigned char Delay_Time);                                     //��ʱ1����

////////////////////////////////ȫ�ֱ�����������///////////////////////////////////
extern SCI_Data_TypeDef   SCIA_Data;                 //����A���ݶ���
extern SCI_Data_TypeDef   SCIC_Data;                 //����C���ݶ���
extern SCI_TX_Type  SCIA_Tx_Message;                 //����A���ݷ���
extern SCI_TX_Type  SCIC_Tx_Message;                 //����C���ݷ���
extern ROBOT_STATUS_REGS_TypeDef Robot_Run_Reg;      //������������Ϣ�ļĴ���
extern Robot_RANGE_Type * User_Range;                //�û��趨�˶���Χ����
extern float  User_Range_Buff[12];                   //�˶���Χ���ݻ���������
extern unsigned char User_Range_Str[72];             //�����û��趨�˶���Χ�ַ����洢
extern unsigned char  RAMCS[10];                       //RAMceshi
extern DH_Parameters_Type * Robot_DH;                //�۳�����
extern float  Robot_DH_Buff[6];                      //�۳�����������
extern unsigned char Robot_DH_Str[30];               //����DH�����ַ���
extern float Speed_Percent;                          //���������ٶȱ���
extern unsigned char Speed_Percent_Str[3];           //���������ٶȱ����ַ���
extern unsigned char CESHI[100] ;
extern unsigned char CESHIR[100] ;
extern unsigned int CESHIF[100] ;
extern THETA_JOINT_Type SCARA_Run_Theta;             //SCARA�ؽڿռ����궨��
extern FPGA_Run_Info_Type Trajetory_points;          //ֱ�������˶��˶�����
extern Motor_Run_Info_Type Motor_Run_points;         //�켣�滮�����������
extern unsigned char  Auxiliary_Fun;                 //���ڴ������и�������λ
extern SCI_Cmd_TypeDef *SCI_CMD_Message;             //���ڴ���������
extern SCI_Cmd_TypeDef SCI_CMD_Message1;             //���ڴ���������
extern int Cmd_Tx_Long;                              //�жϷ��ͳ���
extern unsigned char Execute_Flag;                   //ָ��ִ�б�־λ
extern unsigned int AC;
extern SCARA_ARM_Type SCARA_DH;                      //SCARA������DH����
extern POSE_DECARE_Type SCARA_Decare;                //�˶�����ת���ѿ�����Ϣ
extern unsigned char Answer_Flag;                    //������Ϣ�洢ʱ����ָ��ظ���־
extern Robot_Descartes_Point_Type Now_Point;         //����λ�õ㶨��

//����ֵλ��ʹ�ܼĴ�����ַ
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
