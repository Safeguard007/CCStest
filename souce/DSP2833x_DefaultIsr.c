//###########################################################################
//
// FILE:	DSP2833x_DefaultIsr.c
//
// TITLE:	DSP2833x Device Default Interrupt Service Routines.
//
// This file contains shell ISR routines for the 2833x PIE vector table.
// Typically these shell ISR routines can be used to populate the entire PIE
// vector table during device debug.  In this manner if an interrupt is taken
// during firmware development, there will always be an ISR to catch it.
//
// As develpment progresses, these ISR rotuines can be eliminated and replaced
// with the user's own ISR routines for each interrupt.  Since these shell ISRs
// include infinite loops they will typically not be included as-is in the final
// production firmware.
//
//###########################################################################
// $TI Release: 2833x/2823x Header Files and Peripheral Examples V133 $
// $Release Date: June 8, 2012 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "control.h"
#include "PlatForm.h"

SCI_Cmd_TypeDef *ACK_SCI_Cmd;                                                //�Ա����������ݽ��ո�ʽ���и�ʽ��

// INT9.1
interrupt void SCIRXINTA_ISR(void)    // SCI-A
{
	unsigned char Get_Temp=0x00;
	Get_Temp=SciaRegs.SCIRXBUF.all;

    if(SCIA_Data.Rx_FLag==0x00)
	{
 		SCIA_Data.Rx_Buff[SCIA_Data.Rx_Counter]=Get_Temp;
	    //�����ݽ�����λ���λ��1
		SCIA_Data.Rx_Status|=(1<<Rx_Message);
        if(SCIA_Data.Rx_Counter==0)
		{
			if(SCIA_Data.Rx_Buff[SCIA_Data.Rx_Counter]==Cmd_Rx_Head)//�жϽ������ݵ�ͷ�Ƿ����Э�飬���������ݽ���״̬��λ����������
			{
				SCIA_Data.Rx_Counter++;
				SCIA_Data.Rx_Status|=(1<<Rx_Head_OK);
				SCIA_Data.Rx_Status&=~(1<<Rx_Message);//����������ݷ���ϵͳҪ�������λû������ �������ó�Ĭ��ֵ
				SCIC_Tx_Message.Cmd_Buff = SCIA_Data.Rx_Status;
			}
			else
			{
				SCIA_Data.Rx_Status&=~(1<<Rx_Head_OK);
			}
		}
	  	else
		{
			SCIA_Data.Rx_Counter++;
			if((SCIA_Data.Rx_Counter-1)==Cmd_Long_Num)//�����ǰ���յ������ݳ��ȵĵ�λ��������ݰ����Ƚ���ת��������Ĵ�����
			{
				SCIA_Data.Rx_Message_Long=Str_To_Int( & SCIA_Data.Rx_Buff[Cmd_Long_Bit]);
				if (SCIA_Data.Rx_Message_Long>Cmd_Max_Long)//�����յ��ĳ���ֵ�����������ݵ���󳤶ȣ������״̬�ĳ������㣬������λ
				{
					SCIA_Data.Rx_Status&=~(1<<Rx_Long_OK);
				}
			    else
				{
					SCIA_Data.Rx_Status|=(1<<Rx_Long_OK);
				}
			}
			if((SCIA_Data.Rx_Counter-1)>Cmd_Long_Num)//�����ǰ���ռ���ֵ���ڽ��յ����ݳ��ȵ�λ���ڼ���ֵ����������λ��У��ͣ����������ز���
			{

				if((SCIA_Data.Rx_Counter-1)== SCIA_Data.Rx_Message_Long + Cmd_Long_Num )//�������ֵ���ڽ��յ��ġ����ݳ���ֵ����������λ����ֵ
				{
					SCIA_Data.Rx_FLag=0x01;//���ձ�־λ��λ
                    if(SCIA_Data.Rx_Buff[(SCIA_Data.Rx_Counter-1)]==Cmd_Rx_End)//�жϽ���λ
					{
						SCIA_Data.Rx_Status|=(1<<Rx_End_OK);
						SCIA_Data.Check_Value=Get_Check_Num(&SCIA_Data.Rx_Buff[Cmd_Long_Bit],(unsigned char)((SCIA_Data.Rx_Counter-1)-5));//�ж�У���  �����У��͵�λ��Ϊ
						if(SCIA_Data.Check_Value== Check_Char_To_Int(&SCIA_Data.Rx_Buff[(SCIA_Data.Rx_Counter-1)-4]))
						{
							SCIA_Data.Rx_Status|=(1<<Rx_Check_OK);//У���״̬λ��λ
							SCIA_Data.Rx_Counter=0x00;//��ս��������ۼӱ���
							SCIA_Data.Rx_Message_Long=0x00;//���Ҫ���յ����ݳ��ȱ���
 						    ACK_SCI_Cmd=(SCI_Cmd_TypeDef *)SCIA_Data.Rx_Buff;
                            if((ACK_SCI_Cmd->Cmd_Type==Cmd_Rx_Type)&&(ACK_SCI_Cmd->Cmd_Fun=='?'))
							{
								if (ACK_SCI_Cmd->Cmd_Fun=='?')
								{
									SCIA_Data.Tx_Flag=0x01;
									SCIA_Data.Rx_FLag=0x02;//���ձ�־λ��λ
 						//			System_Quick_ACK(Robot_Run_Reg,&SCIA_Data.Tx_Buff[0]);
									SCIA_Data.Rx_Status=0x0000;
								}
							}
						}
						else
						{
							SCIA_Data.Rx_Status&=~(1<<Rx_Check_OK);//У���״̬λ���
						}
					}
					else
					{
						SCIA_Data.Rx_Status&=~(1<<Rx_End_OK);
					}
				}
			}
		}
	}
    PieCtrlRegs.PIEACK.all=0x0100;  //ʹ��ͬ�������ж��ܹ��õ���Ӧ
    EINT;  //��ȫ���ж�vcc
}

