/******************************************************************************
 * @file bsp_delay.c
 *
 * @par dependencies
 * - "bsp_delay.h"
 * - "ti_msp_dl_config.h"
 *
 * @author Ethan-Hang
 *
 * @brief BSP delay driver implementation based on SysTick timer
 *
 * Processing flow:
 *
 * SysTick generates 1ms periodic interrupt to increment tick counter.
 * Delay functions use this counter for accurate timing.
 *
 * @version V1.0 2025-11-11
 *
 * @note 1 tab == 4 spaces!
 *
 *****************************************************************************/

//******************************** Includes *********************************//
#include "bsp_delay.h"
#include "ti_msp_dl_config.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
/* Private variables */
static volatile uint32_t g_systick_ms = 0;      /* Millisecond counter */
//******************************** Defines **********************************//

//************************** Function Implementations ***********************//

/******************************************************************
 * @brief  SysTick interrupt handler (1ms period)
 *
 * @param[in] : None
 *
 * @param[out] : None
 *
 * @retval None
 *
 * @note This ISR is called every 1ms by SysTick timer
 ******************************************************************/
void SysTick_Handler(void)
{
    g_systick_ms++;
}

/******************************************************************
 * @brief  Initialize delay driver based on SysTick timer
 *
 * @param[in] : sysclk_freq - System clock frequency in Hz (e.g., 32000000)
 *
 * @param[out] : None
 *
 * @retval None
 *
 * @note DL_SYSTICK_config() enables interrupt and starts timer automatically
 ******************************************************************/
void BSP_Delay_Init(uint32_t sysclk_freq)
{
    g_systick_ms = 0;
    
    /* Configure SysTick to generate interrupt every 1ms */
    /* DL_SYSTICK_config already enables interrupt and starts timer */
    DL_SYSTICK_config(sysclk_freq / 1000);
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
void BSP_Delay_ms(uint32_t ms)
{
    uint32_t start = g_systick_ms;
    
    while ((g_systick_ms - start) < ms)
    {
        /* Wait for time to elapse */
        __WFI();  /* Enter sleep mode to save power */
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
 * @note Busy-wait using CPU cycles. At 32MHz: 1us = 32 cycles
 ******************************************************************/
void BSP_Delay_us(uint32_t us)
{
    /* Use cycle-based delay for microsecond delays */
    /* At 32MHz: 1us = 32 cycles */
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
 * @note Overflows after approximately 49.7 days (2^32 ms)
 ******************************************************************/
uint32_t BSP_GetTick(void)
{
    return g_systick_ms;
}

/******************************************************************
 * @brief  Get system tick count in microseconds
 *
 * @param[in] : None
 *
 * @param[out] : None
 *
 * @retval System tick count in microseconds since initialization
 *
 * @note Calculated from millisecond counter, lower precision
 ******************************************************************/
uint64_t BSP_GetTick_us(void)
{
    return (uint64_t)g_systick_ms * 1000;
}

//************************** Function Implementations ***********************//
