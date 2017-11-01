#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "PlatForm.h"
#include "control.h"
#include "math.h"

/************************************************************
* 函数名称：main
* 输入参数：无
* 输出参数：无
* 返 回 值 ：无
* 功       能 ：主程序
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void main(void)
{
	P_Board_Init();                                          //配置系统信息参数初始化
	SCIA_Data_Int();                                         //串口A数据初始化
	SCIC_Data_Int();                                         //串口A数据初始化

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
			LED1_L;                 //LED1灯亮
			SCI_RX_Message_Process(SCIC_Data.Rx_Buff,
					               &Robot_Run_Reg,
					               &SCIC_Data.Tx_Buff[0]);   //串口C接收数据处理
			SCI_Command_Execute(&Robot_Run_Reg);             //数据指令执行
			LED1_H;                 //LED1灯亮
		}
		if(SCIA_Data.Rx_FLag==0x0001)
		{
			LED1_L;                 //LED1灯亮
			SCIA_RX_Message_Process(SCIA_Data.Rx_Buff,
					               &Robot_Run_Reg,
					               &SCIA_Data.Tx_Buff[0]);   //串口A接收数据处理
			SCIA_Command_Execute(&Robot_Run_Reg);             //数据指令执行
			LED1_H;                 //LED1灯亮
		}
	}
}