// INT9.2
interrupt void SCITXINTA_ISR(void)     // SCI-A
{
    if(SCIA_Data.Tx_Flag == 1)
    {
		SCIA_Data.Tx_Counter++;
        SciaRegs.SCITXBUF = SCIA_Data.Tx_Buff[SCIA_Data.Tx_Counter];
        if(	SCIA_Data.Tx_Counter ==  10)
        {
		  	SCIA_Data.Tx_Counter = 0;
		    SCIA_Data.Tx_Flag = 0;
			SCIA_Data.Rx_FLag=0x00;
        }
    }
    PieCtrlRegs.PIEACK.all=0x0100;  //ʹ��ͬ�������ж��ܹ��õ���Ӧ
    EINT;  //��ȫ���ж�
    //SCITXBUF�е���������TXSHF�Ĵ����������ݷ��ͳ�ȥ��TXRDY��־λ��1
}
// Note CPU-Timer1 ISR is reserved for TI use.
// Connected to INT13 of CPU (use MINT13 mask):
// Note CPU-Timer1 is reserved for TI use, however XINT13
// ISR can be used by the user.
// INT8.5

interrupt void SCIRXINTC_ISR(void)                                           // SCI-C
{
	unsigned char Get_Temp = 0x00;
	Get_Temp = ScicRegs.SCIRXBUF.all;                                        //���������ݴ洢

    if(SCIC_Data.Rx_FLag == 0x00)                                            //�жϽ��ձ�־λ�Ƿ�Ϊ0
	{
 		SCIC_Data.Rx_Buff[SCIC_Data.Rx_Counter] = Get_Temp;                  //���������ݴ�����ջ�����
		SCIC_Data.Rx_Status |= (1<<Rx_Message);                              //�����ݽ���״̬λ���λ��1
        if(SCIC_Data.Rx_Counter == 0)                                        //�ж����ݽ��ռ���λ�Ƿ�Ϊ0
		{
			if(SCIC_Data.Rx_Buff[SCIC_Data.Rx_Counter] == Cmd_Rx_Head)       //�жϽ������ݵ�ͷ�Ƿ�Ϊ'$'
			{
				SCIC_Data.Rx_Counter++;                                      //�������ݼ���λ��1
				SCIC_Data.Rx_Status |= (1<<Rx_Head_OK);                      //���ݽ���״̬λ���λ��1
				SCIC_Data.Rx_Status &= ~(1<<Rx_Message);                     //����������ݷ���ϵͳҪ�������λû������ �������ó�Ĭ��ֵ
				SCIC_Tx_Message.Cmd_Buff = SCIC_Data.Rx_Status;
			}
			else
			{
				SCIC_Data.Rx_Status &= ~(1<<Rx_Head_OK);                     //���ݽ���״̬λ���λ����
			}
		}
	  	else
		{
			SCIC_Data.Rx_Counter++;                                          //�������ݼ���λ��1
			if((SCIC_Data.Rx_Counter - 1) == Cmd_Long_Num)                   //�ж����ݼ���λ�Ƿ�Ϊ���ݳ��ȵĵ�λ
			{
				SCIC_Data.Rx_Message_Long = Str_To_Int(&SCIC_Data.Rx_Buff[Cmd_Long_Bit]); //���������Ϣ����ֵ����ת��������Ĵ�����
				if(SCIC_Data.Rx_Message_Long > Cmd_Max_Long)                 //�жϽ������ݵĳ���ֵ�Ƿ�����������ݵ���󳤶�
				{
					SCIC_Data.Rx_Status &= ~(1<<Rx_Long_OK);                 //����״̬���ݳ���״̬λ����
				}
			    else
				{
					SCIC_Data.Rx_Status |= (1<<Rx_Long_OK);                  //����״̬���ݳ���״̬λ��1
				}
			}
			if((SCIC_Data.Rx_Counter - 1) > Cmd_Long_Num)                    //�ж����ݼ���λ�Ƿ�������ݳ��ȵĵ�λ
			{
				if((SCIC_Data.Rx_Counter -1) == SCIC_Data.Rx_Message_Long + Cmd_Long_Num ) //�������ֵ���ڽ��յ��ġ����ݳ���ֵ����������λ����ֵ
				{
					SCIC_Data.Rx_FLag = 0x01;                                //���ձ�־λ��1
                    if(SCIC_Data.Rx_Buff[(SCIC_Data.Rx_Counter -1)] == Cmd_Rx_End)         //�жϽ���λ�Ƿ�Ϊ���س���
					{
						SCIC_Data.Rx_Status |= (1<<Rx_End_OK);               //���ݽ���״̬λ����״̬λ��1
						SCIC_Data.Check_Value = Get_Check_Num(&SCIC_Data.Rx_Buff[Cmd_Long_Bit],
								                              (unsigned char)((SCIC_Data.Rx_Counter -1) -5)); //�ж�У���  �����У��͵�λ��Ϊ
						if(SCIC_Data.Check_Value == Check_Char_To_Int(&SCIC_Data.Rx_Buff[(SCIC_Data.Rx_Counter -1) -4]))
						{
							SCIC_Data.Rx_Status |= (1<<Rx_Check_OK);         //У���״̬λ��1
							SCIC_Data.Rx_Counter = 0x00;                     //��ս��������ۼӱ���
							SCIC_Data.Rx_Message_Long = 0x00;                //���Ҫ���յ����ݳ��ȱ���
 						    ACK_SCI_Cmd = (SCI_Cmd_TypeDef *)SCIC_Data.Rx_Buff;
                            if((ACK_SCI_Cmd->Cmd_Type == Cmd_Rx_Type))       //�ж��豸����λ�Ƿ�ΪH������λ�Ƿ�Ϊ?
							{
								if(ACK_SCI_Cmd->Cmd_Fun == '?')              //�жϹ���λ�Ƿ�Ϊ?
								{
									SCIC_Data.Tx_Flag = 0x01;                //���ͱ�־λ��1
									SCIC_Data.Rx_FLag = 0x02;                //���ձ�־λ��1
									SCIC_Data.Rx_Status = 0x0000;            //����״̬λ����
								}
							}
						}
						else
						{
							SCIC_Data.Rx_Status &= ~(1<<Rx_Check_OK);        //У���״̬λ��0
						}
					}
					else
					{
						SCIC_Data.Rx_Status &= ~(1<<Rx_End_OK);              //���ݽ���״̬λ����״̬λ��0
					}
				}
			}
		}
	}
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;                          //ʹ��ͬ�������ж��ܹ��õ���Ӧ
    EINT;                                                            //��ȫ���ж�vcc
}

