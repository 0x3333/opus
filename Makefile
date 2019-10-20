#       ____
#      / __ \____  __  _______
#     / / / / __ \/ / / / ___/
#    / /_/ / /_/ / /_/ (__  )
#    \____/ .___/\__,_/____/
#        /_/         Framework
#    Copyright (C) 2019 Tercio Gaudencio Filho.
#
#    This file is part of Opus Framework.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

#
# Build global options
# NOTE: Can be overridden externally.
#

# Compiler options here.
ifeq ($(USE_OPT),)
    USE_OPT = -O3 -ggdb -fomit-frame-pointer -falign-functions=16
endif

# C specific options here (added to USE_OPT).
ifeq ($(USE_COPT),)
    USE_COPT =
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
    USE_CPPOPT = -fno-rtti
endif

# Enable this if you want the linker to remove unused code and data.
ifeq ($(USE_LINK_GC),)
    USE_LINK_GC = yes
endif

# Linker extra options here.
ifeq ($(USE_LDOPT),)
    USE_LDOPT =
endif

# Enable this if you want link time optimizations (LTO).
ifeq ($(USE_LTO),)
    USE_LTO = yes
endif

# Enable this if you want to see the full log while compiling.
ifeq ($(USE_VERBOSE_COMPILE),)
    USE_VERBOSE_COMPILE = no
endif

# If enabled, this option makes the build process faster by not compiling
# modules not used in the current configuration.
ifeq ($(USE_SMART_BUILD),)
    USE_SMART_BUILD = yes
endif

#
# Build global options
####################################################################################################

####################################################################################################
# Architecture or project specific options
#

# Stack size to be allocated to the Cortex-M process stack. This stack is
# the stack used by the main() thread.
ifeq ($(USE_PROCESS_STACKSIZE),)
    USE_PROCESS_STACKSIZE = 0x400
endif

# Stack size to the allocated to the Cortex-M main/exceptions stack. This
# stack is used for processing interrupts and exceptions.
ifeq ($(USE_EXCEPTIONS_STACKSIZE),)
    USE_EXCEPTIONS_STACKSIZE = 0x400
endif

# Enables the use of FPU (no, softfp, hard).
ifeq ($(USE_FPU),)
    USE_FPU = no
endif

# FPU-related options.
ifeq ($(USE_FPU_OPT),)
    USE_FPU_OPT = -mfloat-abi=$(USE_FPU) -mfpu=fpv4-sp-d16
endif

#
# Architecture or project specific options
####################################################################################################

####################################################################################################
# Project, target, sources and paths
#

# Project Name
PROJECT = $(shell basename $(CURDIR))

# Target settings.
MCU  = cortex-m3

# Imported source files and paths.
APPDIR      := ./app
APPCONFDIR  := $(APPDIR)/cfg

LIBDIR      := ./lib
CHIBIOS     := $(LIBDIR)/chibios
FREERTOSDIR := $(LIBDIR)/freertos
OPUSDIR     := $(LIBDIR)/opus
CONFDIR     := $(OPUSDIR)/cfg

RESDIR      := $(OPUSDIR)/res
BUILDDIR    := ./out
DEPDIR      := ./.dep

# Startup files.
include $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32f1xx.mk

# HAL files.
include $(CHIBIOS)/os/hal/hal.mk

# Board files.
include $(CHIBIOS)/os/hal/ports/STM32/STM32F1xx/platform.mk
include $(CHIBIOS)/os/hal/boards/STM32F103C8_MINIMAL/board.mk

# Opus Framework files.
include $(OPUSDIR)/mk/opus.mk

# App files.
include $(APPDIR)/app.mk

# RTOS files.
ifeq ($(OP_RTOS_FREERTOS),1)
    # FreeRTOS
    $(info ** Building with FreeRTOS support)
    include $(CHIBIOS)/os/hal/osal/freertos/osal.mk
    include $(OPUSDIR)/mk/freertos.mk
else ifeq ($(OP_RTOS_CHIBIOSRT),1)
    # ChibiOS RT.
    $(info ** Building with ChibiOS RT support)
    include $(CHIBIOS)/os/license/license.mk
    include $(CHIBIOS)/os/hal/osal/rt-nil/osal.mk
    include $(CHIBIOS)/os/rt/rt.mk
    include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/port_v7m.mk
else
    $(error You must select OP_RTOS_FREERTOS or OP_RTOS_CHIBIOSRT in app.mk)
endif

# Other files (optional).
include $(CHIBIOS)/os/hal/lib/streams/streams.mk
include $(CHIBIOS)/os/hal/lib/complex/mfs/hal_mfs.mk
include $(CHIBIOS)/os/hal/lib/complex/soft_serial/hal_soft_serial.mk

# Bootloader
ifdef OP_BOOTLOADER
    LDSCRIPT = $(RESDIR)/STM32F103xB_DAPBOOT.ld
    APPDEFS += -DOP_BOOTLOADER
    $(info ** Building with bootloader)
else
    LDSCRIPT = $(RESDIR)/STM32F103xB.ld
    $(info ** Building without bootloader)
endif

$(info )

# C sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CSRC = $(ALLCSRC) \
       $(OPUSCSRC) \
       $(APPCSRC)

# C++ sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CPPSRC = $(ALLCPPSRC)

# List ASM source files here.
ASMSRC = $(ALLASMSRC)

# List ASM with preprocessor source files here.
ASMXSRC = $(ALLXASMSRC)

# Inclusion directories.
INCDIR = $(APPCONFDIR) $(CONFDIR) $(ALLINC) $(OPUSINCDIR) $(APPINCDIR)

# Define C warning options here.
CWARN = -Wall -Wextra -Wundef -Wstrict-prototypes

# Define C++ warning options here.
CPPWARN = -Wall -Wextra -Wundef

#
# Project, target, sources and paths
####################################################################################################

####################################################################################################
# Start of user section
#

UDEFS = $(APPDEFS) -DOP_RTOS_FREERTOS=$(OP_RTOS_FREERTOS) -DOP_RTOS_CHIBIOSRT=$(OP_RTOS_CHIBIOSRT)

# Define ASM defines here
UADEFS = $(UDEFS)

# List all user directories here
UINCDIR =

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS =

#
# End of user section
####################################################################################################

####################################################################################################
# Common rules
#

RULESPATH = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk
include $(RULESPATH)/arm-none-eabi.mk
include $(RULESPATH)/rules.mk

#
# Common rules
####################################################################################################

####################################################################################################
# Custom rules
#

include $(OPUSDIR)/mk/programmer.mk

#
# Custom rules
####################################################################################################
