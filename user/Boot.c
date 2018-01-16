
#include "Boot.h"
#include "stdint.h"
#include "string.h"
#include "Common.h"
void BootInit( void );

void Boot( void );
uint32_t *AppAddress;

/* 4K flash  */
#define     IAP_BUF_LENGTH      1024ul
uint8_t	    GucIapTmp[ IAP_BUF_LENGTH ] ;
uint32_t    FLASH_SEC_INFO[ USER_FLASH_SEC_COUNT ];
uint32_t    IAP_Flash_Address    = 0;

typedef void (*pFunction)(void);
pFunction Jump_to_Application;
uint32_t JumpAddress2;

void BootInit( void )
{
    IAP_Flash_Address = USER_APP_START_ADD;
}

void Boot( void )
{


    /* Change the Vector Table to the USER_FLASH_START
    in case the user application uses interrupts */
    SCB->VTOR = USER_APP_START_ADD & 0x1FFFFF80;
    JumpAddress2=*(__IO uint32_t*)(ApplicationAddress+4);
    Jump_to_Application=(pFunction)JumpAddress2;
    __set_MSP(*(__IO uint32_t*)ApplicationAddress);
    Jump_to_Application();
}

void SetFlashBlank( void )
{

}