// INT8.6
interrupt void SCITXINTC_ISR(void)     // SCI-C
{
	if(SCIC_Data.Tx_Flag == 1)                                       //�жϷ��ͱ�־λ�Ƿ�Ϊ1
	{
		SCIC_Data.Tx_Counter++;                                      //���ڷ��ͼ���λ��1
	    ScicRegs.SCITXBUF = SCIC_Data.Tx_Buff[SCIC_Data.Tx_Counter];//���ڷ�������
	    if(	SCIC_Data.Tx_Counter == Cmd_Tx_Long)                     //�жϷ��ͼ���λ�Ƿ�������ݳ���ֵ
	    {
			SCIC_Data.Tx_Counter = 0;                                //���ڴ��ڷ��ͼ���λ��0
			SCIC_Data.Tx_Flag = 0;                                   //���ڷ��ͱ�־λ��0
			SCIC_Data.Rx_FLag=0x00;                                  //���ڽ��ձ�־λ��0
	    }
	}
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;                          //ʹ��ͬ�������ж��ܹ��õ���Ӧ
	EINT;                                                            //��ȫ���ж�
}
interrupt void INT13_ISR(void)     // INT13 or CPU-Timer1
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// Note CPU-Timer2 is reserved for TI use.
interrupt void INT14_ISR(void)     // CPU-Timer2
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

