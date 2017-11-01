#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "PlatForm.h"
#include "control.h"
#include "math.h"

/************************************************************
* �������ƣ�main
* �����������
* �����������
* �� �� ֵ ����
* ��       �� ��������
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void main(void)
{
	P_Board_Init();                                          //����ϵͳ��Ϣ������ʼ��
	SCIA_Data_Int();                                         //����A���ݳ�ʼ��
	SCIC_Data_Int();                                         //����A���ݳ�ʼ��

	int i;
	for(i=0;i<5;i++)
	{
		LED1_H;
		LED2_H;
		LED3_H;
		Delay_ms(500);
		LED1_L;
		LED2_L;
		LED3_L;
		Delay_ms(500);
	}

	while(1)
	{
		if(SCIC_Data.Rx_FLag==0x0001)
		{
			LED1_L;                 //LED1����
			SCI_RX_Message_Process(SCIC_Data.Rx_Buff,
					               &Robot_Run_Reg,
					               &SCIC_Data.Tx_Buff[0]);   //����C�������ݴ���
			SCI_Command_Execute(&Robot_Run_Reg);             //����ָ��ִ��
			LED1_H;                 //LED1����
		}
		if(SCIA_Data.Rx_FLag==0x0001)
		{
			LED1_L;                 //LED1����
			SCIA_RX_Message_Process(SCIA_Data.Rx_Buff,
					               &Robot_Run_Reg,
					               &SCIA_Data.Tx_Buff[0]);   //����A�������ݴ���
			SCIA_Command_Execute(&Robot_Run_Reg);             //����ָ��ִ��
			LED1_H;                 //LED1����
		}
	}
}





