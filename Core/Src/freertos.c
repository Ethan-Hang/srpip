/******************************************************************************
 * @file freertos.c
 *
 * @par dependencies
 * - <stdio.h>
 * - "ti_msp_dl_config.h"
 * - "FreeRTOS.h"
 * - "task.h"
 * - "elog.h"
 *
 * @author Ethan-Hang
 *
 * @brief FreeRTOS task initialization and implementation
 *
 * Processing flow:
 * 1. FREERTOS_Init() creates all application tasks
 * 2. vLedTask toggles LED and logs status every 100ms
 * 3. vTask1/2/3 output periodic messages for testing
 *
 * @version V1.0 2025-11-15
 *          - Initial FreeRTOS task implementation
 *          - Created LED blinking task with logging
 *          - Created three demo tasks for testing scheduler
 *
 * @note 1 tab == 4 spaces!
 *
 *****************************************************************************/

//******************************** Includes *********************************//
#include <stdio.h>

#include "ti_msp_dl_config.h"

#include "FreeRTOS.h"
#include "task.h"

#include "elog.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//


//******************************** Defines **********************************//

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void vLedTask(void *pvParameters);
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void *pvParameters);
/* USER CODE END FunctionPrototypes */


/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of defaultTask */

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* Create LED blinking task */
    xTaskCreate(vLedTask, /* Task function */
                "LED",    /* Task name */
                256,      /* Stack size (words) */
                NULL,     /* Task parameter */
                1,        /* Task priority */
                NULL);    /* Task handle */

    /* Create Task1 */
    xTaskCreate(vTask1,  /* Task function */
                "Task1", /* Task name */
                256,     /* Stack size (words) */
                NULL,    /* Task parameter */
                2,       /* Task priority */
                NULL);   /* Task handle */

    /* Create Task2 */
    xTaskCreate(vTask2,  /* Task function */
                "Task2", /* Task name */
                256,     /* Stack size (words) */
                NULL,    /* Task parameter */
                2,       /* Task priority */
                NULL);   /* Task handle */

    /* Create Task3 */
    xTaskCreate(vTask3,  /* Task function */
                "Task3", /* Task name */
                256,     /* Stack size (words) */
                NULL,    /* Task parameter */
                2,       /* Task priority */
                NULL);   /* Task handle */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */


/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/**
 * @brief LED blinking task
 *
 * @param[in]  pvParameters : Task parameter (unused)
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
        log_i("LED Task running, count: %lu, tick: %lu", count++,
              xTaskGetTickCount());

        /* Delay 500ms */
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/**
 * @brief Task1 - Output message every 1 second
 *
 * @param[in]  pvParameters : Task parameter (unused)
 *
 * @retval None
 */
void vTask1(void *pvParameters)
{
    (void)pvParameters;

    while (1)
    {
        printf("Task1: Hello from Thread 1\r\n");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/**
 * @brief Task2 - Output message every 1.5 seconds
 *
 * @param[in]  pvParameters : Task parameter (unused)
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
 * @brief Task3 - Output message every 2 seconds
 *
 * @param[in]  pvParameters : Task parameter (unused)
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

/* USER CODE END Application */