interrupt void DATALOG_ISR(void)   // Datalogging interrupt
{
   // Insert ISR Code here

   // Next two lines for debug only to halt the processor here
   // Remove after inserting ISR Code
   asm ("      ESTOP0");
   for(;;);
}

interrupt void RTOSINT_ISR(void)   // RTOS interrupt
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

interrupt void EMUINT_ISR(void)    // Emulation interrupt
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

interrupt void NMI_ISR(void)       // Non-maskable interrupt
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
//  asm ("      ESTOP0");
//  for(;;);
  LED1_H;
  Delay_ms(500);//��ȫ���ж�vcc
  LED1_L;
  Delay_ms(500);//��ȫ���ж�vcc
}

interrupt void ILLEGAL_ISR(void)   // Illegal operation TRAP
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm("          ESTOP0");
  for(;;);

}


interrupt void USER1_ISR(void)     // User Defined trap 1
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

interrupt void USER2_ISR(void)     // User Defined trap 2
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);


}

interrupt void USER3_ISR(void)     // User Defined trap 3
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

interrupt void USER4_ISR(void)     // User Defined trap 4
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

interrupt void USER5_ISR(void)     // User Defined trap 5
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

interrupt void USER6_ISR(void)     // User Defined trap 6
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

interrupt void USER7_ISR(void)     // User Defined trap 7
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

interrupt void USER8_ISR(void)     // User Defined trap 8
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

interrupt void USER9_ISR(void)     // User Defined trap 9
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

interrupt void USER10_ISR(void)    // User Defined trap 10
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

interrupt void USER11_ISR(void)    // User Defined trap 11
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

interrupt void USER12_ISR(void)     // User Defined trap 12
{
 // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

// -----------------------------------------------------------
// PIE Group 1 - MUXed into CPU INT1
// -----------------------------------------------------------

// INT1.1
interrupt void SEQ1INT_ISR(void)   //SEQ1 ADC
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code

  asm ("      ESTOP0");
  for(;;);

}

// INT1.2
interrupt void SEQ2INT_ISR(void)  //SEQ2 ADC
{

  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code

  asm("	  ESTOP0");
  for(;;);

}
// INT1.3 - Reserved

// INT1.4
interrupt void  XINT1_ISR(void)
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
//  asm ("      ESTOP0");
//  for(;;);
  LED2_H;
  Delay_ms(500);
  LED2_L;
  Delay_ms(500);
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;                          //ʹ��ͬ�������ж��ܹ��õ���Ӧ
  EINT;                                                            //��ȫ���ж�vcc
}

