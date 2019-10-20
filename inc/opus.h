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
#ifndef _OPUS_H
#define _OPUS_H

// =================================================================================================
// Includes
// =================================================================================================

#if defined(OP_RTOS_FREERTOS) && OP_RTOS_FREERTOS == 1
// FreeRTOS
#include "FreeRTOS.h"
#elif defined(OP_RTOS_CHIBIOSRT) && OP_RTOS_CHIBIOSRT == 1
// ChibiOS RT
#include "ch.h"
#endif

// Opus
#include "driver.h"
#include "serial.h"
#include "usbcdc.h"
#include "softserial.h"
#include "mfs.h"

// =================================================================================================
// Definitions
// =================================================================================================

#if defined(OP_RTOS_FREERTOS) && OP_RTOS_FREERTOS == 1
#define MIN_PRIORITY /*               */ (tskIDLE_PRIORITY + 1)
#define NORMAL_PRIORITY /*            */ ((uint8_t)(((MAX_PRIORITY - MIN_PRIORITY) / 2) + 1))
#define MAX_PRIORITY /*               */ configMAX_PRIORITIES

// Static Thread creating helper, to be used with THD_WORKING_AREA and THD_FUNCTION macros
#define THD_CREATE_STATIC(tname, twa, tsize, tlabel, param, tprio)                    \
    xTaskCreateStatic(tname,         /* Thread Function                            */ \
                      tlabel,        /* Thread Label                               */ \
                      tsize,         /* Thread Stack                               */ \
                      param,         /* Parameters                                 */ \
                      tprio,         /* Priority                                   */ \
                      twa##Stack,    /* Array to use as the task's stack           */ \
                      &twa##Buffer); /* Variable to hold the task's data structure */

#elif defined(OP_RTOS_CHIBIOSRT) && OP_RTOS_CHIBIOSRT == 1
// Minimum priority for a Thread
#define MIN_PRIORITY /*               */ LOWPRIO
#define NORMAL_PRIORITY /*            */ NORMALPRIO
#define MAX_PRIORITY /*               */ HIGHPRIO

// Static Thread creating helper, to be used with THD_WORKING_AREA and THD_FUNCTION macros
#define THD_CREATE_STATIC(tname, twa, tsize, tlabel, param, tprio)                         \
    {                                                                                      \
        thread_t *staticThread = chThdCreateStatic(twa,         /* Thread Stack         */ \
                                                   sizeof(twa), /* Thread Stack Size    */ \
                                                   tprio,       /* Priority             */ \
                                                   tname,       /* Thread Function      */ \
                                                   param);      /* Parameters           */ \
        chRegSetThreadNameX(staticThread, tlabel);              /* Thread Label         */ \
    }
#endif

// =================================================================================================
// Data structures / Types
// =================================================================================================

// =================================================================================================
// Macros
// =================================================================================================

// =================================================================================================
// External Declarations
// =================================================================================================

int main(void);

#endif /* _OPUS_H */