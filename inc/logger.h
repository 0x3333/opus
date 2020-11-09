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
#ifndef _LOGGER_H
#define _LOGGER_H

// =================================================================================================
// Includes
// =================================================================================================

#ifdef OP_LOGGER
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

#ifdef OP_LOGGER

#define LOG(...) /*                        */ chprintf((BaseSequentialStream *)&OP_LOGGER_DRIVER, __VA_ARGS__);
#define LOG_FUNC() /*                      */ DEBUG("%s:%d:%s\r\n", __FILE__, __LINE__, __func__)
#define LOG_T(fmt, ...) /*                      */ LOG("[%s] " fmt, THREAD_ID(), ##__VA_ARGS__)

#else

#define LOG(...)
#define LOG_FUNC()
#define THREAD_ID()

#endif /* OP_LOGGER */

// =================================================================================================
// External Declarations
// =================================================================================================

#endif /* _LOGGER_H */