/******************************************************************************
 * @file main.c
 *
 * @par dependencies
 * - <stdio.h>
 * - "ti_msp_dl_config.h"
 * - "bsp_delay.h"
 * - "Segger_RTT.h"
 * - "elog.h"
 *
 * @author Ethan-Hang
 *
 * @brief
 *
 * Processing flow:
 *
 * call directly.
 *
 * @version V1.0 2025-11-11
 *
 * @note 1 tab == 4 spaces!
 *
 *****************************************************************************/

//******************************** Includes *********************************//
#include <stdio.h>

#include "ti_msp_dl_config.h"

#include "bsp_delay.h"

#include "Segger_RTT.h"
#include "elog.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//

void app_elog_init(void);

//******************************** Defines **********************************//

//************************** Function Implementations ***********************//
int  main(void)
{
    SYSCFG_DL_init();
    BSP_Delay_Init(CPUCLK_FREQ);
    app_elog_init();

    while (1)
    {
        log_i("Hello EasyLogger on MSPM0G3507!");
        BSP_Delay_ms(1000);
        DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_PIN);
    }
}

/******************************************************************
 *@brief  Retargets the C library printf function to the USART.
 *
 *@param  None
 *
 *@retval None
 ******************************************************************/
int fputc(int ch, FILE *f)
{
    // DL_UART_transmitDataBlocking(UART_0_INST, (uint8_t)ch);
    SEGGER_RTT_printf(0, "%c", ch);
    return ch;
}

/**
 * @brief  Initialize EasyLogger module
 *
 * @param[in] :  None
 *
 * @param[out] : None
 *
 * @retval None
 *
 * */
void app_elog_init(void)
{
    elog_init();

    //   elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG);
    //   elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL);

    elog_start();
}

//************************** Function Implementations ***********************//
