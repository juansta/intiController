#
#             LUFA Library
#     Copyright (C) Dean Camera, 2015.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Run "make help" for target help.

MCU          = atmega32u2
ARCH         = AVR8
BOARD        = USBKEY
F_CPU        = 8000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = intiController
SRC          = main.cpp src/i2cmaster.cpp src/timer.cpp src/rtc.cpp src/datetime.cpp src/eeprom.cpp src/settings.cpp src/dimmer.cpp src/led.cpp src/descriptors.cpp $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
LUFA_PATH    = /opt/lufa/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -Iinclude/ -IConfig/
## Compilation options, type man avr-gcc if you're curious.
CFLAGS      += -mmcu=$(MCU) -DF_USB=$(F_USB)UL -DF_CPU=$(F_CPU)UL -DBAUD=$(BAUD) -Os -I. -I./include -I./Config
CFLAGS      += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums 
CFLAGS      += -Wall
CFLAGS      += -g -ggdb
CFLAGS      += -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--relax
# CFLAGS      += -ffunction-sections --gc-sections
## CFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm  ## for floating-point printf
## CFLAGS += -Wl,-u,vfprintf -lprintf_min      ## for smaller printf
LD_FLAGS     =

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk

## Defined programs / locations
CC      = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude
AVRDFU  = dfu-programmer

flash: $(TARGET).hex
	sudo $(AVRDFU) $(MCU) erase
	sudo $(AVRDFU) $(MCU) flash $(BINDIR)/$(TARGET).hex

## An alias
program: flash
