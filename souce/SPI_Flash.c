#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP28x_Project.h"
#include "PlatForm.h"
#include "control.h"

/************************************************************
* 函数名称：Spi_Send
* 输入参数：无
* 输出参数：无
* 功       能：SPI数据发送
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void Spi_Send(Uint16 txdata)
{
    SpiaRegs.SPITXBUF = txdata<<8;
    while(SpiaRegs.SPIFFRX.bit.RXFFST != 1);
    SpiaRegs.SPIRXBUF;
}

/************************************************************
* 函数名称：Spi_Rece
* 输入参数：无
* 输出参数：无
* 功       能：SPI数据接收
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
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
* 函数名称：w25q256_reset
* 输入参数：无
* 输出参数：无
* 功       能：w25q256 Flash初始化
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void w25q256_reset(void)
{
	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;       //片选低
	Spi_Send(Enable_Reset);                      //发送命令
	Spi_Send(Reset_Dev);
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //片选高
	Delay_ms(1);                                 //延时至少3030uS
}

/************************************************************
* 函数名称：w25q256_read_reg1
* 输入参数：无
* 输出参数：无
* 功       能：读取Flash寄存器1
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
Uint16 w25q256_read_reg1(void)
{
	Uint16 temp;

	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;       //片选低
	Spi_Send(Read_Status_Reg1);                  //发送命令
	temp = Spi_Rece();                           //获取数据
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //片选高

	return temp;
}

/************************************************************
* 函数名称：w25q256_read_reg2
* 输入参数：无
* 输出参数：无
* 功       能：读取Flash寄存器2
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
Uint16 w25q256_read_reg2(void)
{
	Uint16 temp;

	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;       //片选低
	Spi_Send(Read_Status_Reg2);                  //发送命令
	temp = Spi_Rece();                           //获取数据
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //片选高

	return temp;
}

/************************************************************
* 函数名称：w25q256_read_reg3
* 输入参数：无
* 输出参数：无
* 功       能：读取Flash寄存器3
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
Uint16 w25q256_read_reg3(void)
{
	Uint16 temp;

	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;       //片选低
	Spi_Send(Read_Status_Reg3);                  //发送命令
	temp = Spi_Rece();                           //获取数据
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //片选高

	return temp;
}

/************************************************************
* 函数名称：w25q256_set_4addr
* 输入参数：无
* 输出参数：无
* 功       能：设置成4字节地址模式
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void w25q256_set_4addr(void)
{
	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;
	Spi_Send(Enter_4B_Addr_Mode);	             //发送命令
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;	     //片选高
}

/************************************************************
* 函数名称：w25q256_init
* 输入参数：无
* 输出参数：无
* 功       能：Flash初始化
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void w25q256_init(void)
{
	Uint16 temp;

	w25q256_reset();	                         //复位
	temp = w25q256_read_reg3();                  //检测4字节地址模式
	if((temp&0x01) == 0x0)                       //读取寄存器3,第2位ADP
	{
		w25q256_set_4addr();
	}
}

/************************************************************
* 函数名称：w25q256_readid
* 输入参数：无
* 输出参数：无
* 功       能：读取Flash ID
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
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
* 函数名称：w25q256_write_enable
* 输入参数：无
* 输出参数：无
* 功       能：写使能
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void w25q256_write_enable(void)
{
	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;
	Spi_Send(Write_Enable);	                     //发送命令
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;	     //片选高
}

/************************************************************
* 函数名称：w25q256_test_busy
* 输入参数：无
* 输出参数：无
* 功       能：检测忙
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
Uint16 w25q256_test_busy(void)
{
	Uint16 temp,ret;

	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;
	temp = w25q256_read_reg1();                  //发送命令
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //片选高
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
* 函数名称：w25q256_erase_chip
* 输入参数：无
* 输出参数：无
* 功       能：芯片擦除
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void w25q256_erase_chip(void)
{
	w25q256_write_enable();	                     //写使能
	while(w25q256_test_busy() ==0x1);            //检测忙
	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;
	Spi_Send(Chip_Erase1);                       //发送命令
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //片选高
	while(w25q256_test_busy() ==0x1);            //等待擦除完成
}

/************************************************************
* 函数名称：w25q256_erase_sector
* 输入参数：无
* 输出参数：无
* 功       能：擦除扇区4K
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void w25q256_erase_sector(Uint32 addr)
{
	w25q256_write_enable();                      //写使能
	while(w25q256_test_busy() ==0x1);            //检测忙
	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;
	Spi_Send(Sector_Erase);                      //发送命令
	Spi_Send(addr >> 24);                        //发送地址
	Spi_Send(addr >> 16);
	Spi_Send(addr >> 8);
	Spi_Send(addr );
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //片选高

	while(w25q256_test_busy() ==0x1);	         //flash最多400mS后命令开始执行擦除，等待擦除完成
}

/************************************************************
* 函数名称：w25q256_read
* 输入参数：无
* 输出参数：无
* 功       能：addr地址开始连续读N个字节
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void w25q256_read(Uint16 *tar_data, Uint32 addr, Uint32 n)
{
	Uint32 i;

	GpioDataRegs.GPBCLEAR.bit.GPIO57=0x01;

	Spi_Send(Read_Data);                         //发送命令
	Spi_Send(addr >> 24);                        //发送地址
	Spi_Send(addr >> 16);
	Spi_Send(addr >> 8);
	Spi_Send(addr);

	for(i=0;i<n;i++)                             //接收数据
	{
		*(tar_data+i) = Spi_Rece();
	}
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //片选高
	while(w25q256_test_busy() ==0x1);
}

/************************************************************
* 函数名称：w25q256_write
* 输入参数：无
* 输出参数：无
* 功       能：向addr地址开始连续写N个字节
* 备       注：
* 版本说明： 历史版本：                         当前版本：
*          修改原因：
*          修改人日期：
*************************************************************/
void w25q256_write(Uint16 *sou_data, Uint32 addr, Uint16 n)
{
	Uint16 i;

	w25q256_write_enable();                      //写使能
	while(w25q256_test_busy() == 0x1);           //检测忙
	GpioDataRegs.GPBCLEAR.bit.GPIO57 = 0x01;
	Spi_Send(Page_Program);                      //发送命令
	Spi_Send(addr >> 24);
	//发送地址
	Spi_Send(addr >> 16);
	Spi_Send(addr >> 8);
	Spi_Send(addr );
	for(i=0;i<n;i++)                             //发送数据
	{
		Spi_Send(*(sou_data+i));
	}
	GpioDataRegs.GPBSET.bit.GPIO57 = 0x01;       //片选高
	while(w25q256_test_busy() ==0x1);
}
