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
#ifndef _DEBUG_H
#define _DEBUG_H

// =================================================================================================
// Includes
// =================================================================================================

#ifdef OP_DEBUG
// ChibiOS
#include "hal.h"
#include "chprintf.h"

// Opus
#include "types.h"
#ifdef _USB_SERIAL
#include "usbcdc.h"
#endif
#endif

// =================================================================================================
// Definitions
// =================================================================================================

// =================================================================================================
// Data structures / Types
// =================================================================================================

// =================================================================================================
// Macros
// =================================================================================================

#ifdef OP_DEBUG

#define FIX_FOR_RELEASE(stmt) /*             */ stmt
#define DEBUG(...) /*                        */ chprintf((BaseSequentialStream *)&OP_DEBUG_DRIVER, __VA_ARGS__);

#else

#define FIX_FOR_RELEASE(stmt) /*             */ _Pragma("GCC error \"Must be fixed for release version\"")
#define DEBUG(...)

#define DEBUG_FUNC() /*                      */ DEBUG(PRINT_FUNC())
#define DEBUG_BYTE(prefix, bt, suffix) /*    */ DEBUG(PRINT_BYTE(prefix, bt, suffix))
#define DEBUG_WORD(prefix, bt, suffix) /*    */ DEBUG(PRINT_WORD(prefix, bt, suffix))
#define DEBUG_DWORD(prefix, bt, suffix) /*   */ DEBUG(PRINT_DWORD(prefix, bt, suffix))


#endif /* OP_DEBUG */

// =================================================================================================
// External Declarations
// =================================================================================================

#endif /* _DEBUG_H */