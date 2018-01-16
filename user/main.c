/**
* Ymode for lpc17xx iap
*/
/* Includes ------------------------------------------------------------------*/
#include "common.h"

static void IAP_Init(void);
/* Private typedef -----------------------------------------------------------*/

static void delay_ms(uint16_t time)
{
    uint16_t i=0,j;
    for(i=time; i>0; i--)
        for(j=10000; j>0; j--);
}


int main(void)
{
    uint8_t user_key=0;
    int i;
    IAP_Init();
    LED_INIT();
    SerialPutString("\r\n----------------------------------------------------------");
    SerialPutString("\r\n            LPC1758  Cortex-M3 System Update V1.0         ");
    SerialPutString("\r\n  Note: this operation will upgrade your system firmware! ");
    SerialPutString("\r\n                     Date: 2018-01-16   Designer: ZLM&LYF ");
    SerialPutString("\r\n----------------------------------------------------------");
    SerialPutString("\r\n\r\n");
    SerialPutString(" Press 'Z' key to continue!\r\n");
    /*3S Watting*/
    for(i=0;i<50;i++)
    {
        if(SerialKeyPressed(&user_key))
        {
            if((user_key == 'z')||(user_key == 'Z'))
            {
                Main_Menu ();
                i=0xFFFE;
            }
        }
        delay_ms(100);
    }
    SerialPutString(" Timeout Ready to jump to User APP\r\n");
    SerialPutString(" Please Reset MCU to upgrade your system firmware!\r\n");
    Boot();
    while (1)
    {

    }
}

/*
* Function Name  : IAP_Init
* Description    : Initialize the IAP: Configure RCC, USART and GPIOs.
* Return         : None
*/
static void IAP_Init(void)
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
    /*p2.4 rs485 ctrl pin*/
    PinCfg.Funcnum = 0;
    PinCfg.Pinnum = 4;
    PINSEL_ConfigPin( &PinCfg );
    GPIO_SetDir( 2, ( 1 << 5 )|(1<<4), 1 );
    UARTConfigStruct.Databits = UART_DATABIT_8;
    UARTConfigStruct.Baud_rate = BAUD;
    UARTConfigStruct.Parity = UART_PARITY_NONE;
    UARTConfigStruct.Stopbits = UART_STOPBIT_1;
    UART_Init( ( LPC_UART_TypeDef * )LPC_UART1, &UARTConfigStruct );
    UART_TxCmd( ( LPC_UART_TypeDef * )LPC_UART1, ENABLE );

}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
