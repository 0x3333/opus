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

// App
#include "app.h"

// =================================================================================================
// Definitions
// =================================================================================================

#define APP_THREAD_STACK_SIZE 512

// =================================================================================================
// External Declarations
// =================================================================================================

// =================================================================================================
// Exported Variables
// =================================================================================================

// =================================================================================================
// Local Variables / Types
// =================================================================================================

THD_WORKING_AREA(AppWA, APP_THREAD_STACK_SIZE);

// =================================================================================================
// Local Functions
// =================================================================================================

THD_FUNCTION(App, pvParameters)
{
    UNUSED(pvParameters);

    DEBUG(NL("App Thread created!"));
    while (1)
    {
        osalThreadSleepMilliseconds(50);
    }
}

// =================================================================================================
// Exported Functions
// =================================================================================================

void appInit(void)
{
}

void appMain(void)
{
    THD_CREATE_STATIC(App, AppWA, APP_THREAD_STACK_SIZE, "APP", NULL, NORMAL_PRIORITY);
}

#if defined(OP_IDLE_HOOK)
void vApplicationIdleHook(void)
{
}
#endif