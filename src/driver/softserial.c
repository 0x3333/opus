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
#include "softserial.h"

#ifdef OP_SOFT_SERIAL

// =================================================================================================
// Definitions
// =================================================================================================

#define SSD_TIMER /*                         */ STM32_TIM3
#define SSD_TIMER_CLOCK /*                   */ STM32_TIMCLK1
#define SSD_TIMER_HANDLER /*                 */ STM32_TIM3_HANDLER
#define SSD_TIMER_IRQ_NUMBER /*              */ STM32_TIM3_NUMBER
#define SSD_TIMER_ENABLE() /*                */ rccEnableTIM3(true)
#define SSD_TIMER_DISABLE() /*               */ rccDisableTIM3()
#define SSD_TIMER_RESET() /*                 */ rccResetTIM3()
#define SSD_TIMER_FREQ /*                    */ OP_SOFT_SERIAL_BAUD *OP_SOFT_SERIAL_BITRATE_MULTIPLIER
#define SSD_TIMER_ARR /*                     */ (uint16_t)((SSD_TIMER_CLOCK / (SSD_TIMER_FREQ)) - 1)
#define SSD_TIMER_IRQ_PRIORITY /*            */ 5

// =================================================================================================
// External Declarations
// =================================================================================================

// =================================================================================================
// Exported Variables
// =================================================================================================

#ifdef OP_SOFT_SERIAL_1
SoftSerialDriver SSD1;
#endif
#ifdef OP_SOFT_SERIAL_2
SoftSerialDriver SSD2;
#endif
#ifdef OP_SOFT_SERIAL_3
SoftSerialDriver SSD3;
#endif
#ifdef OP_SOFT_SERIAL_4
SoftSerialDriver SSD4;
#endif
#ifdef OP_SOFT_SERIAL_5
SoftSerialDriver SSD5;
#endif
#ifdef OP_SOFT_SERIAL_6
SoftSerialDriver SSD6;
#endif
#ifdef OP_SOFT_SERIAL_7
SoftSerialDriver SSD7;
#endif
#ifdef OP_SOFT_SERIAL_8
SoftSerialDriver SSD8;
#endif
#ifdef OP_SOFT_SERIAL_9
SoftSerialDriver SSD9;
#endif
#ifdef OP_SOFT_SERIAL_10
SoftSerialDriver SSD10;
#endif

// =================================================================================================
// Local Variables / Types
// =================================================================================================

typedef void (*softserial_timercallback_t)(void);

#ifdef OP_SOFT_SERIAL_1
static const SoftSerialConfig ssd1_config = {
    OP_SOFT_SERIAL_BITRATE_MULTIPLIER,
    false,
    OP_SOFT_SERIAL_1_RX_LINE,
    OP_SOFT_SERIAL_1_TX_LINE};
#endif
#ifdef OP_SOFT_SERIAL_2
static const SoftSerialConfig ssd2_config = {
    OP_SOFT_SERIAL_BITRATE_MULTIPLIER,
    false,
    OP_SOFT_SERIAL_2_RX_LINE,
    OP_SOFT_SERIAL_2_TX_LINE};
#endif
#ifdef OP_SOFT_SERIAL_3
static const SoftSerialConfig ssd3_config = {
    OP_SOFT_SERIAL_BITRATE_MULTIPLIER,
    false,
    OP_SOFT_SERIAL_3_RX_LINE,
    OP_SOFT_SERIAL_3_TX_LINE};
#endif
#ifdef OP_SOFT_SERIAL_4
static const SoftSerialConfig ssd4_config = {
    OP_SOFT_SERIAL_BITRATE_MULTIPLIER,
    false,
    OP_SOFT_SERIAL_4_RX_LINE,
    OP_SOFT_SERIAL_4_TX_LINE};
#endif
#ifdef OP_SOFT_SERIAL_5
static const SoftSerialConfig ssd5_config = {
    OP_SOFT_SERIAL_BITRATE_MULTIPLIER,
    false,
    OP_SOFT_SERIAL_5_RX_LINE,
    OP_SOFT_SERIAL_5_TX_LINE};
#endif
#ifdef OP_SOFT_SERIAL_6
static const SoftSerialConfig ssd6_config = {
    OP_SOFT_SERIAL_BITRATE_MULTIPLIER,
    false,
    OP_SOFT_SERIAL_6_RX_LINE,
    OP_SOFT_SERIAL_6_TX_LINE};
