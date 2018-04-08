#include "stm8s.h"
#include "io.h"
#include "address.h"
#include "led.h"
#include "rs485.h"
#include "para.h"
#include "timer2.h"

static uint16_t time_counts = 0;

void clk_init(void)
{
    CLK_DeInit();
    /* Configure the Fcpu to DIV1*/
    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);    
    /* Configure the HSI prescaler to the optimal value */
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
    /* Output Fcpu on CLK_CCO pin */
    //CLK_CCOConfig(CLK_OUTPUT_CPU);
    /* Configure the system clock to use HSE clock source and to run at 24Mhz */
    CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}

void wdt_enable(void)
{
    IWDG_Enable();
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetReload(0xff);
}

void main(void)
{
	clk_init();
	local_address_init();
	led_init();
    io_init();
    rs485_init();
    timer2_init();
	//wdt_enable();
	
	enableInterrupts();
	while (1){
		//IWDG_ReloadCounter();
        if(time_counts++==10000){
            time_counts = 0;
            led_run_blink();
        }
        
		io_task();
        modbus_task();
        para_task();
	}
}

