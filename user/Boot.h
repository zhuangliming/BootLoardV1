
#include "lpc17xx.h"




#ifndef __BOOT_H__
#define __BOOT_H__

//lpc1758
#define MCU_LPC1758           29

//用户程序起始地址
#define USER_APP_START_ADD	   0x2000ul 
//用户程序起始扇区号
#define USER_APP_START_SEC     2
//总可用扇区
#define MCU_FLASH_SEC_MAX      MCU_LPC1758
//用户可用扇区
#define USER_FLASH_SEC_COUNT   ( MCU_FLASH_SEC_MAX - USER_APP_START_SEC)

#define  IAP_ENTER_ADR        0x1FFF1FF1                                  /* IAP入口地址定义              */


#define CRP 0x11223344

#define CRP1  0x12345678
#define CRP2  0x87654321
#define CRP3  0x43218765
#define NOCRP 0x11223344




//初始化Boot
extern void BootInit( void );

//启动用户程序
extern void Boot( void );

//清除扇区
extern void SetFlashBlank( void );
//将数据写入flash
extern uint8_t IAPWriteData( uint8_t *dataSrc, uint32_t dataLen );

#endif



