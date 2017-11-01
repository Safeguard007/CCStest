#ifndef CONTROL_H
#define CONTROL_H

#include"PlatForm.h"

///////////////////////////////////�˶����ƺ���������////////////////////////////////////////
extern void IO_Out_Set(unsigned char *Str , unsigned char *Send_Message);                   //ͨ�����IO����
extern void SCI_RX_Message_Process(unsigned char *Message_Buff,ROBOT_STATUS_REGS_TypeDef *Robot_Status,unsigned char *Send_Message); //���ڴ�����
extern void SCI_Command_Execute(ROBOT_STATUS_REGS_TypeDef *Robot_Status);                   //ָ��ִ�к���
extern void SCIA_Command_Execute(ROBOT_STATUS_REGS_TypeDef *Robot_Status);
extern void SCIA_RX_Message_Process(unsigned char *Message_Buff,ROBOT_STATUS_REGS_TypeDef *Robot_Status,unsigned char *Send_Message);                                            //Flash��Ϣ��ʼ��
extern void Connection_Test(unsigned char *Send_Message);                                   //ͨ�Ų��Իظ�
extern void Information_Flash_Erase(unsigned char *Send_Message);                           //Flash��Ϣ����



extern void CPU_LED(unsigned char *Send_Message);
extern void GPIO_O(unsigned char *Str,unsigned char *Send_Message);
extern void GPIO_I(unsigned char *Str,unsigned char *Send_Message);
extern void RAM_WR(unsigned char *CESHIR,unsigned char *Send_Message);
extern void FLASH_Q(unsigned char *Send_Message);
extern void FLASH_W(unsigned char *CESHIR,unsigned char *Send_Message);
extern void FLASH_R(unsigned char *Send_Message);
extern void SF_SG(unsigned char *CESHIR,unsigned char *Send_Message);
extern void CGQ_ZT(unsigned char *CESHIR,unsigned char *Send_Message);
extern void DJ_KZ(unsigned char *CESHIR,unsigned char *Send_Message);
extern void BMQ_QL(unsigned char *CESHIR,unsigned char *Send_Message);
extern void QDQ_BJ(unsigned char *CESHIR,unsigned char *Send_Message);
void  A_R(unsigned char *Send_Buff,unsigned char *Send_Message);
void  C_R(unsigned char *Send_Buff,unsigned char *Send_Message);
void  BMQ_R(unsigned char *CESHIR,unsigned char *Send_Message);
#endif
