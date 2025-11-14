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
 * @version V1.0 2025-11-12
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

// Linker-generated symbols for RW_IRAM2 custom memory region
// Load addresses (in Flash/ROM)
extern int Load$$RW_IRAM2$$Base;

// Execution addresses (in RAM) - RW data section
extern int Image$$RW_IRAM2$$RW$$Base;
extern int Image$$RW_IRAM2$$RW$$Limit;

// Execution addresses (in RAM) - ZI data section (BSS)
extern int Image$$RW_IRAM2$$ZI$$Base;
extern int Image$$RW_IRAM2$$ZI$$Limit;

void       app_elog_init(void);
//******************************** Defines **********************************//

//************************** Function Implementations ***********************//
int        main(void)
{
    SYSCFG_DL_init();
    bsp_delay_init(CPUCLK_FREQ);
    app_elog_init();

    uint32_t count = 0;
    while (1)
    {
        log_i("get tick: %llu ms", BSP_GetTick());
        DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_PIN);
        bsp_delay_ms(500);
    }
}

/**
 * @brief Retarget printf to SEGGER RTT
 *
 * Redirects standard output to SEGGER RTT for debugging.
 *
 * @param[in]  ch : Character to transmit
 * @param[in]  f  : File pointer
 *
 * @retval The character written (ch)
 */
int fputc(int ch, FILE *f)
{
    // DL_UART_transmitDataBlocking(UART_0_INST, (uint8_t)ch);
    SEGGER_RTT_printf(0, "%c", ch);
    return ch;
}

/**
 * @brief Initialize EasyLogger module
 *
 * Initializes EasyLogger library for system logging.
 *
 * @param[in]  : None
 * @param[out] : None
 *
 * @retval None
 *
 * @note Must be called after __custom_data_init() to ensure all
 *       global variables are properly initialized
 */
void app_elog_init(void)
{
    elog_init();

    //   elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG);
    //   elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL);

    elog_start();
}

/**
 * @brief Custom data section initialization
 *
 * Called in Reset_Handler before main() to initialize RW_IRAM2
 * custom memory region. Prevents global variable initialization
 * failures in custom memory regions.
 *
 * @param[in]  : None
 * @param[out] : None
 *
 * @retval None
 *
 * @note 1. Copy RW data from Flash to RAM
 *       2. Zero-initialize ZI data (BSS)
 *
 * @warning Cannot use memcpy/memset. Must be called in startup
 *          before C library initialization.
 */
void __custom_data_init(void)
{
    uint32_t *src = (uint32_t *)&Load$$RW_IRAM2$$Base;
    uint32_t *dst = (uint32_t *)&Image$$RW_IRAM2$$RW$$Base;
    uint32_t *end = (uint32_t *)&Image$$RW_IRAM2$$RW$$Limit;

    // 1. Copy RW data section (initialized global/static variables)
    while (dst < end)
    {
        *dst = *src;
        dst++;
        src++;
    }

    // 2. Zero-initialize ZI data section (BSS)
    dst = (uint32_t *)&Image$$RW_IRAM2$$ZI$$Base;
    end = (uint32_t *)&Image$$RW_IRAM2$$ZI$$Limit;

    while (dst < end)
    {
        *dst = 0;
        dst++;
    }
}
//************************** Function Implementations ***********************//
