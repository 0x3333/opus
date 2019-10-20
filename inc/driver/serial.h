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
#ifndef _SERIAL_H
#define _SERIAL_H

// =================================================================================================
// Includes
// =================================================================================================

// Opus
#include "driver.h"

#ifdef OP_SERIAL

// =================================================================================================
// Definitions
// =================================================================================================

#ifdef OP_SERIAL_1
#define BS_SD1 /*                            */ ((BaseSequentialStream *)&SD1)
#endif

#ifdef OP_SERIAL_2
#define BS_SD2 /*                            */ ((BaseSequentialStream *)&SD2)
#endif

#ifdef OP_SERIAL_3
#define BS_SD3 /*                            */ ((BaseSequentialStream *)&SD3)
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

void opSerialInit(void);

#endif /* OP_SERIAL */

#endif /* _SERIAL_H */