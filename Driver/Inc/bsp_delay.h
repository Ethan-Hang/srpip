/******************************************************************************
 * @file bsp_delay.h
 *
 * @par dependencies
 * - <stdint.h>
 * - "ti_msp_dl_config.h" (implementation file)
 *
 * @author Ethan-Hang
 *
 * @brief BSP delay driver based on SysTick timer
 *
 * Processing flow:
 *
 * 1. Call BSP_Delay_Init() to initialize SysTick timer
 * 2. Use BSP_Delay_ms() for millisecond delays
 * 3. Use BSP_GetTick() to get system timestamp
 *
 * @version V1.0 2025-11-11
 *
 * @note 1 tab == 4 spaces!
 *
 *****************************************************************************/

#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

//******************************** Includes *********************************//
#include <stdint.h>
//******************************** Includes *********************************//

//************************** Function Declarations **************************//

/******************************************************************
 * @brief  Initialize delay driver based on SysTick timer
 *
 * @param[in] : sysclk_freq - System clock frequency in Hz (e.g., 32000000)
 *
 * @param[out] : None
 *
 * @retval None
 *
 * @note Must be called before using any delay functions
 ******************************************************************/
void BSP_Delay_Init(uint32_t sysclk_freq);

/******************************************************************
 * @brief  Delay in milliseconds
 *
 * @param[in] : ms - Milliseconds to delay
 *
 * @param[out] : None
 *
 * @retval None
 *
 * @note Uses WFI (Wait For Interrupt) for power saving
 ******************************************************************/
void BSP_Delay_ms(uint32_t ms);

/******************************************************************
 * @brief  Delay in microseconds
 *
 * @param[in] : us - Microseconds to delay
 *
 * @param[out] : None
 *
 * @retval None
 *
 * @note Busy-wait delay, suitable for short precise delays
 ******************************************************************/
void BSP_Delay_us(uint32_t us);

/******************************************************************
 * @brief  Get system tick count in milliseconds
 *
 * @param[in] : None
 *
 * @param[out] : None
 *
 * @retval System tick count in milliseconds since initialization
 *
 * @note Overflows after approximately 49.7 days
 ******************************************************************/
uint32_t BSP_GetTick(void);

/******************************************************************
 * @brief  Get system tick count in microseconds
 *
 * @param[in] : None
 *
 * @param[out] : None
 *
 * @retval System tick count in microseconds since initialization
 *
 * @note Lower precision, calculated from millisecond counter
 ******************************************************************/
uint64_t BSP_GetTick_us(void);

//************************** Function Declarations **************************//

#ifdef __cplusplus
}
#endif

#endif /* __BSP_DELAY_H */
