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

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//

// Linker-generated symbols for RW_IRAM2 custom memory region
// Load addresses (in Flash/ROM)
// extern int Load$$RW_IRAM2$$Base;

// // Execution addresses (in RAM) - RW data section
// extern int Image$$RW_IRAM2$$RW$$Base;
// extern int Image$$RW_IRAM2$$RW$$Limit;

// // Execution addresses (in RAM) - ZI data section (BSS)
// extern int Image$$RW_IRAM2$$ZI$$Base;
// extern int Image$$RW_IRAM2$$ZI$$Limit;

/* Function declarations */
void       app_elog_init(void);
void       vLedTask(void *pvParameters);
void       vTask1(void *pvParameters);
void       vTask2(void *pvParameters);
void       vTask3(void *pvParameters);
//******************************** Defines **********************************//

//************************** Function Implementations ***********************//
int        main(void)
{
    SYSCFG_DL_init();
    bsp_delay_init(CPUCLK_FREQ);
    app_elog_init();

    /* 创建 LED 闪烁任务 */
    xTaskCreate(vLedTask,              /* 任务函数 */
                "LED",                 /* 任务名称 */
                256,                   /* 栈大小(字) */
                NULL,                  /* 任务参数 */
                1,                     /* 任务优先级 */
                NULL);                 /* 任务句柄 */

    /* 创建任务1 */
    xTaskCreate(vTask1,                /* 任务函数 */
                "Task1",               /* 任务名称 */
                256,                   /* 栈大小(字) */
                NULL,                  /* 任务参数 */
                2,                     /* 任务优先级 */
                NULL);                 /* 任务句柄 */

    /* 创建任务2 */
    xTaskCreate(vTask2,                /* 任务函数 */
                "Task2",               /* 任务名称 */
                256,                   /* 栈大小(字) */
                NULL,                  /* 任务参数 */
                2,                     /* 任务优先级 */
                NULL);                 /* 任务句柄 */

    /* 创建任务3 */
    xTaskCreate(vTask3,                /* 任务函数 */
                "Task3",               /* 任务名称 */
                256,                   /* 栈大小(字) */
                NULL,                  /* 任务参数 */
                2,                     /* 任务优先级 */
                NULL);                 /* 任务句柄 */

    log_i("FreeRTOS Starting...");

    /* 启动调度器 */
    vTaskStartScheduler();

    /* 永远不会到达这里 */
    while (1)
    {
        log_i("Error: Should never reach here!");
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
    vTaskSuspendAll();
    // DL_UART_transmitDataBlocking(UART_0_INST, (uint8_t)ch);
    SEGGER_RTT_printf(0, "%c", ch);
    xTaskResumeAll();
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
// void __custom_data_init(void)
// {
//     uint32_t *src = (uint32_t *)&Load$$RW_IRAM2$$Base;
//     uint32_t *dst = (uint32_t *)&Image$$RW_IRAM2$$RW$$Base;
//     uint32_t *end = (uint32_t *)&Image$$RW_IRAM2$$RW$$Limit;

//     // 1. Copy RW data section (initialized global/static variables)
//     while (dst < end)
//     {
//         *dst = *src;
//         dst++;
//         src++;
//     }

//     // 2. Zero-initialize ZI data section (BSS)
//     dst = (uint32_t *)&Image$$RW_IRAM2$$ZI$$Base;
//     end = (uint32_t *)&Image$$RW_IRAM2$$ZI$$Limit;

//     while (dst < end)
//     {
//         *dst = 0;
//         dst++;
//     }
// }
//************************** Function Implementations ***********************//

/**
 * @brief LED 闪烁任务
 *
 * @param[in]  pvParameters : 任务参数(未使用)
 *
 * @retval None
 */
void vLedTask(void *pvParameters)
{
    (void)pvParameters;
    uint32_t count = 0;

    while (1)
    {
        DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_PIN);
        log_i("LED Task running, count: %lu, tick: %lu", count++, xTaskGetTickCount());
        
        /* 延时 500ms */
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/**
 * @brief 任务1 - 每隔1秒输出信息
 *
 * @param[in]  pvParameters : 任务参数(未使用)
 *
 * @retval None
 */
void vTask1(void *pvParameters)
{
    (void)pvParameters;

    while (1)
    {
        printf("Task1: Hello from Thread 1\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief 任务2 - 每隔1.5秒输出信息
 *
 * @param[in]  pvParameters : 任务参数(未使用)
 *
 * @retval None
 */
void vTask2(void *pvParameters)
{
    (void)pvParameters;

    while (1)
    {
        printf("Task2: Hello from Thread 2\r\n");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/**
 * @brief 任务3 - 每隔2秒输出信息
 *
 * @param[in]  pvParameters : 任务参数(未使用)
 *
 * @retval None
 */
void vTask3(void *pvParameters)
{
    (void)pvParameters;

    while (1)
    {
        printf("Task3: Hello from Thread 3\r\n");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
