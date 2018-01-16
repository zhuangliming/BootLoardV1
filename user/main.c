/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : Main program body
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "common.h"


void RCC_Configuration(void);
void IAP_Init(void);
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#define IAP_LED_ON   GPIO_SetBits(GPIOB, GPIO_Pin_0)		
#define IAP_LED_OFF  GPIO_ResetBits(GPIOB, GPIO_Pin_0) 	
extern u32 *AppAddress;
static void delay_ms(uint16_t time)
{
  uint16_t i=0,j;
  for(i=time; i>0; i--)
    for(j=10000; j>0; j--);
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
  uint8_t user_key=0;
  u32 APP=0x0010;
  int i;
  AppAddress=&APP;
  
#ifdef DEBUG
  debug();
#endif
  //  FLASH_Unlock();			// Flash unlock
  IAP_Init();
  
  BootInit();
  SerialPutString("\r\n----------------------------------------------------------");
  SerialPutString("\r\n            LPC1758  Cortex-M3 System Update V1.1                ");
  SerialPutString("\r\n  Note: this operation will upgrade your system firmware! ");
  SerialPutString("\r\n                                           --Luyinfa ");
  SerialPutString("\r\n----------------------------------------------------------");
  SerialPutString("\r\n\r\n");
  SerialPutString(" Press Z to continue\r\n");
  for(i=0; i<100; i++) {
    // SerialPutChar(23); 
    if(SerialKeyPressed(&user_key)) {
      if(user_key == 'z') {
        Main_Menu ();
        i=101;
      }
    }
    delay_ms(100);
  }
 SerialPutString(" Timeout Ready to jump to User APP\r\n");
 SerialPutString(" Please Reset MCU to upgrade your system firmware!\r\n");
 Boot();
  
  while (1) {    
    
  }
}

/*******************************************************************************
* Function Name  : IAP_Init
* Description    : Initialize the IAP: Configure RCC, USART and GPIOs.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void IAP_Init(void)
{
  UART_CFG_Type UARTConfigStruct;
  UART_FIFO_CFG_Type UARTFIFOConfigStruct;
  PINSEL_CFG_Type PinCfg;
  PinCfg.Funcnum = 2;
  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Pinnum = 0;
  PinCfg.Portnum = 2;
  PINSEL_ConfigPin( &PinCfg );
  PinCfg.Pinnum = 1;
  PINSEL_ConfigPin( &PinCfg );
  PinCfg.Funcnum = 0;
  PinCfg.Pinnum = 5;
  PINSEL_ConfigPin( &PinCfg );
  /*p2.4*/
  PinCfg.Funcnum = 0;
  PinCfg.Pinnum = 4;
  PINSEL_ConfigPin( &PinCfg );
  GPIO_SetDir(1, 1<<23, 1);   //LED灯的方向位设置
  GPIO_SetDir( 2, ( 1 << 5 )|(1<<4), 1 );
  UARTConfigStruct.Databits = UART_DATABIT_8;
  UARTConfigStruct.Baud_rate = 9600;
  UARTConfigStruct.Parity = UART_PARITY_NONE;
  UARTConfigStruct.Stopbits = UART_STOPBIT_1;
  UART_Init( ( LPC_UART_TypeDef * )LPC_UART1, &UARTConfigStruct );
  UART_TxCmd( ( LPC_UART_TypeDef * )LPC_UART1, ENABLE );
  //UART_IntConfig( ( LPC_UART_TypeDef * )LPC_UART1, UART_INTCFG_RBR, ENABLE );
  //UART_IntConfig( ( LPC_UART_TypeDef * )LPC_UART1, UART_INTCFG_THRE , ENABLE );
  // NVIC_EnableIRQ( UART1_IRQn );
  
}

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
  
}
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
