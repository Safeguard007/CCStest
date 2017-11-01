#include "DSP2833x_Device.h"     // DSP281x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP281x Examples Include File
#include "PlatForm.h"
#include "control.h"
#include "math.h"

/************************************************************
* 函数名称：SCI_RX_Message_Process
* 输入参数：转换字符串
* 输出参数：无
* 返 回 值： 无
* 功       能：处理串口数据
* 版本说明： 历史版本：                         当前版本：
*        修改原因：
*        修改人日期：
*************************************************************/
void SCI_RX_Message_Process(unsigned char *Message_Buff,ROBOT_STATUS_REGS_TypeDef *Robot_Status,unsigned char *Send_Message)
{
    AC = 0;
	unsigned char Send_Buff1[]={'#','0','8','H','Z','Q','0','1','5','B',0x0d};     //应答字符串定义
	unsigned char Send_Buff2[]={'#','0','9','H','P','D','Q','0','1','5','B',0x0d}; //应答字符串定义
	unsigned char i;
	unsigned int Get_Check_Counter=0x0000;                           //字符串校验和初值定义
	unsigned char Reply_Flag = 0;                                    //串口应答标志位定义并赋初值为0

	Execute_Flag = 0;                                                //指令执行标志位为指令不发送
	SCI_CMD_Message = (SCI_Cmd_TypeDef *)(Message_Buff);             //将接收字符串根据接收通信协议格式强制转化并赋值
	if(((unsigned char)(SCIC_Data.Rx_Status&(1<<Rx_End_OK)) != 0x00)
      &&(unsigned char)((SCIC_Data.Rx_Status&(1<<Rx_Check_OK)) != 0x00)
      &&(SCI_CMD_Message->Cmd_Type == 'H'))                          //判断接收字符串设备类型位/结束位/校验位是否正确
	{
		Execute_Flag = 1;                                            //指令执行标志位为指令执行
		SCI_CMD_Message1 = *SCI_CMD_Message;
		switch(SCI_CMD_Message1.Cmd_Fun)                             //判断功能位字符
		{
		/*******************************CPU-LED**********************************/
		case 'L':
			Robot_Status->Robot_Rx_CMD_Reg = 'L';                    //
			break;
		/****************************GPIO****************************************/
		case 'G':
			Robot_Status->Robot_Rx_CMD_Reg = 'G';                    //
			if(SCI_CMD_Message1.Cmd_Buff[0] == 'I')                  //
				{
							Auxiliary_Fun = 'I';                                 //辅助功能位赋值
				}
				else if(SCI_CMD_Message1.Cmd_Buff[0] == 'O')             //
				{
							Auxiliary_Fun = 'O';                                 //辅助功能位赋值
				}
			break;
		/**********************************RAM**********************************/
		case 'R':
			Robot_Status->Robot_Rx_CMD_Reg = 'R';                    //
			break;
		/**********************************FLASH*******************************/
		case 'F':
			Robot_Status->Robot_Rx_CMD_Reg = 'F';                    //
			if(SCI_CMD_Message1.Cmd_Buff[0] == 'Q')                  //
			{
				Auxiliary_Fun = 'Q';                                 //
			}
			else if(SCI_CMD_Message1.Cmd_Buff[0] == 'W')             //
			{
				Auxiliary_Fun = 'W';                                 //
			}
			else if(SCI_CMD_Message1.Cmd_Buff[0] == 'R')             //
			{
				Auxiliary_Fun = 'R';                                 //
			}
			break;
		/**********************************SF**********************************/
		case 'S':
			Robot_Status->Robot_Rx_CMD_Reg = 'S';                    //
			break;
		/**********************************插板传感器**********************************/
		case 'C':
			Robot_Status->Robot_Rx_CMD_Reg = 'C';                    //
			break;
		/**********************************电机旋转**********************************/
		case 'D':
			Robot_Status->Robot_Rx_CMD_Reg = 'D';                    //
			break;
		/**********************************编码器&报警信息**********************************/
		case 'B':
			Robot_Status->Robot_Rx_CMD_Reg = 'B';                    //
			if(SCI_CMD_Message1.Cmd_Buff[0] == 'R')                  //
			{
				Auxiliary_Fun = 'R';                                 //
			}
			if(SCI_CMD_Message1.Cmd_Buff[0] == 'Q')                  //
			{
				Auxiliary_Fun = 'Q';                                 //
			}
			if(SCI_CMD_Message1.Cmd_Buff[0] == 'J')                  //报警信息
			{
				Auxiliary_Fun = 'J';                                 //
			}
			break;
		default:
		    break;
		}
	}
	else                                                             //接收字符串设备类型位/结束位/校验位不正确
	{
		Execute_Flag = 0;                                            //指令执行标志位为指令不执行
		Send_Buff1[4] = 'E';                                         //发送字符串第四位赋值为E
		Reply_Flag = 0x01;                                           //信息应答标志位为1
	}
	if(Reply_Flag == 0x01)                                           //判断应答标志位是否为1，是则发送应答字符串
	{
		Reply_Flag = 0x00;                                           //信息应答标志位为0
	    for(i=1;i<6;i++)                                             //计算发送字符串第1位到第5位的校验和并赋值
		{
			Get_Check_Counter+=Send_Buff1[i];
	 	}
	 	Check_Int_To_Char(Get_Check_Counter,&Send_Buff1[6]);         //将校验和数值转换为校验和字符串
	    memcpy(Send_Message,Send_Buff1,sizeof(Send_Buff1));          //将赋值好的字符串设定为发送字符串
		SCIC_Tx(Send_Message,sizeof(Send_Buff1));                    //字符串发送
		SCIC_Data.Rx_Status=0x00;                                    //系统接收状态位清零
		SCIC_Data_Int();
	}
	if(Reply_Flag == 0x02)                                           //判断应答标志位是否为2，是则发送应答字符串
	{
		Reply_Flag = 0x00;                                           //信息应答标志位为0
	    for(i=1;i<7;i++)                                             //计算发送字符串第1位到第6位的校验和并赋值
		{
			Get_Check_Counter+=Send_Buff2[i];
	 	}
	 	Check_Int_To_Char(Get_Check_Counter,&Send_Buff2[7]);         //将校验和数值转换为校验和字符串
	    memcpy(Send_Message,Send_Buff2,sizeof(Send_Buff2));          //将赋值好的字符串设定为发送字符串
		SCIC_Tx(Send_Message,sizeof(Send_Buff2));                    //字符串发送
		SCIC_Data.Rx_Status=0x00;                                    //系统接收状态位清零
		SCIC_Data_Int();
	}
}