// INT1.5
interrupt void  XINT2_ISR(void)
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
//  asm ("      ESTOP0");
//  for(;;);
  LED3_H;
  Delay_ms(500);
  LED3_L;
  Delay_ms(500);
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;                          //ʹ��ͬ�������ж��ܹ��õ���Ӧ
  EINT;
}

// INT1.6
interrupt void  ADCINT_ISR(void)     // ADC
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT1.7
interrupt void  TINT0_ISR(void)      // CPU-Timer 0
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}


// INT1.8
interrupt void  WAKEINT_ISR(void)    // WD, LOW Power
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}


// -----------------------------------------------------------
// PIE Group 2 - MUXed into CPU INT2
// -----------------------------------------------------------

// INT2.1
interrupt void EPWM1_TZINT_ISR(void)    // EPWM-1
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT2.2
interrupt void EPWM2_TZINT_ISR(void)    // EPWM-2
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT2.3
interrupt void EPWM3_TZINT_ISR(void)    // EPWM-3
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}


// INT2.4
interrupt void EPWM4_TZINT_ISR(void)    // EPWM-4
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}


// INT2.5
interrupt void EPWM5_TZINT_ISR(void)    // EPWM-5
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT2.6
interrupt void EPWM6_TZINT_ISR(void)   // EPWM-6
{
  // Insert ISR Code here


  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT2.7 - Reserved
// INT2.8 - Reserved

// -----------------------------------------------------------
// PIE Group 3 - MUXed into CPU INT3
// -----------------------------------------------------------

// INT 3.1
interrupt void EPWM1_INT_ISR(void)     // EPWM-1
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT3.2
interrupt void EPWM2_INT_ISR(void)     // EPWM-2
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT3.3
interrupt void EPWM3_INT_ISR(void)    // EPWM-3
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT3.4
interrupt void EPWM4_INT_ISR(void)    // EPWM-4
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT3.5
interrupt void EPWM5_INT_ISR(void)    // EPWM-5
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT3.6
interrupt void EPWM6_INT_ISR(void)    // EPWM-6
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT3.7 - Reserved
// INT3.8 - Reserved


// -----------------------------------------------------------
// PIE Group 4 - MUXed into CPU INT4
// -----------------------------------------------------------

// INT 4.1
interrupt void ECAP1_INT_ISR(void)    // ECAP-1
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT4.2
interrupt void ECAP2_INT_ISR(void)    // ECAP-2
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT4.3
interrupt void ECAP3_INT_ISR(void)    // ECAP-3
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT4.4
interrupt void ECAP4_INT_ISR(void)     // ECAP-4
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT4.5
interrupt void ECAP5_INT_ISR(void)     // ECAP-5
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}
// INT4.6
interrupt void ECAP6_INT_ISR(void)     // ECAP-6
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}
// INT4.7 - Reserved
// INT4.8 - Reserved

// -----------------------------------------------------------
// PIE Group 5 - MUXed into CPU INT5
// -----------------------------------------------------------

// INT 5.1
interrupt void EQEP1_INT_ISR(void)    // EQEP-1
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT5.2
interrupt void EQEP2_INT_ISR(void)    // EQEP-2
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT5.3 - Reserved
// INT5.4 - Reserved
// INT5.5 - Reserved
// INT5.6 - Reserved
// INT5.7 - Reserved
// INT5.8 - Reserved

// -----------------------------------------------------------
// PIE Group 6 - MUXed into CPU INT6
// -----------------------------------------------------------

// INT6.1
interrupt void SPIRXINTA_ISR(void)    // SPI-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
   asm ("      ESTOP0");
   for(;;);
}

// INT6.2
interrupt void SPITXINTA_ISR(void)     // SPI-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
   asm ("      ESTOP0");
   for(;;);
}

// INT6.3
interrupt void MRINTB_ISR(void)     // McBSP-B
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT6.4
interrupt void MXINTB_ISR(void)     // McBSP-B
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT6.5
interrupt void MRINTA_ISR(void)     // McBSP-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
   asm ("      ESTOP0");
   for(;;);
}

// INT6.6
interrupt void MXINTA_ISR(void)     // McBSP-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
   asm ("      ESTOP0");
   for(;;);
}

// INT6.7 - Reserved
// INT6.8 - Reserved




