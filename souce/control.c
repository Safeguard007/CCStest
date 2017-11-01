#include "DSP2833x_Device.h"     // DSP281x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP281x Examples Include File
#include "PlatForm.h"
#include "control.h"
#include "math.h"
#include "stdio.h"
int i;




/************************************************************
* �������ƣ�CPU_LED
* ���������1
* ���������
* �� �� ֵ��
* ��       �ܣ���CPUƬ��LED���в���
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void CPU_LED(unsigned char *Send_Message)
{

	unsigned char Send_Buff[]={'#','0','9','H','L','E','D','0','1','8','6',0x0d};
	int ii;
	if(AC == 0)
	{
		memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
		SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
		SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
		SCIC_Data_Int();
	}
	if(AC == 1)
	{
		memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
		SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
		SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
		SCIA_Data_Int();
	}
	for(ii=0;ii<5;ii++)
	{
		Delay_ms(500);          //��ʱ500����
		LED1_H;                 //LED1����
		LED2_H;                 //LED1����
		LED3_H;                 //LED1����
		Delay_ms(500);          //��ʱ500����
		LED1_L;                 //LED1����
		LED2_L;                 //LED1����
		LED3_L;                 //LED1����
	}

}
/************************************************************
* �������ƣ�GPIO_O
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ���IO���ϵ�O���в���
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void GPIO_O(unsigned char *Str,unsigned char *Send_Message)
{
	unsigned char Send_Buff[]={'#','0','9','H','G','P','O','0','1','9','7',0x0d};
	if(AC == 0)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
	}
	if(AC == 1)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIA_Data_Int();
	}
	if(Str[0] == '0')
	{
	GPIO1_OUT0;             //���״̬Ϊ0
	GPIO2_OUT0;             //���״̬Ϊ0
	GPIO3_OUT0;             //���״̬Ϊ0
	GPIO4_OUT0;             //���״̬Ϊ0
	GPIO5_OUT0;             //���״̬Ϊ0
	GPIO6_OUT0;             //���״̬Ϊ0
	GPIO7_OUT0;             //���״̬Ϊ0
	GPIO8_OUT0;             //���״̬Ϊ0
	GPIO9_OUT0;             //���״̬Ϊ0
	GPIO10_OUT0;             //���״̬Ϊ0
	GPIO11_OUT0;             //���״̬Ϊ0
	GPIO12_OUT0;             //���״̬Ϊ0
	}

	if(Str[0] == '1')
	{
	GPIO1_OUT1;             //���״̬Ϊ1
	GPIO2_OUT1;             //���״̬Ϊ1
	GPIO3_OUT1;             //���״̬Ϊ1
	GPIO4_OUT1;             //���״̬Ϊ1
	GPIO5_OUT1;             //���״̬Ϊ1
	GPIO6_OUT1;             //���״̬Ϊ1
	GPIO7_OUT1;             //���״̬Ϊ1
	GPIO8_OUT1;             //���״̬Ϊ1
	GPIO9_OUT1;             //���״̬Ϊ1
	GPIO10_OUT1;             //���״̬Ϊ1
	GPIO11_OUT1;             //���״̬Ϊ1
	GPIO12_OUT1;             //���״̬Ϊ1
	}

}
/************************************************************
* �������ƣ�GPIO_I
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ���IO���ϵ�I���в���
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void GPIO_I(unsigned char *Str,unsigned char *Send_Message)
{
	int a;
	unsigned char Send_Buff[]={'#','1','0','H','G','P','I','0','0','1','8','F',0x0d};     //��ǰ������Ϣ�ظ��ַ�������
    if(Str[0] == '0')
    {
        a = SENSOR0;
	}
    if(Str[0] == '1')
    {
    	a = SENSOR1;
	}
    if(Str[0] == '2')
    {
    	a = SENSOR2;
	}
    if(Str[0] == '3')
    {
    	a = SENSOR3;
	}
    if(Str[0] == '4')
    {
        a = SENSOR4;
	}
    if(Str[0] == '5')
    {
    	a = SENSOR5;
	}
    if(Str[0] == '6')
    {
    	a = SENSOR6;
	}
    if(Str[0] == '7')
    {
    	a = SENSOR7;
	}
    if(Str[0] == '8')
    {
        a = SENSOR8;
	}
    if(Str[0] == '9')
    {
    	a = SENSOR9;
	}
    if(Str[0] == 'A')
    {
    	a = SENSOR10;
	}
    if(Str[0] == 'B')
    {
    	a = SENSOR11;
	}

    if(a == 0)
    	Send_Buff[7] = '0';
    else
    	Send_Buff[7] = '1';

/******************************�ַ�������*********************************/
	unsigned char Get_Check_Counter;
	for(i=1;i<8;i++)                                           //���㷢���ַ�����1λ����7λ��У��Ͳ���ֵ
    {
	Get_Check_Counter+=Send_Buff[i];
	}
	Check_Int_To_Char(Get_Check_Counter,&Send_Buff[8]);        //��У�����ֵת��ΪУ����ַ���

	if(AC == 0)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
	}
	if(AC == 1)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIA_Data_Int();
	}
}
/************************************************************
* �������ƣ�RAM_WR
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ���RAM���ж�д����
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void RAM_WR(unsigned char *CESHIR,unsigned char *Send_Message)
{
	memcpy(RAMCS,CESHIR,sizeof(RAMCS));             //�����ַ����洢��������Ϣ��ѯ�ظ�����
	unsigned char Send_Buff[]={'#','1','7','H','R','0','9','8','7','6','5','4','3','2','1','5','5','5','5',0x0d};     //��ǰ������Ϣ�ظ��ַ�������
	for(i=0;i<10;i++)
	{
		Send_Buff[i+5] = RAMCS[i];
	}
/******************************�ַ�������*********************************/
	unsigned char Get_Check_Counter;
	for(i=1;i<15;i++)                                           //���㷢���ַ�����1λ����14λ��У��Ͳ���ֵ
    {
		Get_Check_Counter+=Send_Buff[i];
	}
	Check_Int_To_Char(Get_Check_Counter,&Send_Buff[15]);        //��У�����ֵת��ΪУ����ַ������ڵ�ʮ��λ���Ժ�
	if(AC == 0)
	{
		memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
		SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
		SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
		SCIC_Data_Int();
	}
	if(AC == 1)
	{
		memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
		SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
		SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
		SCIA_Data_Int();
	}
}
/************************************************************
* �������ƣ�FLASH_Q
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ���FLASH�����������
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void FLASH_Q(unsigned char *Send_Message)
    {
	w25q256_erase_sector(0X0000);                              //�����˶���Χ��������
	unsigned char Send_Buff[]={'#','0','9','H','F','Q','O','0','1','7','8',0x0d};

	if(AC == 0)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
	}
	if(AC == 1)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIA_Data_Int();
	}
	}
/************************************************************
* �������ƣ�FLASH_W
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ���FLASH����д����
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void FLASH_W(unsigned char *CESHIR,unsigned char *Send_Message)
{
	memcpy(CESHIF,CESHIR,10);             //�����ַ����洢��������Ϣ��ѯ�ظ�����
    w25q256_write((Uint16 *)CESHIF, 0X0000, 10);       //���˶���Χ�ַ���д���Ӧ��ַflash
	unsigned char Send_Buff[]={'#','0','9','H','F','W','O','0','1','7','8',0x0d};
	if(AC == 0)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
	}
	if(AC == 1)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIA_Data_Int();
	}
}
/************************************************************
* �������ƣ�FLASH_R
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ���FLASH���ж�����
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void FLASH_R(unsigned char *Send_Message)
{
	int i;
	int j;
	unsigned int a;
	unsigned int zhi[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//int ������
	unsigned char zhc[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};//char ������
	w25q256_read((Uint16 *)CESHIF, 0X0000, 10);
	unsigned  char Send_Buff[]={'#','0','9','H','R','0','9','8','7','6','5','4','3','2','1','5','5','5','5',0x0d};     //��ǰ������Ϣ�ظ��ַ�������

for(i=0;i<10;i++)
{
	for(j=0;j<16;j++)                                              //jΪ�ַ������ַ�����
	{
		a = CESHIF[i];
		a = a & 0xf;
	    if(zhi[j] == a)
			{
				Send_Buff[i+5] = zhc[j];
			}
	}
}
/******************************�ַ�������*********************************/
	unsigned char Get_Check_Counter;
