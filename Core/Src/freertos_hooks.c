/******************************************************************************
 * @file freertos_hooks.c
 * @brief FreeRTOS 静态内存分配和钩子函数
 *****************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#if (configSUPPORT_STATIC_ALLOCATION == 1)

/* 空闲任务的静态内存 */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

/* 定时器任务的静态内存 */
#if (configUSE_TIMERS == 1)
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];
#endif

/**
 * @brief 为空闲任务提供静态内存
 * 
 * @note 当 configSUPPORT_STATIC_ALLOCATION = 1 时必须实现此函数
 */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

#if (configUSE_TIMERS == 1)
/**
 * @brief 为定时器服务任务提供静态内存
 * 
 * @note 当 configSUPPORT_STATIC_ALLOCATION = 1 且 configUSE_TIMERS = 1 时必须实现此函数
 */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize)
{
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
    *ppxTimerTaskStackBuffer = &xTimerStack[0];
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
#endif /* configUSE_TIMERS */

#endif /* configSUPPORT_STATIC_ALLOCATION */

/**
 * @brief 堆栈溢出钩子函数
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;
    
    /* 栈溢出！进入死循环便于调试 */
    taskDISABLE_INTERRUPTS();
    while(1)
    {
        /* 在这里设置断点调试 */
    }
}

/**
 * @brief 内存分配失败钩子函数
 */
void vApplicationMallocFailedHook(void)
{
    /* 内存分配失败！进入死循环便于调试 */
    taskDISABLE_INTERRUPTS();
    while(1)
    {
        /* 在这里设置断点调试 */
    }
}