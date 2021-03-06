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
#ifndef _DRIVER_H
#define _DRIVER_H

// =================================================================================================
// Includes
// =================================================================================================

// FreeRTOS
#if defined(OP_RTOS_FREERTOS) && OP_RTOS_FREERTOS == 1
#include "FreeRTOS.h"
#endif
// ChibiOS RT
#if defined(OP_RTOS_CHIBIOSRT) && OP_RTOS_CHIBIOSRT == 1
#include "ch.h"
#endif

// ChibiOS
#include "hal.h"
#include "chprintf.h"

// Opus
#include "debug.h"
#include "logger.h"
#include "types.h"
#include "macros.h"

// =================================================================================================
// Definitions
// =================================================================================================

// =================================================================================================
// Data structures / Types
// =================================================================================================

// =================================================================================================
// Macros
// =================================================================================================

// =================================================================================================
// External Declarations
// =================================================================================================

#endif /* _DRIVER_H */