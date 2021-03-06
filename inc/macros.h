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

// Terminate a String with \r\n
#define NL(s) /*                             */ "" s "\r\n"

#define BYTE_TO_BINARY_PATTERN /*            */ "%c%c%c%c %c%c%c%c"
#define BYTE_TO_BINARY(byte) /*              */ ((byte)&b10000000 ? '1' : '0'), \
                                                ((byte)&b01000000 ? '1' : '0'), \
                                                ((byte)&b00100000 ? '1' : '0'), \
                                                ((byte)&b00010000 ? '1' : '0'), \
                                                ((byte)&b00001000 ? '1' : '0'), \
                                                ((byte)&b00000100 ? '1' : '0'), \
                                                ((byte)&b00000010 ? '1' : '0'), \
                                                ((byte)&b00000001 ? '1' : '0')

#define PRINT_FUNC /*                        */ "%s:%d:%s\r\n", __FILE__, __LINE__, __func__
#define PRINT_BYTE(prefix, bt, suffix) /*    */ prefix BYTE_TO_BINARY_PATTERN suffix, \
                                                           BYTE_TO_BINARY(bt)
#define PRINT_WORD(prefix, bt, suffix) /*    */ prefix BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN suffix, \
                                                           BYTE_TO_BINARY(bt >> 8), BYTE_TO_BINARY(bt)
#define PRINT_DWORD(prefix, bt, suffix) /*   */ prefix BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN suffix, \
                                                           BYTE_TO_BINARY(bt >> 24),                                                                                              \
                                                           BYTE_TO_BINARY(bt >> 16),                                                                                              \
                                                           BYTE_TO_BINARY(bt >> 8),                                                                                               \
                                                           BYTE_TO_BINARY(bt)

// =================================================================================================
// External Declarations
// =================================================================================================

#endif /* _MACROS_H */