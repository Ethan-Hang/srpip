/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 *
 ******************************************************************************
 */
/* USER CODE END Header */

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
    /* 创建 LED 闪烁任务 */
    xTaskCreate(vLedTask, /* 任务函数 */
                "LED",    /* 任务名称 */
                256,      /* 栈大小(字) */
                NULL,     /* 任务参数 */
                1,        /* 任务优先级 */
                NULL);    /* 任务句柄 */

    /* 创建任务1 */
    xTaskCreate(vTask1,  /* 任务函数 */
                "Task1", /* 任务名称 */
                256,     /* 栈大小(字) */
                NULL,    /* 任务参数 */
                2,       /* 任务优先级 */
                NULL);   /* 任务句柄 */

    /* 创建任务2 */
    xTaskCreate(vTask2,  /* 任务函数 */
                "Task2", /* 任务名称 */
                256,     /* 栈大小(字) */
                NULL,    /* 任务参数 */
                2,       /* 任务优先级 */
                NULL);   /* 任务句柄 */

    /* 创建任务3 */
    xTaskCreate(vTask3,  /* 任务函数 */
                "Task3", /* 任务名称 */
                256,     /* 栈大小(字) */
                NULL,    /* 任务参数 */
                2,       /* 任务优先级 */
                NULL);   /* 任务句柄 */
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
        log_i("LED Task running, count: %lu, tick: %lu", count++,
              xTaskGetTickCount());

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
        vTaskDelay(pdMS_TO_TICKS(100));
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

/* USER CODE END Application */