#endif
#ifdef OP_SOFT_SERIAL_7
static const SoftSerialConfig ssd7_config = {
    OP_SOFT_SERIAL_BITRATE_MULTIPLIER,
    false,
    OP_SOFT_SERIAL_7_RX_LINE,
    OP_SOFT_SERIAL_7_TX_LINE};
#endif
#ifdef OP_SOFT_SERIAL_8
static const SoftSerialConfig ssd8_config = {
    OP_SOFT_SERIAL_BITRATE_MULTIPLIER,
    false,
    OP_SOFT_SERIAL_8_RX_LINE,
    OP_SOFT_SERIAL_8_TX_LINE};
#endif
#ifdef OP_SOFT_SERIAL_9
static const SoftSerialConfig ssd9_config = {
    OP_SOFT_SERIAL_BITRATE_MULTIPLIER,
    false,
    OP_SOFT_SERIAL_9_RX_LINE,
    OP_SOFT_SERIAL_9_TX_LINE};
#endif
#ifdef OP_SOFT_SERIAL_10
static const SoftSerialConfig ssd10_config = {
    OP_SOFT_SERIAL_BITRATE_MULTIPLIER,
    false,
    OP_SOFT_SERIAL_10_RX_LINE,
    OP_SOFT_SERIAL_10_TX_LINE};
#endif
// =================================================================================================
// Local Functions
// =================================================================================================

OSAL_IRQ_HANDLER(SSD_TIMER_HANDLER)
{
    OSAL_IRQ_PROLOGUE();
    SSD_TIMER->SR = 0; // Clear pending IRQs

    osalSysLockFromISR();
#ifdef OP_SOFT_SERIAL_1
    ssdTickI(&SSD1);
#endif
#ifdef OP_SOFT_SERIAL_2
    ssdTickI(&SSD2);
#endif
#ifdef OP_SOFT_SERIAL_3
    ssdTickI(&SSD3);
#endif
#ifdef OP_SOFT_SERIAL_4
    ssdTickI(&SSD4);
#endif
#ifdef OP_SOFT_SERIAL_5
    ssdTickI(&SSD5);
#endif
#ifdef OP_SOFT_SERIAL_6
    ssdTickI(&SSD6);
#endif
#ifdef OP_SOFT_SERIAL_7
    ssdTickI(&SSD7);
#endif
#ifdef OP_SOFT_SERIAL_8
    ssdTickI(&SSD8);
#endif
#ifdef OP_SOFT_SERIAL_9
    ssdTickI(&SSD9);
#endif
#ifdef OP_SOFT_SERIAL_10
    ssdTickI(&SSD10);
#endif
    osalSysUnlockFromISR();

    OSAL_IRQ_EPILOGUE();
}

static void timerStop(void)
{
    SSD_TIMER->CR1 = 0;  // Timer disabled
    SSD_TIMER->DIER = 0; // All IRQs disabled
    SSD_TIMER->SR = 0;   // Clear pending IRQs

    nvicDisableVector(SSD_TIMER_IRQ_NUMBER);
    SSD_TIMER_DISABLE();
}

static void timerStart(void)
{
    SSD_TIMER_ENABLE();
    SSD_TIMER_RESET();

    nvicEnableVector(SSD_TIMER_IRQ_NUMBER, SSD_TIMER_IRQ_PRIORITY);

    SSD_TIMER->CR1 = 0;  // Initially stopped
    SSD_TIMER->CR2 = 0;  //
    SSD_TIMER->PSC = 0;  // Prescaler value
    SSD_TIMER->SR = 0;   // Clear pending IRQs
    SSD_TIMER->DIER = 0; // DMA-related DIER bits
    SSD_TIMER->PSC = 0;  // Prescaler value

    SSD_TIMER->ARR = SSD_TIMER_ARR;       // Time constant
    SSD_TIMER->EGR = 0;                   // Update event
    SSD_TIMER->CNT = 0;                   // Reset counter
    SSD_TIMER->SR = 0;                    // Clear pending IRQs
    SSD_TIMER->CR1 = STM32_TIM_CR1_CEN;   // Enable Timer
    SSD_TIMER->DIER = STM32_TIM_DIER_UIE; // Update Event IRQ enabled
}