/************************************************************
* 函数名称：SCI_Command_Execute
* 输入参数：无
* 输出参数：无
* 返 回 值： 无
* 功       能：根据处理后函数进行指令执行
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void SCI_Command_Execute(ROBOT_STATUS_REGS_TypeDef *Robot_Status)
{

	if(Execute_Flag == 1)                           //判断接收字符串设备类型位/结束位/校验位是否正确
	{
	    Execute_Flag = 0;
        switch(Robot_Status->Robot_Rx_CMD_Reg)      //判断系统运行命令位字符
	    {
            /***************************CPU-LED***************************/
		    case 'L':
		    	CPU_LED(&SCIC_Data.Tx_Buff[0]);
		        break;
	        /***************************GPIO_IO***************************/
			case 'G':
				if(Auxiliary_Fun == 'I')
				GPIO_I(&SCI_CMD_Message1.Cmd_Buff[1],&SCIC_Data.Tx_Buff[0]);
				if(Auxiliary_Fun == 'O')
				GPIO_O(&SCI_CMD_Message1.Cmd_Buff[1],&SCIC_Data.Tx_Buff[0]);
			    break;
		    /*****************************RAM****************************/
		    case 'R':
		    	RAM_WR(&SCI_CMD_Message1.Cmd_Buff[0],&SCIC_Data.Tx_Buff[0]);                               //复位运动
			    break;
		    /******************************FLASH***************************/
		    case 'F':
			    if(Auxiliary_Fun == 'Q')
			    	FLASH_Q(&SCIC_Data.Tx_Buff[0]);         //
			    if(Auxiliary_Fun == 'W')
			    	FLASH_W(&SCI_CMD_Message1.Cmd_Buff[1],&SCIC_Data.Tx_Buff[0]);            //
			    if(Auxiliary_Fun == 'R')
			    	FLASH_R(&SCIC_Data.Tx_Buff[0]);         //
			    break;

			/*****************************SF****************************/
			case 'S':
				SF_SG(&SCI_CMD_Message1.Cmd_Buff[0], &SCIC_Data.Tx_Buff[0]);        //
				break;
			/*****************************插板传感器****************************/
			case 'C':
				CGQ_ZT(&SCI_CMD_Message1.Cmd_Buff[0], &SCIC_Data.Tx_Buff[0]);             //
				break;
			/*****************************电机旋转****************************/
			case 'D':
				DJ_KZ(&SCI_CMD_Message1.Cmd_Buff[0], &SCIC_Data.Tx_Buff[0]);             //
				break;
			/******************************FLASH***************************/
			    case 'B':
				    if(Auxiliary_Fun == 'R')
				    	 BMQ_R(&SCI_CMD_Message1.Cmd_Buff[1],&SCIC_Data.Tx_Buff[0]);         //
				    if(Auxiliary_Fun == 'Q')
				    	BMQ_QL(&SCI_CMD_Message1.Cmd_Buff[1],&SCIC_Data.Tx_Buff[0]);            //
				    if(Auxiliary_Fun == 'J')
				    	QDQ_BJ(&SCI_CMD_Message1.Cmd_Buff[1],&SCIC_Data.Tx_Buff[0]);         //
				    break;
		    default:
			    break;
	    }
	}
}
/************************************************************
* 函数名称：SCIA_RX_Message_Process
* 输入参数：串口A转换字符串
* 输出参数：无
* 返 回 值： 无
* 功       能：处理串口数据
* 版本说明： 历史版本：                         当前版本：
*        修改原因：
*        修改人日期：
*************************************************************/
void SCIA_RX_Message_Process(unsigned char *Message_Buff,ROBOT_STATUS_REGS_TypeDef *Robot_Status,unsigned char *Send_Message)
{
	AC = 1;
	unsigned char Send_Buff1[]={'#','0','8','H','Z','Q','0','1','5','B',0x0d};     //应答字符串定义
	unsigned char Send_Buff2[]={'#','0','9','H','P','D','Q','0','1','5','B',0x0d}; //应答字符串定义
	unsigned char i;
	unsigned int Get_Check_Counter=0x0000;                           //字符串校验和初值定义
	unsigned char Reply_Flag = 0;                                    //串口应答标志位定义并赋初值为0

	Execute_Flag = 0;                                                //指令执行标志位为指令不发送
	SCI_CMD_Message = (SCI_Cmd_TypeDef *)(Message_Buff);             //将接收字符串根据接收通信协议格式强制转化并赋值
	if(((unsigned char)(SCIA_Data.Rx_Status&(1<<Rx_End_OK)) != 0x00)
      &&(unsigned char)((SCIA_Data.Rx_Status&(1<<Rx_Check_OK)) != 0x00)
      &&(SCI_CMD_Message->Cmd_Type == 'H'))                          //判断接收字符串设备类型位/结束位/校验位是否正确
	{
		Execute_Flag = 1;                                            //指令执行标志位为指令执行
		SCI_CMD_Message1 = *SCI_CMD_Message;
		switch(SCI_CMD_Message1.Cmd_Fun)                             //判断功能位字符
		{
		/*******************************CPU-LED**********************************/
		case 'L':
			Robot_Status->Robot_Rx_CMD_Reg = 'L';                    //
			break;
		/****************************GPIO****************************************/
		case 'G':
			Robot_Status->Robot_Rx_CMD_Reg = 'G';                    //
			if(SCI_CMD_Message1.Cmd_Buff[0] == 'I')                  //
				{
							Auxiliary_Fun = 'I';                                 //辅助功能位赋值
				}
				else if(SCI_CMD_Message1.Cmd_Buff[0] == 'O')             //
				{
							Auxiliary_Fun = 'O';                                 //辅助功能位赋值
				}
			break;
		/**********************************RAM**********************************/
		case 'R':
			Robot_Status->Robot_Rx_CMD_Reg = 'R';                    //
			break;
		/**********************************FLASH*******************************/
		case 'F':
			Robot_Status->Robot_Rx_CMD_Reg = 'F';                    //
			if(SCI_CMD_Message1.Cmd_Buff[0] == 'Q')                  //
			{
				Auxiliary_Fun = 'Q';                                 //
			}
			else if(SCI_CMD_Message1.Cmd_Buff[0] == 'W')             //
			{
				Auxiliary_Fun = 'W';                                 //
			}
			else if(SCI_CMD_Message1.Cmd_Buff[0] == 'R')             //
			{
				Auxiliary_Fun = 'R';                                 //
			}
			break;
		/**********************************SF**********************************/
		case 'S':
			Robot_Status->Robot_Rx_CMD_Reg = 'S';                    //
			break;
		/**********************************插板传感器**********************************/
		case 'C':
			Robot_Status->Robot_Rx_CMD_Reg = 'C';                    //
			break;
		/**********************************电机旋转**********************************/
		case 'D':
			Robot_Status->Robot_Rx_CMD_Reg = 'D';                    //
			break;
		/**********************************编码器&报警信息**********************************/
		case 'B':
			Robot_Status->Robot_Rx_CMD_Reg = 'B';                    //
			if(SCI_CMD_Message1.Cmd_Buff[0] == 'R')                  //
			{
				Auxiliary_Fun = 'R';                                 //
			}
			if(SCI_CMD_Message1.Cmd_Buff[0] == 'Q')                  //
			{
				Auxiliary_Fun = 'Q';                                 //
			}
			if(SCI_CMD_Message1.Cmd_Buff[0] == 'J')                  //报警信息
			{
				Auxiliary_Fun = 'J';                                 //
			}
			break;
		default:
		    break;
		}
	}
	else                                                             //接收字符串设备类型位/结束位/校验位不正确
	{
		Execute_Flag = 0;                                            //指令执行标志位为指令不执行
		Send_Buff1[4] = 'E';                                         //发送字符串第四位赋值为E
		Reply_Flag = 0x01;                                           //信息应答标志位为1
	}
	if(Reply_Flag == 0x01)                                           //判断应答标志位是否为1，是则发送应答字符串
	{
		Reply_Flag = 0x00;                                           //信息应答标志位为0
	    for(i=1;i<6;i++)                                             //计算发送字符串第1位到第5位的校验和并赋值
		{
			Get_Check_Counter+=Send_Buff1[i];
	 	}
	 	Check_Int_To_Char(Get_Check_Counter,&Send_Buff1[6]);         //将校验和数值转换为校验和字符串
	    memcpy(Send_Message,Send_Buff1,sizeof(Send_Buff1));          //将赋值好的字符串设定为发送字符串
		SCIA_Tx(Send_Message,sizeof(Send_Buff1));                    //字符串发送
		SCIA_Data.Rx_Status=0x00;                                    //系统接收状态位清零
		SCIA_Data_Int();
	}
	if(Reply_Flag == 0x02)                                           //判断应答标志位是否为2，是则发送应答字符串
	{
		Reply_Flag = 0x00;                                           //信息应答标志位为0
	    for(i=1;i<7;i++)                                             //计算发送字符串第1位到第6位的校验和并赋值
		{
			Get_Check_Counter+=Send_Buff2[i];
	 	}
	 	Check_Int_To_Char(Get_Check_Counter,&Send_Buff2[7]);         //将校验和数值转换为校验和字符串
	    memcpy(Send_Message,Send_Buff2,sizeof(Send_Buff2));          //将赋值好的字符串设定为发送字符串
		SCIA_Tx(Send_Message,sizeof(Send_Buff2));                    //字符串发送
		SCIA_Data.Rx_Status=0x00;                                    //系统接收状态位清零
		SCIA_Data_Int();
	}
}
/************************************************************
* 函数名称：SCIA_Command_Execute
* 输入参数：无
* 输出参数：无
* 返 回 值： 无
* 功       能：A根据处理后函数进行指令执行
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void SCIA_Command_Execute(ROBOT_STATUS_REGS_TypeDef *Robot_Status)
{

	if(Execute_Flag == 1)                           //判断接收字符串设备类型位/结束位/校验位是否正确
	{
	    Execute_Flag = 0;
        switch(Robot_Status->Robot_Rx_CMD_Reg)      //判断系统运行命令位字符
	    {
            /***************************CPU-LED***************************/
		    case 'L':
		    	CPU_LED(&SCIA_Data.Tx_Buff[0]);
		        break;
	        /***************************GPIO_IO***************************/
			case 'G':
				if(Auxiliary_Fun == 'I')
				GPIO_I(&SCI_CMD_Message1.Cmd_Buff[1],&SCIA_Data.Tx_Buff[0]);
				if(Auxiliary_Fun == 'O')
				GPIO_O(&SCI_CMD_Message1.Cmd_Buff[1],&SCIA_Data.Tx_Buff[0]);
			    break;
		    /*****************************RAM****************************/
		    case 'R':
		    	RAM_WR(&SCI_CMD_Message1.Cmd_Buff[0],&SCIA_Data.Tx_Buff[0]);                               //复位运动
			    break;
		    /******************************FLASH***************************/
		    case 'F':
			    if(Auxiliary_Fun == 'Q')
			    	FLASH_Q(&SCIA_Data.Tx_Buff[0]);         //
			    if(Auxiliary_Fun == 'W')
			    	FLASH_W(&SCI_CMD_Message1.Cmd_Buff[1],&SCIA_Data.Tx_Buff[0]);            //
			    if(Auxiliary_Fun == 'R')
			    	FLASH_R(&SCIA_Data.Tx_Buff[0]);         //
			    break;

			/*****************************SF****************************/
			case 'S':
				SF_SG(&SCI_CMD_Message1.Cmd_Buff[0], &SCIA_Data.Tx_Buff[0]);        //
				break;
			/*****************************插板传感器****************************/
			case 'C':
				CGQ_ZT(&SCI_CMD_Message1.Cmd_Buff[0], &SCIA_Data.Tx_Buff[0]);             //
				break;
			/*****************************电机旋转****************************/
			case 'D':
				DJ_KZ(&SCI_CMD_Message1.Cmd_Buff[0], &SCIA_Data.Tx_Buff[0]);             //
				break;
			/******************************FLASH***************************/
			    case 'B':
				    if(Auxiliary_Fun == 'R')
				    	 BMQ_R(&SCI_CMD_Message1.Cmd_Buff[1],&SCIA_Data.Tx_Buff[0]);         //
				    if(Auxiliary_Fun == 'Q')
				    	BMQ_QL(&SCI_CMD_Message1.Cmd_Buff[1],&SCIA_Data.Tx_Buff[0]);            //
				    if(Auxiliary_Fun == 'J')
				    	QDQ_BJ(&SCI_CMD_Message1.Cmd_Buff[1],&SCIA_Data.Tx_Buff[0]);         //
				    break;
		    default:
			    break;
	    }
	}
}

/************************************************************
* 函数名称：Information_Flash_Erase
* 输入参数：无
* 输出参数：无
* 功       能：FLASH数据复位
* 备       注：Information_Int
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Information_Flash_Erase(unsigned char *Send_Message)
{
	unsigned char Send_Buff[]={'#','0','8','H','I','S','0','1','4','C',0x0d};     //当前坐标信息回复字符串定义

	w25q256_erase_chip();                                          //芯片擦除
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //将赋值好的字符串设定为发送字符串
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //字符串发送
	SCIC_Data.Rx_Status=0x00;                                      //系统接收状态位清零
	SCIC_Data_Int();
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
/************************************************************
* 函数名称：Connection_Test
* 输入参数：无
* 输出参数：无
* 返 回 值： 无
* 功       能：发送通信连接测试回复指令
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Connection_Test(unsigned char *Send_Message)
{
	unsigned char Send_Buff[]={'#','0','8','H','C','S','0','1','4','6',0x0d};     //当前坐标信息回复字符串定义

	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //将赋值好的字符串设定为发送字符串
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //字符串发送
	SCIC_Data.Rx_Status=0x00;                                      //系统接收状态位清零
	SCIC_Data_Int();
}
