/******************************************************************************
 * @file bsp_delay.h
 *
 * @par dependencies
 * - <stdint.h>
 * - "ti_msp_dl_config.h" (implementation file)
 *
 * @author Ethan-Hang
 *
 * @brief BSP delay driver based on TIMERG0
 *
 * Processing flow:
 *
 * 1. Call BSP_Delay_Init() to initialize delay counter
 * 2. Use BSP_Delay_ms() for millisecond delays
 * 3. Use BSP_GetTick() to get system timestamp
 *
 * @version V2.0 2025-11-15
 * @note Changed from SysTick to TIMERG0, uses 64-bit counter internally
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
 * @brief  Initialize delay driver based on TIMERG0
 *
 * @param[in] : sysclk_freq - System clock frequency (not used, for compatibility)
 *
 * @param[out] : None
 *
 * @retval None
 *
 * @note Must be called before using any delay functions
 * @note TIMERG0 is configured in ti_msp_dl_config.c (SysConfig)
 ******************************************************************/
void bsp_delay_init(uint32_t sysclk_freq);

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
void bsp_delay_ms(uint32_t ms);

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
void bsp_delay_us_block(uint32_t us);

/******************************************************************
 * @brief  Get system tick count in milliseconds
 *
 * @param[in] : None
 *
 * @param[out] : None
 *
 * @retval System tick count in milliseconds since initialization
 *
 * @note Uses 64-bit counter internally, returns uint32_t for compatibility
 ******************************************************************/
uint32_t BSP_GetTick(void);

//************************** Function Declarations **************************//

#ifdef __cplusplus
}
#endif

#endif /* __BSP_DELAY_H */
