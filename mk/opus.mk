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

OPUSINCDIR = $(OPUSDIR)/inc $(OPUSDIR)/inc/driver
OPUSSRCDIR = $(OPUSDIR)/src

# List all C Source Files
OPUSCSRC =  $(OPUSSRCDIR)/opus.c
OPUSCSRC += $(OPUSSRCDIR)/driver/serial.c
OPUSCSRC += $(OPUSSRCDIR)/driver/softserial.c
OPUSCSRC += $(OPUSSRCDIR)/driver/usbcdc.c
OPUSCSRC += $(OPUSSRCDIR)/driver/mfs.c