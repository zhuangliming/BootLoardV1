
#include "lpc17xx.h"




#ifndef __BOOT_H__
#define __BOOT_H__

//lpc1758
#define MCU_LPC1758           29

//�û�������ʼ��ַ
#define USER_APP_START_ADD	   0x2000ul 
//�û�������ʼ������
#define USER_APP_START_SEC     2
//�ܿ�������
#define MCU_FLASH_SEC_MAX      MCU_LPC1758
//�û���������
#define USER_FLASH_SEC_COUNT   ( MCU_FLASH_SEC_MAX - USER_APP_START_SEC)

#define  IAP_ENTER_ADR        0x1FFF1FF1                                  /* IAP��ڵ�ַ����              */


#define CRP 0x11223344

#define CRP1  0x12345678
#define CRP2  0x87654321
#define CRP3  0x43218765
#define NOCRP 0x11223344




//��ʼ��Boot
extern void BootInit( void );

//�����û�����
extern void Boot( void );

//�������
extern void SetFlashBlank( void );
//������д��flash
extern uint8_t IAPWriteData( uint8_t *dataSrc, uint32_t dataLen );

#endif



