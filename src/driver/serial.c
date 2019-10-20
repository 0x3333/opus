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
#include "serial.h"

#ifdef OP_SERIAL

// =================================================================================================
// Definitions
// =================================================================================================

// =================================================================================================
// External Declarations
// =================================================================================================

// =================================================================================================
// Exported Variables
// =================================================================================================

// =================================================================================================
// Local Variables / Types
// =================================================================================================

#ifdef OP_SERIAL_1
static const SerialConfig sd1_config = {
    OP_SERIAL_1_BAUD,
    0,
    USART_CR2_STOP1_BITS,
    0};
#endif

#ifdef OP_SERIAL_2
static const SerialConfig sd2_config = {
    OP_SERIAL_2_BAUD,
    0,
    USART_CR2_STOP1_BITS,
    0};
#endif

#ifdef OP_SERIAL_3
static const SerialConfig sd3_config = {
    OP_SERIAL_3_BAUD,
    0,
    USART_CR2_STOP1_BITS,
    0};
#endif

// =================================================================================================
// Local Functions
// =================================================================================================

// =================================================================================================
// Exported Functions
// =================================================================================================

void opSerialInit()
{
#ifdef OP_SERIAL_1
    palSetLineMode(OP_SERIAL_1_TX_LINE, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetLineMode(OP_SERIAL_1_RX_LINE, PAL_MODE_INPUT);

    sdStart(&SD1, &sd1_config);
#endif
#ifdef OP_SERIAL_2
    palSetLineMode(OP_SERIAL_2_TX_LINE, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetLineMode(OP_SERIAL_2_RX_LINE, PAL_MODE_INPUT);

    sdStart(&SD2, &sd2_config);
#endif
#ifdef OP_SERIAL_3
    palSetLineMode(OP_SERIAL_3_TX_LINE, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetLineMode(OP_SERIAL_3_RX_LINE, PAL_MODE_INPUT);

    sdStart(&SD3, &sd3_config);
#endif
}

#endif /* OP_SERIAL */