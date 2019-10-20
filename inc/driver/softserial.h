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
#ifndef _SOFTSERIAL_H
#define _SOFTSERIAL_H

// =================================================================================================
// Includes
// =================================================================================================

// Opus
#include "driver.h"

#ifdef OP_SOFT_SERIAL

// ChibiOS
#include "hal_soft_serial.h"
#include "stm32_tim.h"

// =================================================================================================
// Definitions
// =================================================================================================

#ifdef OP_SOFT_SERIAL_1
#define BS_SSD1 /*                           */ ((BaseSequentialStream *)&SSD1)
#endif
#ifdef OP_SOFT_SERIAL_2
#define BS_SSD2 /*                           */ ((BaseSequentialStream *)&SSD2)
#endif
#ifdef OP_SOFT_SERIAL_3
#define BS_SSD3 /*                           */ ((BaseSequentialStream *)&SSD3)
#endif
#ifdef OP_SOFT_SERIAL_4
#define BS_SSD4 /*                           */ ((BaseSequentialStream *)&SSD4)
#endif
#ifdef OP_SOFT_SERIAL_5
#define BS_SSD5 /*                           */ ((BaseSequentialStream *)&SSD5)
#endif
#ifdef OP_SOFT_SERIAL_6
#define BS_SSD6 /*                           */ ((BaseSequentialStream *)&SSD6)
#endif
#ifdef OP_SOFT_SERIAL_7
#define BS_SSD7 /*                           */ ((BaseSequentialStream *)&SSD7)
#endif
#ifdef OP_SOFT_SERIAL_8
#define BS_SSD8 /*                           */ ((BaseSequentialStream *)&SSD8)
#endif
#ifdef OP_SOFT_SERIAL_9
#define BS_SSD9 /*                           */ ((BaseSequentialStream *)&SSD9)
#endif
#ifdef OP_SOFT_SERIAL_10
#define BS_SSD10 /*                          */ ((BaseSequentialStream *)&SSD10)
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

#ifdef OP_SOFT_SERIAL_1
extern SoftSerialDriver SSD1;
#endif
#ifdef OP_SOFT_SERIAL_2
extern SoftSerialDriver SSD2;
#endif
#ifdef OP_SOFT_SERIAL_3
extern SoftSerialDriver SSD3;
#endif
#ifdef OP_SOFT_SERIAL_4
extern SoftSerialDriver SSD4;
#endif
#ifdef OP_SOFT_SERIAL_5
extern SoftSerialDriver SSD5;
#endif
#ifdef OP_SOFT_SERIAL_6
extern SoftSerialDriver SSD6;
#endif
#ifdef OP_SOFT_SERIAL_7
extern SoftSerialDriver SSD7;
#endif
#ifdef OP_SOFT_SERIAL_8
extern SoftSerialDriver SSD8;
#endif
#ifdef OP_SOFT_SERIAL_9
extern SoftSerialDriver SSD9;
#endif
#ifdef OP_SOFT_SERIAL_10
extern SoftSerialDriver SSD10;
#endif

void opSoftSerialInit(void);
void opSoftSerialStop(void);

#endif /* OP_SOFT_SERIAL */

#endif /* _SOFTSERIAL_H */