// -----------------------------------------------------------
// PIE Group 7 - MUXed into CPU INT7
// -----------------------------------------------------------

// INT7.1
interrupt void DINTCH1_ISR(void)     // DMA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
   asm ("      ESTOP0");
   for(;;);
}

// INT7.2
interrupt void DINTCH2_ISR(void)     // DMA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
   asm ("      ESTOP0");
   for(;;);
}

// INT7.3
interrupt void DINTCH3_ISR(void)     // DMA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
   asm ("      ESTOP0");
   for(;;);
}

// INT7.4
interrupt void DINTCH4_ISR(void)     // DMA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
   asm ("      ESTOP0");
   for(;;);
}

// INT7.5
interrupt void DINTCH5_ISR(void)     // DMA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
   asm ("      ESTOP0");
   for(;;);
}

// INT7.6
interrupt void DINTCH6_ISR(void)     // DMA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
   asm ("      ESTOP0");
   for(;;);
}

// INT7.7 - Reserved
// INT7.8 - Reserved

// -----------------------------------------------------------
// PIE Group 8 - MUXed into CPU INT8
// -----------------------------------------------------------

// INT8.1
interrupt void I2CINT1A_ISR(void)     // I2C-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT8.2
interrupt void I2CINT2A_ISR(void)     // I2C-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}

// INT8.3 - Reserved
// INT8.4 - Reserved



// INT8.7 - Reserved
// INT8.8 - Reserved


// -----------------------------------------------------------
// PIE Group 9 - MUXed into CPU INT9
// -----------------------------------------------------------
/*
// INT9.1

interrupt void SCIRXINTA_ISR(void)     // SCI-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

// INT9.2

interrupt void SCITXINTA_ISR(void)     // SCI-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}
*/

// INT9.3
interrupt void SCIRXINTB_ISR(void)     // SCI-B
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

// INT9.4
interrupt void SCITXINTB_ISR(void)     // SCI-B
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

// INT9.5
interrupt void ECAN0INTA_ISR(void)  // eCAN-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

// INT9.6
interrupt void ECAN1INTA_ISR(void)  // eCAN-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

// INT9.7
interrupt void ECAN0INTB_ISR(void)  // eCAN-B
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

// INT9.8
interrupt void ECAN1INTB_ISR(void)  // eCAN-B
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

// -----------------------------------------------------------
// PIE Group 10 - MUXed into CPU INT10
// -----------------------------------------------------------

// INT10.1 - Reserved
// INT10.2 - Reserved
// INT10.3 - Reserved
// INT10.4 - Reserved
// INT10.5 - Reserved
// INT10.6 - Reserved
// INT10.7 - Reserved
// INT10.8 - Reserved


// -----------------------------------------------------------
// PIE Group 11 - MUXed into CPU INT11
// -----------------------------------------------------------

// INT11.1 - Reserved
// INT11.2 - Reserved
// INT11.3 - Reserved
// INT11.4 - Reserved
// INT11.5 - Reserved
// INT11.6 - Reserved
// INT11.7 - Reserved
// INT11.8 - Reserved

// -----------------------------------------------------------
// PIE Group 12 - MUXed into CPU INT12
// -----------------------------------------------------------

// INT12.1
interrupt void XINT3_ISR(void)  // External Interrupt
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

// INT12.2
interrupt void XINT4_ISR(void)  // External Interrupt
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

// INT12.3
interrupt void XINT5_ISR(void)  // External Interrupt
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}
// INT12.4
interrupt void XINT6_ISR(void)  // External Interrupt
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

// INT12.5
interrupt void XINT7_ISR(void)  // External Interrupt
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

// INT12.6 - Reserved
// INT12.7
interrupt void LVF_ISR(void)  // Latched overflow
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}
// INT12.8
interrupt void LUF_ISR(void)  // Latched underflow
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);

}

//---------------------------------------------------------------------------
// Catch All Default ISRs:
//

interrupt void PIE_RESERVED(void)  // Reserved space.  For test.
{
  asm ("      ESTOP0");
  for(;;);
}

interrupt void rsvd_ISR(void)      // For test
{
  asm ("      ESTOP0");
  for(;;);
}

//===========================================================================
// End of file.
//===========================================================================

