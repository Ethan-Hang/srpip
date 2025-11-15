/*
 * Copyright (c) 2022, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== AppHooks_freertos.c ========
 */
#include <FreeRTOS.h>
#include <task.h>

#if (configSUPPORT_STATIC_ALLOCATION == 1)

/* Static memory for idle task */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

/* Static memory for timer task */
#if (configUSE_TIMERS == 1)
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];
#endif

/**
 * @brief Provide static memory for idle task
 * 
 * @note This function must be implemented when configSUPPORT_STATIC_ALLOCATION = 1
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
 * @brief Provide static memory for timer service task
 * 
 * @note This function must be implemented when configSUPPORT_STATIC_ALLOCATION = 1 and configUSE_TIMERS = 1
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
 * @brief Stack overflow hook function
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;
    
    /* Stack overflow! Enter infinite loop for debugging */
    taskDISABLE_INTERRUPTS();
    while(1)
    {
        /* Set breakpoint here for debugging */
    }
}

/**
 * @brief Malloc failed hook function
 */
void vApplicationMallocFailedHook(void)
{
    /* Memory allocation failed! Enter infinite loop for debugging */
    taskDISABLE_INTERRUPTS();
    while(1)
    {
        /* Set breakpoint here for debugging */
    }
}

#if (configCHECK_FOR_STACK_OVERFLOW)
    /*
     *  ======== vApplicationStackOverflowHook ========
     *  When stack overflow checking is enabled the application must provide a
     *  stack overflow hook function. This default hook function is declared as
     *  weak, and will be used by default, unless the application specifically
     *  provides its own hook function.
     */
    #if defined(__IAR_SYSTEMS_ICC__)
__weak void vApplicationStackOverflowHook_TI(TaskHandle_t pxTask, char *pcTaskName)
    #elif (defined(__TI_COMPILER_VERSION__))
        #pragma WEAK(vApplicationStackOverflowHook_TI)
void vApplicationStackOverflowHook_TI(TaskHandle_t pxTask, char *pcTaskName)
    #elif (defined(__GNUC__) || defined(__ti_version__))
void __attribute__((weak)) vApplicationStackOverflowHook_TI(TaskHandle_t pxTask, char *pcTaskName)
    #endif
{
    /* default to spin upon stack overflow */
    while (1) {}
}
#endif
