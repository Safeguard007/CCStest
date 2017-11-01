#include "DSP2833x_Device.h"     // DSP281x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP281x Examples Include File
#include "PlatForm.h"
#include "control.h"
#include "math.h"

/************************************************************
* �������ƣ�SCI_RX_Message_Process
* ���������ת���ַ���
* �����������
* �� �� ֵ�� ��
* ��       �ܣ�����������
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*        �޸�ԭ��
*        �޸������ڣ�
*************************************************************/
void SCI_RX_Message_Process(unsigned char *Message_Buff,ROBOT_STATUS_REGS_TypeDef *Robot_Status,unsigned char *Send_Message)
{
    AC = 0;
	unsigned char Send_Buff1[]={'#','0','8','H','Z','Q','0','1','5','B',0x0d};     //Ӧ���ַ�������
	unsigned char Send_Buff2[]={'#','0','9','H','P','D','Q','0','1','5','B',0x0d}; //Ӧ���ַ�������
	unsigned char i;
	unsigned int Get_Check_Counter=0x0000;                           //�ַ���У��ͳ�ֵ����
	unsigned char Reply_Flag = 0;                                    //����Ӧ���־λ���岢����ֵΪ0

	Execute_Flag = 0;                                                //ָ��ִ�б�־λΪָ�����
	SCI_CMD_Message = (SCI_Cmd_TypeDef *)(Message_Buff);             //�������ַ������ݽ���ͨ��Э���ʽǿ��ת������ֵ
	if(((unsigned char)(SCIC_Data.Rx_Status&(1<<Rx_End_OK)) != 0x00)
      &&(unsigned char)((SCIC_Data.Rx_Status&(1<<Rx_Check_OK)) != 0x00)
      &&(SCI_CMD_Message->Cmd_Type == 'H'))                          //�жϽ����ַ����豸����λ/����λ/У��λ�Ƿ���ȷ
	{
		Execute_Flag = 1;                                            //ָ��ִ�б�־λΪָ��ִ��
		SCI_CMD_Message1 = *SCI_CMD_Message;
		switch(SCI_CMD_Message1.Cmd_Fun)                             //�жϹ���λ�ַ�
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
							Auxiliary_Fun = 'I';                                 //��������λ��ֵ
				}
				else if(SCI_CMD_Message1.Cmd_Buff[0] == 'O')             //
				{
							Auxiliary_Fun = 'O';                                 //��������λ��ֵ
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
		/**********************************��崫����**********************************/
		case 'C':
			Robot_Status->Robot_Rx_CMD_Reg = 'C';                    //
			break;
		/**********************************�����ת**********************************/
		case 'D':
			Robot_Status->Robot_Rx_CMD_Reg = 'D';                    //
			break;
		/**********************************������&������Ϣ**********************************/
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
			if(SCI_CMD_Message1.Cmd_Buff[0] == 'J')                  //������Ϣ
			{
				Auxiliary_Fun = 'J';                                 //
			}
			break;
		default:
		    break;
		}
	}
	else                                                             //�����ַ����豸����λ/����λ/У��λ����ȷ
	{
		Execute_Flag = 0;                                            //ָ��ִ�б�־λΪָ�ִ��
		Send_Buff1[4] = 'E';                                         //�����ַ�������λ��ֵΪE
		Reply_Flag = 0x01;                                           //��ϢӦ���־λΪ1
	}
	if(Reply_Flag == 0x01)                                           //�ж�Ӧ���־λ�Ƿ�Ϊ1��������Ӧ���ַ���
	{
		Reply_Flag = 0x00;                                           //��ϢӦ���־λΪ0
	    for(i=1;i<6;i++)                                             //���㷢���ַ�����1λ����5λ��У��Ͳ���ֵ
		{
			Get_Check_Counter+=Send_Buff1[i];
	 	}
	 	Check_Int_To_Char(Get_Check_Counter,&Send_Buff1[6]);         //��У�����ֵת��ΪУ����ַ���
	    memcpy(Send_Message,Send_Buff1,sizeof(Send_Buff1));          //����ֵ�õ��ַ����趨Ϊ�����ַ���
		SCIC_Tx(Send_Message,sizeof(Send_Buff1));                    //�ַ�������
		SCIC_Data.Rx_Status=0x00;                                    //ϵͳ����״̬λ����
		SCIC_Data_Int();
	}
	if(Reply_Flag == 0x02)                                           //�ж�Ӧ���־λ�Ƿ�Ϊ2��������Ӧ���ַ���
	{
		Reply_Flag = 0x00;                                           //��ϢӦ���־λΪ0
	    for(i=1;i<7;i++)                                             //���㷢���ַ�����1λ����6λ��У��Ͳ���ֵ
		{
			Get_Check_Counter+=Send_Buff2[i];
	 	}
	 	Check_Int_To_Char(Get_Check_Counter,&Send_Buff2[7]);         //��У�����ֵת��ΪУ����ַ���
	    memcpy(Send_Message,Send_Buff2,sizeof(Send_Buff2));          //����ֵ�õ��ַ����趨Ϊ�����ַ���
		SCIC_Tx(Send_Message,sizeof(Send_Buff2));                    //�ַ�������
		SCIC_Data.Rx_Status=0x00;                                    //ϵͳ����״̬λ����
		SCIC_Data_Int();
	}
}

