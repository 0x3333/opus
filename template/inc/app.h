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
#ifndef _APP_H
#define _APP_H

// =================================================================================================
// Includes
// =================================================================================================

// Opus
#include "opus.h"

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

/**
 * This function will be called before any other hardware is initialized.
 */
void appInit(void);

/**
 * This function will be called after all hardware is initialized and the system ir ready to start.
 */
void appMain(void);

#if defined(OP_IDLE_HOOK)
/**
 * This function will be called after IDLE Task has finished running.
 *
 * It is therefore imperative that the hook function does not call any API functions that might
 * cause the idle task to block (delay, or a queue or semaphore function with a block time,
 * for example).
 */
void vApplicationIdleHook(void);
#endif

#endif /* _APP_H */