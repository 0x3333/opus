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

FREERTOSINCDIR = $(FREERTOSDIR)/include $(FREERTOSDIR)/portable/GCC/ARM_CM3

# List all C Source Files
FREERTOSCSRC =  $(FREERTOSDIR)/portable/GCC/ARM_CM3/port.c
FREERTOSCSRC += $(FREERTOSDIR)/portable/MemMang/heap_4.c
FREERTOSCSRC += $(FREERTOSDIR)/croutine.c
FREERTOSCSRC += $(FREERTOSDIR)/event_groups.c
FREERTOSCSRC += $(FREERTOSDIR)/list.c
FREERTOSCSRC += $(FREERTOSDIR)/queue.c
FREERTOSCSRC += $(FREERTOSDIR)/stream_buffer.c
FREERTOSCSRC += $(FREERTOSDIR)/tasks.c
FREERTOSCSRC += $(FREERTOSDIR)/timers.c

ALLCSRC += $(FREERTOSCSRC)
ALLINC  += $(FREERTOSINCDIR)