/************************************************************
* �������ƣ�SCI_Command_Execute
* �����������
* �����������
* �� �� ֵ�� ��
* ��       �ܣ����ݴ����������ָ��ִ��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void SCI_Command_Execute(ROBOT_STATUS_REGS_TypeDef *Robot_Status)
{

	if(Execute_Flag == 1)                           //�жϽ����ַ����豸����λ/����λ/У��λ�Ƿ���ȷ
	{
	    Execute_Flag = 0;
        switch(Robot_Status->Robot_Rx_CMD_Reg)      //�ж�ϵͳ��������λ�ַ�
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
		    	RAM_WR(&SCI_CMD_Message1.Cmd_Buff[0],&SCIC_Data.Tx_Buff[0]);                               //��λ�˶�
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
			/*****************************��崫����****************************/
			case 'C':
				CGQ_ZT(&SCI_CMD_Message1.Cmd_Buff[0], &SCIC_Data.Tx_Buff[0]);             //
				break;
			/*****************************�����ת****************************/
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
* �������ƣ�SCIA_RX_Message_Process
* �������������Aת���ַ���
* �����������
* �� �� ֵ�� ��
* ��       �ܣ�����������
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*        �޸�ԭ��
*        �޸������ڣ�
*************************************************************/
void SCIA_RX_Message_Process(unsigned char *Message_Buff,ROBOT_STATUS_REGS_TypeDef *Robot_Status,unsigned char *Send_Message)
{
	AC = 1;
	unsigned char Send_Buff1[]={'#','0','8','H','Z','Q','0','1','5','B',0x0d};     //Ӧ���ַ�������
	unsigned char Send_Buff2[]={'#','0','9','H','P','D','Q','0','1','5','B',0x0d}; //Ӧ���ַ�������
	unsigned char i;
	unsigned int Get_Check_Counter=0x0000;                           //�ַ���У��ͳ�ֵ����
	unsigned char Reply_Flag = 0;                                    //����Ӧ���־λ���岢����ֵΪ0

	Execute_Flag = 0;                                                //ָ��ִ�б�־λΪָ�����
	SCI_CMD_Message = (SCI_Cmd_TypeDef *)(Message_Buff);             //�������ַ������ݽ���ͨ��Э���ʽǿ��ת������ֵ
	if(((unsigned char)(SCIA_Data.Rx_Status&(1<<Rx_End_OK)) != 0x00)
      &&(unsigned char)((SCIA_Data.Rx_Status&(1<<Rx_Check_OK)) != 0x00)
      &&(SCI_CMD_Message->Cmd_Type == 'H'))                          //�жϽ����ַ����豸����λ/����λ/У��λ�Ƿ���ȷ
	{
		Execute_Flag = 1;                                            //ָ��ִ�б�־λΪָ��ִ��
		SCI_CMD_Message1 = *SCI_CMD_Message;
		switch(SCI_CMD_Message1.Cmd_Fun)                             //�жϹ���λ�ַ�
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
							Auxiliary_Fun = 'I';                                 //��������λ��ֵ
				}
				else if(SCI_CMD_Message1.Cmd_Buff[0] == 'O')             //
				{
							Auxiliary_Fun = 'O';                                 //��������λ��ֵ
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
		/**********************************��崫����**********************************/
		case 'C':
			Robot_Status->Robot_Rx_CMD_Reg = 'C';                    //
			break;
		/**********************************�����ת**********************************/
		case 'D':
			Robot_Status->Robot_Rx_CMD_Reg = 'D';                    //
			break;
		/**********************************������&������Ϣ**********************************/
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
			if(SCI_CMD_Message1.Cmd_Buff[0] == 'J')                  //������Ϣ
			{
				Auxiliary_Fun = 'J';                                 //
			}
			break;
		default:
		    break;
		}
	}
	else                                                             //�����ַ����豸����λ/����λ/У��λ����ȷ
	{
		Execute_Flag = 0;                                            //ָ��ִ�б�־λΪָ�ִ��
		Send_Buff1[4] = 'E';                                         //�����ַ�������λ��ֵΪE
		Reply_Flag = 0x01;                                           //��ϢӦ���־λΪ1
	}
	if(Reply_Flag == 0x01)                                           //�ж�Ӧ���־λ�Ƿ�Ϊ1��������Ӧ���ַ���
	{
		Reply_Flag = 0x00;                                           //��ϢӦ���־λΪ0
	    for(i=1;i<6;i++)                                             //���㷢���ַ�����1λ����5λ��У��Ͳ���ֵ
		{
			Get_Check_Counter+=Send_Buff1[i];
	 	}
	 	Check_Int_To_Char(Get_Check_Counter,&Send_Buff1[6]);         //��У�����ֵת��ΪУ����ַ���
	    memcpy(Send_Message,Send_Buff1,sizeof(Send_Buff1));          //����ֵ�õ��ַ����趨Ϊ�����ַ���
		SCIA_Tx(Send_Message,sizeof(Send_Buff1));                    //�ַ�������
		SCIA_Data.Rx_Status=0x00;                                    //ϵͳ����״̬λ����
		SCIA_Data_Int();
	}
	if(Reply_Flag == 0x02)                                           //�ж�Ӧ���־λ�Ƿ�Ϊ2��������Ӧ���ַ���
	{
		Reply_Flag = 0x00;                                           //��ϢӦ���־λΪ0
	    for(i=1;i<7;i++)                                             //���㷢���ַ�����1λ����6λ��У��Ͳ���ֵ
		{
			Get_Check_Counter+=Send_Buff2[i];
	 	}
	 	Check_Int_To_Char(Get_Check_Counter,&Send_Buff2[7]);         //��У�����ֵת��ΪУ����ַ���
	    memcpy(Send_Message,Send_Buff2,sizeof(Send_Buff2));          //����ֵ�õ��ַ����趨Ϊ�����ַ���
		SCIA_Tx(Send_Message,sizeof(Send_Buff2));                    //�ַ�������
		SCIA_Data.Rx_Status=0x00;                                    //ϵͳ����״̬λ����
		SCIA_Data_Int();
	}
}
/************************************************************
* �������ƣ�SCIA_Command_Execute
* �����������
* �����������
* �� �� ֵ�� ��
* ��       �ܣ�A���ݴ����������ָ��ִ��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void SCIA_Command_Execute(ROBOT_STATUS_REGS_TypeDef *Robot_Status)
{

	if(Execute_Flag == 1)                           //�жϽ����ַ����豸����λ/����λ/У��λ�Ƿ���ȷ
	{
	    Execute_Flag = 0;
        switch(Robot_Status->Robot_Rx_CMD_Reg)      //�ж�ϵͳ��������λ�ַ�
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
		    	RAM_WR(&SCI_CMD_Message1.Cmd_Buff[0],&SCIA_Data.Tx_Buff[0]);                               //��λ�˶�
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
			/*****************************��崫����****************************/
			case 'C':
				CGQ_ZT(&SCI_CMD_Message1.Cmd_Buff[0], &SCIA_Data.Tx_Buff[0]);             //
				break;
			/*****************************�����ת****************************/
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
* �������ƣ�Information_Flash_Erase
* �����������
* �����������
* ��       �ܣ�FLASH���ݸ�λ
* ��       ע��Information_Int
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void Information_Flash_Erase(unsigned char *Send_Message)
{
	unsigned char Send_Buff[]={'#','0','8','H','I','S','0','1','4','C',0x0d};     //��ǰ������Ϣ�ظ��ַ�������

	w25q256_erase_chip();                                          //оƬ����
	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
/************************************************************
* �������ƣ�Connection_Test
* �����������
* �����������
* �� �� ֵ�� ��
* ��       �ܣ�����ͨ�����Ӳ��Իظ�ָ��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void Connection_Test(unsigned char *Send_Message)
{
	unsigned char Send_Buff[]={'#','0','8','H','C','S','0','1','4','6',0x0d};     //��ǰ������Ϣ�ظ��ַ�������

	memcpy(Send_Message,Send_Buff,sizeof(Send_Buff));              //����ֵ�õ��ַ����趨Ϊ�����ַ���
	SCIC_Tx(Send_Message,sizeof(Send_Buff));                       //�ַ�������
	SCIC_Data.Rx_Status=0x00;                                      //ϵͳ����״̬λ����
	SCIC_Data_Int();
}