for(i=1;i<14;i++)                                           //���㷢���ַ�����1λ����14λ��У��Ͳ���ֵ
    {
	Get_Check_Counter+=Send_Buff[i];
	}
	Check_Int_To_Char(Get_Check_Counter,&Send_Buff[15]);        //��У�����ֵת��ΪУ����ַ���
	if(AC == 0)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
	}
	if(AC == 1)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIA_Data_Int();
	}
}
/************************************************************
* �������ƣ�SF_SG
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ����ŷ����迪��ָ��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void SF_SG(unsigned char *CESHIR,unsigned char *Send_Message)
{
	unsigned char Send_Buff1[]={'#','0','9','H','S','F','C','0','1','7','8',0x0d};
    unsigned char Send_Buff[]={'#','0','9','H','S','F','O','0','1','7','8',0x0d};
	if( CESHIR[0] == '1')
	{
	 * SN = 0xFFF;
	 if(AC == 0)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
	}
	if(AC == 1)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIA_Data_Int();
	}
	}
	if( CESHIR[0] == '0')
	{
	 * SN = 0x000;
	 if(AC == 0)
	{
	memcpy(Send_Message,Send_Buff1,sizeof(Send_Buff1));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff1));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
	}
	if(AC == 1)
	{
	memcpy(Send_Message,Send_Buff1,sizeof(Send_Buff1));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIA_Tx(Send_Message,sizeof(Send_Buff1));                       //�ַ�������
	SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIA_Data_Int();
	}
	}


}
/************************************************************
* �������ƣ�CGQ_ZT
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ��Ը��ᴫ����״̬���в�ѯ
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void CGQ_ZT(unsigned char *CESHIR,unsigned char *Send_Message)
{
	unsigned char Send_Buff[]={'#','0','8','H','C','0','0','1','8','F',0x0d};     //��ǰ������Ϣ�ظ��ַ�������
	int a;
    int j;
	unsigned int zhi[]={0,1,2,3,4,5,6,7,8,9};//int ������
    unsigned char zhc[]={'0','1','2','3','4','5','6','7','8','9'};//char ������
	if(CESHIR[0] == '1')
	{
		a = * State_ADD&0x3;
	}
	if(CESHIR[0] == '2')
	{
		a = * State_ADD&0xC;
	}
	if(CESHIR[0] == '3')
	{
		a = * State_ADD&0x30;
	}
	if(CESHIR[0] == '4')
	{
		a = * State_ADD&0xC0;
	}
	if(CESHIR[0] == '5')
	{
		a = * State_ADD&0x300;
	}
	if(CESHIR[0] == '6')
	{
		a = * State_ADD&0xC00;
	}
	for(j=0;j<10;j++)                                              //jΪ�ַ������ַ�����
	{
	    if(zhi[j] == a)
			{
				Send_Buff[5] = zhc[j];
			}
	}

/******************************�ַ�������*********************************/

	unsigned char Get_Check_Counter;
