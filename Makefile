OBJDIR = obj
BINDIR = bin
MCU    = atmega32u2
F_CPU  = 8000000
BAUD   = 38400

## This is where main() lives
MAIN = main.cpp

## include the additional .c source (in same directory) here
## (and include the .h files in your foo.c)
LOCAL_SOURCE =

## Here you can link to one more directory (and multiple .c files)
# EXTRA_SOURCE_DIR = ../AVR-Programming-Library/
# EXTRA_SOURCE_FILES = USART.c
EXTRA_SOURCE_DIR   = ./src/
EXTRA_SOURCE_FILES = lcd.cpp  rotary.cpp  ST7036.cpp
EXTRA_INCLUDE_DIR = ./include/

# List Assembler source files here.
# # Make them always end in a capital .S.  Files ending in a lowercase .s
# # will not be considered source files but generated files (assembler
# # output from the compiler), and will be deleted upon "make clean"!
# # Even though the DOS/Win* filesystem matches both .s and .S the same,
# # it will preserve the spelling of the filenames, and gcc itself does
# # care about how the name is spelled on its command-line.
ASRC =

## Defined programs / locations
CC      = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude
AVRDFU  = dfu-programmer

## Compilation options, type man avr-gcc if you're curious.
CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU)UL -DBAUD=$(BAUD) -Os -I. -I$(EXTRA_INCLUDE_DIR)
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -Wall
CFLAGS += -g -ggdb
CFLAGS += -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--relax
CFLAGS += -std=c++11
## CFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm  ## for floating-point printf
## CFLAGS += -Wl,-u,vfprintf -lprintf_min      ## for smaller printf

# Optional assembler flags.
# #  -Wa,...:   tell GCC to pass this to the assembler.
# #  -ahlms:    create listing
# #  -gstabs:   have the assembler create line number information; note that
# #             for use in COFF files, additional information about filenames
# #             and function names needs to be present in the assembler source
# #             files -- see avr-libc docs [FIXME: not yet described there]
ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs

## Lump target and extra source files together
TARGET = $(strip $(basename $(MAIN)))
SRC    = $(TARGET).cpp
EXTRA_SOURCE = $(addprefix $(EXTRA_SOURCE_DIR), $(EXTRA_SOURCE_FILES))
SRC += $(EXTRA_SOURCE)
SRC += $(LOCAL_SOURCE)

## List of all header files
HEADERS = $(SRC:.cpp=.h)

## For every .c file, compile an .o object file
OBJ = $(SRC:.cpp=.o) $(ASRC:.S=.o)

# Define all listing files.
LST = $(ASRC:.S=.lst) $(SRC:.c=.lst)

## Generic Makefile targets.  (Only .hex file is necessary)
all: $(TARGET).hex

%.hex:%.elf
	$(OBJCOPY) -R .eeprom -O ihex $(OBJDIR)/$< $(BINDIR)/$@

%.elf: $(SRC)
	$(CC) $(CFLAGS) $(SRC) --output $(OBJDIR)/$@

%.eeprom: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $(OBJDIR)/$< $(BINDIR)/$@

debug:
	@echo
	@echo "Source files:"   $(SRC)
	@echo "MCU, F_CPU, BAUD:"  $(MCU), $(F_CPU), $(BAUD)
	@echo

# Optionally create listing file from .elf
# This creates approximate assembly-language equivalent of your code.
# Useful for debugging time-sensitive bits,
# or making sure the compiler does what you want.
disassemble: $(TARGET).lst

disasm: disassemble

eeprom: $(TARGET).eeprom

%.lst: %.elf
	$(OBJDUMP) -S $(OBJDIR)$< > $@

# Optionally show how big the resulting program is
size:  $(TARGET).elf
	$(AVRSIZE) -C --mcu=$(MCU) $(TARGET).elf

clean:
	rm -f $(OBJDIR)/$(TARGET).elf $(BINDIR)/$(TARGET).hex $(OBJDIR)/$(TARGET).obj \
	$(OBJDIR)/$(TARGET).o $(TARGET).d $(TARGET).eep $(TARGET).lst \
	$(TARGET).lss $(TARGET).sym $(TARGET).map $(TARGET)~ \
	$(BINDIR)/$(TARGET).eeprom

squeaky_clean:
	rm -f *.elf *.hex *.obj *.o *.d *.eep *.lst *.lss *.sym *.map *~

flash: $(TARGET).hex
	sudo $(AVRDFU) $(MCU) erase
	sudo $(AVRDFU) $(MCU) flash $(BINDIR)/$(TARGET).hex

## An alias
program: flash

flash_eeprom: $(TARGET).eeprom
	sudo $(AVRDFU) $(MCU) erase
	sudo $(AVRDFU) $(MCU) eeprom-flash $(BINDIR)/$(TARGET).hex

##########------------------------------------------------------##########
##########       Fuse settings and suitable defaults            ##########
##########------------------------------------------------------##########

## Mega 48, 88, 168, 328 default values
LFUSE = 0x62
HFUSE = 0xdf
EFUSE = 0x00

## Generic
FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m

fuses:
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) \
	           $(PROGRAMMER_ARGS) $(FUSE_STRING)
show_fuses:
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -nv

## Called with no extra definitions, sets to defaults
set_default_fuses:  FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m
set_default_fuses:  fuses

## Set the fuse byte for full-speed mode
## Note: can also be set in firmware for modern chips
set_fast_fuse: LFUSE = 0xE2
set_fast_fuse: FUSE_STRING = -U lfuse:w:$(LFUSE):m
set_fast_fuse: fuses

## Set the EESAVE fuse byte to preserve EEPROM across flashes
set_eeprom_save_fuse: HFUSE = 0xD7
set_eeprom_save_fuse: FUSE_STRING = -U hfuse:w:$(HFUSE):m
set_eeprom_save_fuse: fuses

## Clear the EESAVE fuse byte
clear_eeprom_save_fuse: FUSE_STRING = -U hfuse:w:$(HFUSE):m
clear_eeprom_save_fuse: fuses
