#include "stm8s.h"
#include "io.h"
#include "modbus_driver.h"

extern uint8_t  MB_Coils[];
extern uint8_t  MB_DisIn[];

void io_init()
{
    GPIO_Init(GPIOB,(GPIO_Pin_TypeDef)GPIO_PIN_5, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(GPIOB,(GPIO_Pin_TypeDef)GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(GPIOC,(GPIO_Pin_TypeDef)GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(GPIOC,(GPIO_Pin_TypeDef)GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);
}

uint8_t read_di0()
{
    return GPIO_ReadInputPin(GPIOB, GPIO_PIN_5);
}

uint8_t read_di1()
{
    return GPIO_ReadInputPin(GPIOB, GPIO_PIN_4);
}

void write_do0(uint8_t val)
{
    if(val){
        GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
    } else {
        GPIO_WriteLow(GPIOC, GPIO_PIN_4);
    } 
}

void write_do1(uint8_t val)
{
    if(val){
        GPIO_WriteHigh(GPIOC, GPIO_PIN_3);
    } else {
        GPIO_WriteLow(GPIOC, GPIO_PIN_3);
    } 
}

void io_task(void)
{
    uint8_t di0,di1;
    
    di0 = read_di0();
    di1 = read_di1();
    
    if(di0){
        MB_DisIn[0] |= 0x01;
    } else {
        MB_DisIn[0] &= ~0x01;
    }
    
    if(di1){
        MB_DisIn[0] |= 0x02;
    } else {
        MB_DisIn[0] &= ~0x02;
    }
    
    write_do0(MB_Coils[0]&0x01);
    write_do1(MB_Coils[0]&0x02);
}
