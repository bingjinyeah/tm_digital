#include "stm8s.h"


extern void delay_ms(uint16_t);
uint8_t mb_local_address = 250;

void spi_init(void)
{
    //SPI_DeInit();
    GPIO_Init(GPIOC,(GPIO_Pin_TypeDef)GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(GPIOC,(GPIO_Pin_TypeDef)GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(GPIOC,(GPIO_Pin_TypeDef)GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);
    GPIO_WriteHigh(GPIOC,GPIO_PIN_5);
    //SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_256, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_HIGH,
    //    SPI_CLOCKPHASE_2EDGE,SPI_DATADIRECTION_1LINE_RX, SPI_NSS_SOFT,0x00);
    //SPI_Cmd(ENABLE); 
}

uint8_t spi_read_byte(void)
{
    /*
    while(SPI_GetFlagStatus(SPI_FLAG_TXE) == RESET);
    SPI_SendData(0xaa);
    while(SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
    return SPI_ReceiveData();
    */
    uint8_t i;
    uint16_t temp = 0;
    
    //GPIO_WriteHigh(GPIOC,GPIO_PIN_5);
    //delay_ms(20);
    for(i=0;i<8;i++){
        
        GPIO_WriteLow(GPIOC,GPIO_PIN_5);
        delay_ms(20);
        if(GPIO_ReadInputPin(GPIOC, GPIO_PIN_7)){
            temp |= 0x01;
        }
        temp <<= 1;
        GPIO_WriteHigh(GPIOC,GPIO_PIN_5);
        delay_ms(20);
    }
    temp >>= 1;
    return (uint8_t)temp;
    
    
}

void delay_ms(uint16_t ms)
{
    uint16_t res = 500;
    while(ms--){
        while(res--){
            
        }
        res = 500;
    }
}

void get_local_address(void)
{
    GPIO_WriteLow(GPIOC,GPIO_PIN_6);
    delay_ms(10);
    GPIO_WriteHigh(GPIOC,GPIO_PIN_6);
    delay_ms(10);
    mb_local_address = spi_read_byte();
}

void local_address_init()
{
    spi_init();
    delay_ms(10);
    get_local_address();
}
