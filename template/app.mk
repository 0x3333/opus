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

APPSRCDIR = $(APPDIR)/src
APPINCDIR = $(APPDIR)/inc

# List all C Source Files
APPCSRC = $(APPSRCDIR)/app.c

# OOCD Interface and Target, overridable
ifeq ($(OOCD_INTERFACE),)
OOCD_INTERFACE = $(OOCD_HOME)/scripts/interface/stlink.cfg
endif
ifeq ($(OOCD_TARGET),)
OOCD_TARGET    = $(OOCD_HOME)/scripts/target/stm32f1x.cfg
endif

#
# Application Definitions
#
# Debug/Release Build, comment to release build
APPDEFS += -DOP_DEBUG
# Debug Serial Driver
APPDEFS += -DOP_DEBUG_DRIVER=SD1

#
# RTOS
#
OP_RTOS_FREERTOS = 1
OP_RTOS_CHIBIOSRT = 0

#
# Bootloader App base address
#
# BL_APP_BASE_ADDRESS = 0x08004000
# Bootloader Build Defines
# ex.: Use button on PA8, active low
# BL_DEFS = -DHAVE_BUTTON=1 -DBUTTON_GPIO_PORT=GPIOA -DBUTTON_GPIO_PIN=GPIO8 -DBUTTON_ACTIVE_HIGH=0

#
# ChibiOS RT options
#
# APPDEFS += -DCH_DBG_STATISTICS=TRUE
# APPDEFS += -DCH_DBG_SYSTEM_STATE_CHECK=TRUE
# APPDEFS += -DCH_DBG_ENABLE_CHECKS=TRUE
# APPDEFS += -DCH_DBG_ENABLE_ASSERTS=TRUE
# APPDEFS += -DCH_DBG_TRACE_MASK=TRUE
# APPDEFS += -DCH_DBG_ENABLE_STACK_CHECK=TRUE
# APPDEFS += -DCH_DBG_FILL_THREADS=TRUE
