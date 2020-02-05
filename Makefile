
##########------------------------------------------------------##########
##########              Config                                  ##########
##########------------------------------------------------------##########

MCU   ?= atmega328p
F_CPU ?= 1000000UL   # 1MHz
BAUD  ?= 9600UL
PROGRAMMER_TYPE ?= usbasp
PROGRAMMER_ARGS ?=

##########------------------------------------------------------##########

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude

##########------------------------------------------------------##########

TARGET = TM1637

SOURCES=$(wildcard src/*.c example/*.c)
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(SOURCES:.c=.h)

## Compilation options
CPPFLAGS = -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -I.
CFLAGS = -Os -g -std=gnu99 -Wall
## Use short (8-bit) data types
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
## Splits up object files per function
CFLAGS += -ffunction-sections -fdata-sections
LDFLAGS = -Wl,-Map,$(TARGET).map
## Optional, but often ends up with smaller code
LDFLAGS += -Wl,--gc-sections
TARGET_ARCH = -mmcu=$(MCU)


## Explicit pattern rules
%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c -o $@ $<;

$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.lst: %.elf
	$(OBJDUMP) -S $< > $@



.PHONY: all debug disassemble flash size erase clean

all: $(TARGET).hex

debug:
	@echo
	@echo "Source files:"  $(SOURCES)
	@echo "MCU:" $(MCU) "F_CPU:" $(F_CPU) "BAUD:" $(BAUD)
	@echo

# Optionally create listing file from .elf
# This creates approximate assembly-language equivalent of your code.
# Useful for debugging time-sensitive bits, or making sure the compiler does what you want.
disassemble: $(TARGET).lst

flash: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U flash:w:$<

# Show how big the resulting program is
size:  $(TARGET).elf
	$(AVRSIZE) -C --mcu=$(MCU) $(TARGET).elf

# Erase the AVR chip
erase:
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -e

clean:
	rm -f *.elf *.hex *.obj *.o *.d *.eep *.lst \
	      *.sym *.map $(TARGET).eeprom \
				$(OBJECTS)