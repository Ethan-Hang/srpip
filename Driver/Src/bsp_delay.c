/******************************************************************************
 * @file bsp_delay.c
 *
 * @par dependencies
 * - "bsp_delay.h"
 * - "ti_msp_dl_config.h"
 *
 * @author Ethan-Hang
 *
 * @brief BSP delay driver implementation based on TIMERG0
 *
 * Processing flow:
 *
 * TIMERG0 generates 1ms periodic interrupt to increment tick counter.
 * Delay functions use this counter for accurate timing.
 *
 * @version V2.0 2025-11-15
 * @note Changed from SysTick to TIMERG0, counter changed to uint64_t
 * @note 1 tab == 4 spaces!
 *
 ******************************************************************************/

//******************************** Includes *********************************//
#include "bsp_delay.h"
#include "ti_msp_dl_config.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
/* Private variables */
static volatile uint64_t g_timer_ms = 0; /* Millisecond counter (64-bit) */
//******************************** Defines **********************************//

//************************** Function Implementations ***********************//

/******************************************************************
 * @brief  TIMERG0 interrupt handler (1ms period)
 *
 * @param[in] : None
 *
 * @param[out] : None
 *
 * @retval None
 *
 * @note This ISR is called every 1ms by TIMERG0 (TIMER_Delay)
 ******************************************************************/
void                     TIMER_Delay_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_Delay_INST))
    {
        case DL_TIMERG_IIDX_ZERO:
            g_timer_ms++;
            break;
        default:
            break;
    }
}

/******************************************************************
 * @brief  Initialize delay driver based on TIMERG0
 *
 * @param[in] : sysclk_freq - System clock frequency (not used, for
 *compatibility)
 *
 * @param[out] : None
 *
 * @retval None
 *
 * @note TIMERG0 is configured in ti_msp_dl_config.c (SysConfig generated)
 *       This function only resets counter and enables NVIC interrupt
 ******************************************************************/
void bsp_delay_init(uint32_t sysclk_freq)
{
    (void)sysclk_freq; /* Unused - timer configured by SysConfig */

    g_timer_ms = 0;

    /* Enable TIMERG0 interrupt in NVIC */
    NVIC_EnableIRQ(TIMER_Delay_INST_INT_IRQN);
}

/******************************************************************
 * @brief  Delay in milliseconds
 *
 * @param[in] : ms - Milliseconds to delay
 *
 * @param[out] : None
 *
 * @retval None
 *
 * @note Uses WFI instruction to enter low-power mode during wait
 ******************************************************************/
void bsp_delay_ms(uint32_t ms)
{
    uint64_t start = g_timer_ms;

    while ((g_timer_ms - start) < ms)
    {
        /* Wait for time to elapse */
        // __WFI(); /* Enter sleep mode to save power */
    }
}

/******************************************************************
 * @brief  Delay in microseconds
 *
 * @param[in] : us - Microseconds to delay
 *
 * @param[out] : None
 *
 * @retval None
 *
 * @note Busy-wait using CPU cycles. At 80MHz: 1us = 80 cycles
 ******************************************************************/
void bsp_delay_us_block(uint32_t us)
{
    /* Use cycle-based delay for microsecond delays */
    /* At 80MHz: 1us = 80 cycles */
    delay_cycles(us * (CPUCLK_FREQ / 1000000));
}

/******************************************************************
 * @brief  Get system tick count in milliseconds
 *
 * @param[in] : None
 *
 * @param[out] : None
 *
 * @retval System tick count in milliseconds since initialization
 *
 * @note With uint64_t, overflows after ~584 million years
 ******************************************************************/
uint32_t BSP_GetTick(void)
{
    return (uint32_t)g_timer_ms; /* Cast to uint32 for compatibility */
}

//************************** Function Implementations ***********************//
