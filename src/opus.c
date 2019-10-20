/**
 *      ____
 *     / __ \____  __  _______
 *    / / / / __ \/ / / / ___/
 *   / /_/ / /_/ / /_/ (__  )
 *   \____/ .___/\__,_/____/
 *       /_/         Framework
 *   Copyright (C) 2019 Tercio Gaudencio Filho.
 *
 *   This file is part of Opus Framework.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
// =================================================================================================
// Includes
// =================================================================================================

// Opus
#include "opus.h"
#include "chprintf.h"

// =================================================================================================
// Definitions
// =================================================================================================

#define WATCHDOG_THREAD_STACK_SIZE 64

// =================================================================================================
// External Declarations
// =================================================================================================

extern void appInit(void); // User Application Initialization
extern void appMain(void); // User Application Entrypoint

// =================================================================================================
// Exported Variables
// =================================================================================================

// =================================================================================================
// Local Variables / Types
// =================================================================================================

#ifdef OP_WATCHDOG_LED
THD_WORKING_AREA(WatchdogLedWA, WATCHDOG_THREAD_STACK_SIZE);
#endif

// =================================================================================================
// Local Functions
// =================================================================================================

static void mainInit(void)
{
    palSetLineMode(OP_WATCHDOG_LED_LINE, PAL_MODE_OUTPUT_OPENDRAIN);
    palClearLine(OP_WATCHDOG_LED_LINE);
}

#ifdef OP_WATCHDOG_LED
THD_FUNCTION(WatchdogLed, pvParameters)
{
    UNUSED(pvParameters);

    while (1)
    {
        // Blink Watchdog Onboard Led
        DEBUG(NL("."));
        palToggleLine(OP_WATCHDOG_LED_LINE);
        osalThreadSleepMilliseconds(OP_WATCHDOG_LED_DELAY);
    }
}
#endif

// =================================================================================================
// Exported Functions
// =================================================================================================

int main(void)
{
    // System initialization
    halInit();
    osalInit();
#if defined(OP_RTOS_CHIBIOSRT) && OP_RTOS_CHIBIOSRT == 1
    chSysInit();
#endif
    mainInit();

    // User Application Initialization
    appInit();

    // Peripherals Initialization
#if defined(OP_SERIAL)
    opSerialInit();
#endif
#if defined(OP_USB_SERIAL)
    opUsbCdcInit();
#endif
#if defined(OP_SOFT_SERIAL)
    opSoftSerialInit();
#endif
#if defined(OP_MFS)
    opMfsInit();
#endif

    // User Application EntryPoint
    appMain();

#ifdef OP_WATCHDOG_LED
    THD_CREATE_STATIC(WatchdogLed, WatchdogLedWA, WATCHDOG_THREAD_STACK_SIZE, "WDLED", NULL, MIN_PRIORITY);
#endif

#if defined(OP_RTOS_FREERTOS) && OP_RTOS_FREERTOS == 1
    vTaskStartScheduler(); // This function never returns
#elif defined(OP_RTOS_CHIBIOSRT) && OP_RTOS_CHIBIOSRT == 1
    while(1){
        chThdSleep(TIME_INFINITE); // Sleep forever
    };
#else
    #error You must select OP_RTOS_FREERTOS or OP_RTOS_CHIBIOSRT in app.mk
#endif

    return 0;
}

#if defined(OP_RTOS_FREERTOS) && OP_RTOS_FREERTOS == 1
void vApplicationAssertHook(const char *file, unsigned long line, const char *reason)
{
    UNUSED(file);
    UNUSED(line);
    UNUSED(reason);

    taskDISABLE_INTERRUPTS();
    while (1)
        ;
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    UNUSED(xTask);
    UNUSED(pcTaskName);

    while (1)
        ;
}
#endif