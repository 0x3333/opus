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
#ifndef _MACROS_H
#define _MACROS_H

// =================================================================================================
// Includes
// =================================================================================================

// =================================================================================================
// Definitions
// =================================================================================================

// =================================================================================================
// Data structures / Types
// =================================================================================================

// =================================================================================================
// Macros
// =================================================================================================

#define FORCE_INLINE /*                      */ __attribute__((always_inline)) inline
#define UNUSED(x) /*                         */ (void)(x)

// Macros to make a string from a macro
#define STRINGIFY_(M) /*                     */ #M
#define STRINGIFY(M) /*                      */ STRINGIFY_(M)

// Terminate a String with \n\r
#define NL(s) /*                             */ "" s "\n\r"

// =================================================================================================
// External Declarations
// =================================================================================================

#endif /* _MACROS_H */