for(i=1;i<6;i++)                                           //���㷢���ַ�����1λ����6λ��У��Ͳ���ֵ
    {
	Get_Check_Counter+=Send_Buff[i];
	}
	Check_Int_To_Char(Get_Check_Counter,&Send_Buff[6]);        //��У�����ֵת��ΪУ����ַ���
	if(AC == 0)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
	}
	if(AC == 1)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIA_Data_Int();
	}
}
/************************************************************
* �������ƣ�DJ_KZ
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ��Ը����������˶�ָ��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void DJ_KZ(unsigned char *CESHIR,unsigned char *Send_Message)
{
	if(CESHIR[0] == '1')
	{
		Motor_X_Set(50000,Motor_X_Run_Right,9000);
		Motor_Set_EN (0X01);
		Delay_s(5);
		Motor_X_Set(100000,Motor_X_Run_Left,18000);
		Motor_Set_EN (0X01);
		Delay_s(5);
		Motor_X_Set(200000,Motor_X_Run_Right,36000);
		Motor_Set_EN (0X01);
		Delay_s(5);
		Motor_X_Set(400000,Motor_X_Run_Left,72000);
		Motor_Set_EN (0X01);
		Delay_s(5);
	}
	if(CESHIR[0] == '2')
	{
		Motor_Y_Set(50000,Motor_Y_Run_Right,9000);
		Motor_Set_EN (0X02);
		Delay_s(5);
		Motor_Y_Set(100000,Motor_Y_Run_Left,18000);
		Motor_Set_EN (0X02);
		Delay_s(5);
		Motor_Y_Set(200000,Motor_Y_Run_Right,36000);
		Motor_Set_EN (0X02);
		Delay_s(5);
		Motor_Y_Set(400000,Motor_Y_Run_Left,72000);
		Motor_Set_EN (0X02);
		Delay_s(5);

	}
	if(CESHIR[0] == '3')
	{
		Motor_Z_Set(50000, Motor_Z_Run_Down ,9000);
		Motor_Set_EN (0X04);
		Delay_s(5);
		Motor_Z_Set(100000,Motor_Z_Run_Up,18000);
		Motor_Set_EN (0X04);
		Delay_s(5);
		Motor_Z_Set(200000, Motor_Z_Run_Down ,36000);
		Motor_Set_EN (0X04);
		Delay_s(5);
		Motor_Z_Set(400000,Motor_Z_Run_Up,72000);
		Motor_Set_EN (0X04);
		Delay_s(5);
	}
	if(CESHIR[0] == '4')
	{
		Motor_R_Set(50000,Motor_R_Run_Right,9000);
		Motor_Set_EN (0X08);
		Delay_s(5);
		Motor_R_Set(100000,Motor_R_Run_Left,18000);
		Motor_Set_EN (0X08);
		Delay_s(5);
		Motor_R_Set(200000,Motor_R_Run_Right,36000);
		Motor_Set_EN (0X08);
		Delay_s(5);
		Motor_R_Set(400000,Motor_R_Run_Left,72000);
		Motor_Set_EN (0X08);
		Delay_s(5);

	}
	if(CESHIR[0] == '5')
	{
		Motor_B_Set(50000,Motor_R_Run_Right,9000);
		Motor_Set_EN (0X10);
		Delay_s(5);
		Motor_B_Set(100000,Motor_R_Run_Left,18000);
		Motor_Set_EN (0X10);
		Delay_s(5);
		Motor_B_Set(200000,Motor_R_Run_Right,36000);
		Motor_Set_EN (0X10);
		Delay_s(5);
		Motor_B_Set(400000,Motor_R_Run_Left,72000);
		Motor_Set_EN (0X10);
	}
	if(CESHIR[0] == '6')
	{
		Motor_T_Set(50000,Motor_R_Run_Right,9000);
		Motor_Set_EN (0X20);
		Delay_s(5);
		Motor_T_Set(100000,Motor_R_Run_Left,18000);
		Motor_Set_EN (0X20);
		Delay_s(5);
		Motor_T_Set(200000,Motor_R_Run_Right,36000);
		Motor_Set_EN (0X20);
		Delay_s(5);
		Motor_T_Set(400000,Motor_R_Run_Left,72000);
		Motor_Set_EN (0X20);
		Delay_s(5);
	}
	unsigned char Send_Buff[]={'#','0','9','H','D','J','O','0','1','8','E',0x0d};
	if(AC == 0)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
	}
	if(AC == 1)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIA_Data_Int();
	}
}
/************************************************************
* �������ƣ�BMQ_QL
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ��Ը�������������������
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void BMQ_QL(unsigned char *CESHIR,unsigned char *Send_Message)
{
	if(CESHIR[0] == '1')
	{
		Motor_X_AbsReset_Set();
	}
	if(CESHIR[0] == '2')
	{
		Motor_Y_AbsReset_Set();
	}
	if(CESHIR[0] == '3')
	{
		Motor_Z_AbsReset_Set();
	}
	if(CESHIR[0] == '4')
	{
		Motor_R_AbsReset_Set();
	}
	if(CESHIR[0] == '5')
	{
		Motor_B_AbsReset_Set();
	}
	if(CESHIR[0] == '6')
	{
		Motor_T_AbsReset_Set();
	}
	unsigned char Send_Buff[]={'#','0','9','H','Q','L','O','0','1','9','D',0x0d};
	if(AC == 0)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
	}
	if(AC == 1)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIA_Data_Int();
	}
}
/************************************************************
* �������ƣ�QDQ_BJ
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ��Ը������������в�ѯ
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void QDQ_BJ(unsigned char *CESHIR,unsigned char *Send_Message)
{
	unsigned int zhi[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//int ������
    unsigned char zhc[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};//char ������
unsigned char Get_Check_Counter;
unsigned char Send_Buff[]={'#','0','9','H','B','J','O','0','1','9','D',0x0d};
int b;
int a;
int j;
if(CESHIR[0] == '1')
{
	b = BJ_X_Read();
}
if(CESHIR[0] == '2')
{
	b = BJ_Y_Read();
}
if(CESHIR[0] == '3')
{
	b = BJ_Z_Read();
}
if(CESHIR[0] == '4')
{
	b = BJ_R_Read();
}
if(CESHIR[0] == '5')
{
	b = BJ_B_Read();
}
if(CESHIR[0] == '6')
{
	b = BJ_T_Read();
}


a = b&0x0f;
for(j=0;j<16;j++)                                              //jΪ�ַ������ַ�����
{
    if(zhi[j] == a)
		{
			Send_Buff[6] = zhc[j];
		}
}
/******************************�ַ�������*********************************/

