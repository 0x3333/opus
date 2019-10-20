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
#include "mfs.h"

#ifdef OP_MFS

// =================================================================================================
// Definitions
// =================================================================================================

// =================================================================================================
// External Declarations
// =================================================================================================

// =================================================================================================
// Exported Variables
// =================================================================================================

MFSDriver MFS1;

// =================================================================================================
// Local Variables / Types
// =================================================================================================

static const MFSConfig mfs1_config = {
    .flashp = (BaseFlash *)&EFLD1,
    .erased = 0xFFFFFFFFU,
    .bank_size = OP_MFS_BANK_SIZE,

    .bank0_start = OP_MFS_BANK0_START,
    .bank1_start = OP_MFS_BANK1_START,

    .bank0_sectors = 4U,
    .bank1_sectors = 4U};

// =================================================================================================
// Local Functions
// =================================================================================================

// =================================================================================================
// Exported Functions
// =================================================================================================

void opMfsInit()
{
    eflStart(&EFLD1, NULL);

    mfsObjectInit(&MFS1);
    mfsStart(&MFS1, &mfs1_config);
}

#endif /* OP_MFSL */