// =================================================================================================
// Exported Functions
// =================================================================================================

void opSoftSerialInit(void)
{
#ifdef OP_SOFT_SERIAL_1
    palSetLineMode(OP_SOFT_SERIAL_1_RX_LINE, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(OP_SOFT_SERIAL_1_TX_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    ssdObjectInit(&SSD1);
    ssdStart(&SSD1, &ssd1_config);
#endif
#ifdef OP_SOFT_SERIAL_2
    palSetLineMode(OP_SOFT_SERIAL_2_RX_LINE, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(OP_SOFT_SERIAL_2_TX_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    ssdObjectInit(&SSD2);
    ssdStart(&SSD2, &ssd2_config);
#endif
#ifdef OP_SOFT_SERIAL_3
    palSetLineMode(OP_SOFT_SERIAL_3_RX_LINE, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(OP_SOFT_SERIAL_3_TX_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    ssdObjectInit(&SSD3);
    ssdStart(&SSD3, &ssd3_config);
#endif
#ifdef OP_SOFT_SERIAL_4
    palSetLineMode(OP_SOFT_SERIAL_4_RX_LINE, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(OP_SOFT_SERIAL_4_TX_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    ssdObjectInit(&SSD4);
    ssdStart(&SSD4, &ssd4_config);
#endif
#ifdef OP_SOFT_SERIAL_5
    palSetLineMode(OP_SOFT_SERIAL_5_RX_LINE, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(OP_SOFT_SERIAL_5_TX_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    ssdObjectInit(&SSD5);
    ssdStart(&SSD5, &ssd5_config);
#endif
#ifdef OP_SOFT_SERIAL_6
    palSetLineMode(OP_SOFT_SERIAL_6_RX_LINE, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(OP_SOFT_SERIAL_6_TX_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    ssdObjectInit(&SSD6);
    ssdStart(&SSD6, &ssd6_config);
#endif
#ifdef OP_SOFT_SERIAL_7
    palSetLineMode(OP_SOFT_SERIAL_7_RX_LINE, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(OP_SOFT_SERIAL_7_TX_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    ssdObjectInit(&SSD7);
    ssdStart(&SSD7, &ssd7_config);
#endif
#ifdef OP_SOFT_SERIAL_8
    palSetLineMode(OP_SOFT_SERIAL_8_RX_LINE, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(OP_SOFT_SERIAL_8_TX_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    ssdObjectInit(&SSD8);
    ssdStart(&SSD8, &ssd8_config);
#endif
#ifdef OP_SOFT_SERIAL_9
    palSetLineMode(OP_SOFT_SERIAL_9_RX_LINE, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(OP_SOFT_SERIAL_9_TX_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    ssdObjectInit(&SSD9);
    ssdStart(&SSD9, &ssd9_config);
#endif
#ifdef OP_SOFT_SERIAL_10
    palSetLineMode(OP_SOFT_SERIAL_10_RX_LINE, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(OP_SOFT_SERIAL_10_TX_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    ssdObjectInit(&SSD10);
    ssdStart(&SSD10, &ssd10_config);
#endif

    timerStart();
}

void opSoftSerialStop(void)
{
    timerStop();

#ifdef OP_SOFT_SERIAL_1
    ssdStop(&SSD1);
#endif
#ifdef OP_SOFT_SERIAL_2
    ssdStop(&SSD2);
#endif
#ifdef OP_SOFT_SERIAL_3
    ssdStop(&SSD3);
#endif
#ifdef OP_SOFT_SERIAL_4
    ssdStop(&SSD4);
#endif
#ifdef OP_SOFT_SERIAL_5
    ssdStop(&SSD5);
#endif
#ifdef OP_SOFT_SERIAL_6
    ssdStop(&SSD6);
#endif
#ifdef OP_SOFT_SERIAL_7
    ssdStop(&SSD7);
#endif
#ifdef OP_SOFT_SERIAL_8
    ssdStop(&SSD8);
#endif
#ifdef OP_SOFT_SERIAL_9
    ssdStop(&SSD9);
#endif
#ifdef OP_SOFT_SERIAL_10
    ssdStop(&SSD10);
#endif
}

#endif /* OP_SOFT_SERIAL */