for(i=1;i<7;i++)                                           //���㷢���ַ�����1λ����8λ��У��Ͳ���ֵ
{
Get_Check_Counter+=Send_Buff[i];
}
Check_Int_To_Char(Get_Check_Counter,&Send_Buff[7]);        //��У�����ֵת��ΪУ����ַ���
if(AC == 0)
{
memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
SCIC_Data_Int();
}
if(AC == 1)
{
memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
SCIA_Data_Int();
}
}
/************************************************************
* �������ƣ�BMQ_R
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ�
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void  BMQ_R(unsigned char *CESHIR,unsigned char *Send_Message)
{
	unsigned char Get_Check_Counter;
	int i;
	int j;
	long b;
	unsigned char Send_Buff[]={'#','1','7','H','Q','1','2','3','4','5','6','7','8','9','0','6','6','6','6',0x0d};
	char Str[10];
	if(CESHIR[0] == '1')
	{
		b = Motor_X_Abs_Read();
	}
	if(CESHIR[0] == '2')
	{
		b = Motor_Y_Abs_Read();
	}
	if(CESHIR[0] == '3')
	{
		b = Motor_Z_Abs_Read();
	}
	if(CESHIR[0] == '4')
	{
		b = Motor_R_Abs_Read();
	}
	if(CESHIR[0] == '5')
	{
		b = Motor_B_Abs_Read();
	}
	if(CESHIR[0] == '6')
	{
		b = Motor_T_Abs_Read();
	}
	sprintf(Str,"%010ld",b);
	for(j=0;j<10;j++)                                              //jΪ�ַ������ַ�����
	{
		Send_Buff[5+j] = Str[j];
	}
	for(i=1;i<15;i++)                                           //���㷢���ַ�����1λ����8λ��У��Ͳ���ֵ
	{
	Get_Check_Counter+=Send_Buff[i];
	}
	Check_Int_To_Char(Get_Check_Counter,&Send_Buff[15]);        //��У�����ֵת��ΪУ����ַ���
	if(AC == 0)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
	}
	if(AC == 1)
	{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIA_Data_Int();
	}
}
/************************************************************
* �������ƣ�C_R
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ�
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void  C_R(unsigned char Send_Buff[],unsigned char *Send_Message)
{
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
}
/************************************************************
* �������ƣ�A_R
* ���������
* ���������
* �� �� ֵ��
* ��       �ܣ�
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
* �����ˣ���˷
*************************************************************/
void  A_R(unsigned char Send_Buff[],unsigned char *Send_Message)
{
//	unsigned char a[];
//	a = Send_Buff;
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIA_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIA_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIA_Data_Int();
}
