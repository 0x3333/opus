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

.PHONY: boot flash erase gdb

ifndef BL_APP_BASE_ADDRESS
BL_APP_BASE_ADDRESS = 0x08004000
endif

# Check for programmers defines
check:
ifndef PROGRAMMER
$(error PROGRAMMER is not set)
endif
ifeq ($(PROGRAMMER),STLINK)
ifndef OOCD_HOME
	$(error OOCD_HOME is not set)
endif
endif
ifeq ($(PROGRAMMER),BMP)
ifndef BMP_PORT
	$(error BMP_PORT is not set)
endif
endif

# DAP Bootloader
boot: | check
	cd lib/dapboot/src; \
    make clean; \
    DEFS="$(BL_DEFS) -DAPP_BASE_ADDRESS=$(BL_APP_BASE_ADDRESS)" make TARGET=BLUEPILL
ifeq ($(PROGRAMMER),STLINK)
	cd lib/dapboot/src; \
	make OOCD_INTERFACE=$(OOCD_INTERFACE) flash
endif
ifeq ($(PROGRAMMER),BMP)
	cd lib/dapboot/src; \
	arm-none-eabi-gdb -nx --batch \
        -ex 'target extended-remote $(BMP_PORT)' \
        -ex 'monitor swdp_scan' \
        -ex 'attach 1' \
        -ex 'load' \
        -ex 'compare-sections' \
        -ex 'kill' \
        dapboot.elf
endif
ifeq ($(PROGRAMMER),BOOTLOADER)
	$(error Bootloader cannot be flashed with bootloader)
endif

# Flash rules
flash: $(OUTFILES) | check
ifeq ($(PROGRAMMER),STLINK)
	openocd \
        -f $(OOCD_INTERFACE) \
        -c "transport select hla_swd" \
        -f $(OOCD_TARGET) \
        -c "program $(BUILDDIR)/$(PROJECT).elf verify reset exit"
endif
ifeq ($(PROGRAMMER),BMP)
	arm-none-eabi-gdb -nx --batch \
        -ex 'target extended-remote $(BMP_PORT)' \
        -ex 'monitor swdp_scan' \
        -ex 'attach 1' \
        -ex 'load' \
        -ex 'compare-sections' \
        -ex 'kill' \
        $(BUILDDIR)/$(PROJECT).elf
endif
ifeq ($(PROGRAMMER),BOOTLOADER)
	dfu-util -d 1209:db42 -D $(BUILDDIR)/$(PROJECT).bin
endif

# Erase rules
erase: | check
ifeq ($(PROGRAMMER),STLINK)
	openocd \
        -f $(OOCD_INTERFACE) \
        -c "transport select hla_swd" \
        -f $(OOCD_TARGET) \
        -c "init" -c "reset init" \
        -c "stm32f1x unlock 0; reset halt" \
        -c "flash erase_sector 0 0 last" \
        -c "reset" \
        -c "shutdown"
endif
ifeq ($(PROGRAMMER),BMP)
	arm-none-eabi-gdb -nx --batch \
        -ex 'target extended-remote $(BMP_PORT)' \
        -ex 'monitor swdp_scan' \
        -ex 'attach 1' \
        -ex 'monitor erase_mass'
endif
ifeq ($(PROGRAMMER),BOOTLOADER)
	$(error Erase not supported using bootloader)
endif

# GDB Rules
gdb: | check
ifeq ($(PROGRAMMER),STLINK)
	openocd -f $(OOCD_INTERFACE) -c "transport select hla_swd" -f $(OOCD_TARGET)
endif
ifeq ($(PROGRAMMER),BMP)
	arm-none-eabi-gdb \
        -ex "target extended-remote $(BMP_PORT)" -ex "monitor swdp_scan" -ex "attach 1" \
        -ex "set mem inaccessible-by-default off" $(BUILDDIR)/$(PROJECT).elf
endif
ifeq ($(PROGRAMMER),BOOTLOADER)
	$(error GDB is not supported using bootloader)
endif
