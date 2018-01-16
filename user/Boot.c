
#include "Boot.h"
#include "stdint.h"
#include "string.h"
#include "Common.h"
//��ʼ��Boot
void BootInit( void );

//�����û�����
void Boot( void );
uint32_t *AppAddress;

/* ����4K�ռ䣬���Flashʱʹ��  */
#define   IAP_BUF_LENGTH      1024ul


//const uint32_t crp __attribute__((section(".ARM.__at_0x1FC"))) = CRP;



	uint8_t	    GucIapTmp[ IAP_BUF_LENGTH ] ;				  
//uint32_t                Flash_Writed_Len     = 0;
//�û��� flash ��Ϣ
uint32_t                FLASH_SEC_INFO[ USER_FLASH_SEC_COUNT ];
//����������id
//uint8_t                 UserSectorIndex      = 0;
//��Ҫд���flash��ַ
uint32_t                IAP_Flash_Address    = 0;

typedef void (*pFunction)(void);
pFunction Jump_to_Application;
uint32_t JumpAddress2;



//��ʼ��Boot
void BootInit( void )
{
//	uint8_t i;
//	
//	for ( i = 0; i < USER_FLASH_SEC_COUNT; i ++ )
//	{
//		if ( ( i + USER_APP_START_SEC ) <= 15 ) {
//			FLASH_SEC_INFO[ i ] = 4096ul;
//		}else{
//			FLASH_SEC_INFO[ i ] = 32768ul;
//		}
//		
//	}
	
	IAP_Flash_Address = USER_APP_START_ADD;

	//IAP_Entry = (void(*)())IAP_ENTER_ADR;
	
//	Flash_Writed_Len = 0;
//	UserSectorIndex  = 0;
	
}



//�����û�����
void Boot( void )
{
	

	 	/* Change the Vector Table to the USER_FLASH_START 
	in case the user application uses interrupts */
	SCB->VTOR = USER_APP_START_ADD & 0x1FFFFF80;
         JumpAddress2=*(__IO uint32_t*)(ApplicationAddress+4);
	 Jump_to_Application=(pFunction)JumpAddress2;
         __set_MSP(*(__IO uint32_t*)ApplicationAddress);
         Jump_to_Application();        
         //JMP_Boot();					
}





//�������
void SetFlashBlank( void )
{

	
		
    	
}




