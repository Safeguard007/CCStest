#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP28x_Project.h"
#include "PlatForm.h"
#include "control.h"

/************************************************************
* �������ƣ�Spi_Send
* �����������
* �����������
* ��       �ܣ�SPI���ݷ���
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void Spi_Send(Uint16 txdata)
{
    SpiaRegs.SPITXBUF = txdata<<8;
    while(SpiaRegs.SPIFFRX.bit.RXFFST != 1);
    SpiaRegs.SPIRXBUF;
}

/************************************************************
* �������ƣ�Spi_Rece
* �����������
* �����������
* ��       �ܣ�SPI���ݽ���
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
Uint16 Spi_Rece(void)
{
	Uint16 rxdata;

    SpiaRegs.SPITXBUF = (Uint16)(0xff<<8);
    while(SpiaRegs.SPIFFRX.bit.RXFFST != 1);
    rxdata = SpiaRegs.SPIRXBUF;

    return rxdata;
}

/************************************************************
* �������ƣ�w25q256_reset
* �����������
* �����������
* ��       �ܣ�w25q256 Flash��ʼ��
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void w25q256_reset(void)
{
	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;       //Ƭѡ��
	Spi_Send(Enable_Reset);                      //��������
	Spi_Send(Reset_Dev);
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //Ƭѡ��
	Delay_ms(1);                                 //��ʱ����3030uS
}

/************************************************************
* �������ƣ�w25q256_read_reg1
* �����������
* �����������
* ��       �ܣ���ȡFlash�Ĵ���1
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
Uint16 w25q256_read_reg1(void)
{
	Uint16 temp;

	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;       //Ƭѡ��
	Spi_Send(Read_Status_Reg1);                  //��������
	temp = Spi_Rece();                           //��ȡ����
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //Ƭѡ��

	return temp;
}

/************************************************************
* �������ƣ�w25q256_read_reg2
* �����������
* �����������
* ��       �ܣ���ȡFlash�Ĵ���2
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
Uint16 w25q256_read_reg2(void)
{
	Uint16 temp;

	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;       //Ƭѡ��
	Spi_Send(Read_Status_Reg2);                  //��������
	temp = Spi_Rece();                           //��ȡ����
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //Ƭѡ��

	return temp;
}

/************************************************************
* �������ƣ�w25q256_read_reg3
* �����������
* �����������
* ��       �ܣ���ȡFlash�Ĵ���3
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
Uint16 w25q256_read_reg3(void)
{
	Uint16 temp;

	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;       //Ƭѡ��
	Spi_Send(Read_Status_Reg3);                  //��������
	temp = Spi_Rece();                           //��ȡ����
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //Ƭѡ��

	return temp;
}

/************************************************************
* �������ƣ�w25q256_set_4addr
* �����������
* �����������
* ��       �ܣ����ó�4�ֽڵ�ַģʽ
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void w25q256_set_4addr(void)
{
	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;
	Spi_Send(Enter_4B_Addr_Mode);	             //��������
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;	     //Ƭѡ��
}

/************************************************************
* �������ƣ�w25q256_init
* �����������
* �����������
* ��       �ܣ�Flash��ʼ��
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void w25q256_init(void)
{
	Uint16 temp;

	w25q256_reset();	                         //��λ
	temp = w25q256_read_reg3();                  //���4�ֽڵ�ַģʽ
	if((temp&0x01) == 0x0)                       //��ȡ�Ĵ���3,��2λADP
	{
		w25q256_set_4addr();
	}
}

/************************************************************
* �������ƣ�w25q256_readid
* �����������
* �����������
* ��       �ܣ���ȡFlash ID
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
Uint32 w25q256_readid(void)
{
	Uint32 Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;
	Spi_Send(0x9F);
	Temp0 = Spi_Rece();
	Temp1 = Spi_Rece();
	Temp2 = Spi_Rece();
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;
	Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

    return Temp;
}

/************************************************************
* �������ƣ�w25q256_write_enable
* �����������
* �����������
* ��       �ܣ�дʹ��
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void w25q256_write_enable(void)
{
	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;
	Spi_Send(Write_Enable);	                     //��������
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;	     //Ƭѡ��
}

/************************************************************
* �������ƣ�w25q256_test_busy
* �����������
* �����������
* ��       �ܣ����æ
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
Uint16 w25q256_test_busy(void)
{
	Uint16 temp,ret;

	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;
	temp = w25q256_read_reg1();                  //��������
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //Ƭѡ��
	if((temp & 0x01) == 0x01)
	{
		ret = 0x01;
	}
	else
	{
		ret = 0x00;
	}

	return ret;
}

/************************************************************
* �������ƣ�w25q256_erase_chip
* �����������
* �����������
* ��       �ܣ�оƬ����
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void w25q256_erase_chip(void)
{
	w25q256_write_enable();	                     //дʹ��
	while(w25q256_test_busy() ==0x1);            //���æ
	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;
	Spi_Send(Chip_Erase1);                       //��������
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //Ƭѡ��
	while(w25q256_test_busy() ==0x1);            //�ȴ��������
}

/************************************************************
* �������ƣ�w25q256_erase_sector
* �����������
* �����������
* ��       �ܣ���������4K
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void w25q256_erase_sector(Uint32 addr)
{
	w25q256_write_enable();                      //дʹ��
	while(w25q256_test_busy() ==0x1);            //���æ
	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;
	Spi_Send(Sector_Erase);                      //��������
	Spi_Send(addr >> 24);                        //���͵�ַ
	Spi_Send(addr >> 16);
	Spi_Send(addr >> 8);
	Spi_Send(addr );
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //Ƭѡ��

	while(w25q256_test_busy() ==0x1);	         //flash���400mS�����ʼִ�в������ȴ��������
}

/************************************************************
* �������ƣ�w25q256_read
* �����������
* �����������
* ��       �ܣ�addr��ַ��ʼ������N���ֽ�
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void w25q256_read(Uint16 *tar_data, Uint32 addr, Uint32 n)
{
	Uint32 i;

	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;

	Spi_Send(Read_Data);                         //��������
	Spi_Send(addr >> 24);                        //���͵�ַ
	Spi_Send(addr >> 16);
	Spi_Send(addr >> 8);
	Spi_Send(addr);

	for(i=0;i<n;i++)                             //��������
	{
		*(tar_data+i) = Spi_Rece();
	}
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //Ƭѡ��
	while(w25q256_test_busy() ==0x1);
}

/************************************************************
* �������ƣ�w25q256_write
* �����������
* �����������
* ��       �ܣ���addr��ַ��ʼ����дN���ֽ�
* ��       ע��
* �汾˵���� ��ʷ�汾��                         ��ǰ�汾��
*          �޸�ԭ��
*          �޸������ڣ�
*************************************************************/
void w25q256_write(Uint16 *sou_data, Uint32 addr, Uint16 n)
{
	Uint16 i;

	w25q256_write_enable();                      //дʹ��
	while(w25q256_test_busy() == 0x1);           //���æ
	GpioDataRegs.GPBCLEAR.bit.GPIO57 = 0x01;
	Spi_Send(Page_Program);                      //��������
	Spi_Send(addr >> 24);
	//���͵�ַ
	Spi_Send(addr >> 16);
	Spi_Send(addr >> 8);
	Spi_Send(addr );
	for(i=0;i<n;i++)                             //��������
	{
		Spi_Send(*(sou_data+i));
	}
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //Ƭѡ��
	while(w25q256_test_busy() ==0x1);
}
