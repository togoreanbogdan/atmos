
#
# ATMOS Makefile
# C 2008 Davor Ocelic, docelic@spinlocksolutions.com
# http://techpubs.spinlocksolutions.com/atmos/
#

# Smartcard chip name on your card, as recognized by avr libc
#ARCH=at90s2323
#ARCH=at90s8515
#ARCH=at90s8535
#ARCH=atmega161
ARCH=atmega163

# Your programmer device (as required by programmer software)
PROG=stk500v1
PORT=/dev/ttyS0

# Size of the external EEPROM on the smartcard. Atmel's sizes are
# usually in kilobits (i.e. AT90(256) and 24C256 are both 32 KByte).
# Here we set it in kilobytes, so divide by 8.
# 00: none, 01: 16KB, 02: 32KB, 03: 64KB, 04: 128KB,
# 05: 256KB, 06: 512KB, 07: 1024KB, 08: 2048KB, FF: unspec.,
EXT_EEPROM_SIZE=0x02

# The usual compile options
CC=avr-gcc -mmcu=$(ARCH) -DEXT_EEPROM_SIZE=$(EXT_EEPROM_SIZE)
AS=avr-as
OBJCOPY=avr-objcopy
SIZE=avr-size

CFLAGS=-Wall -I. -Os -mcall-prologues
ASFLAGS=-Wall -I.

CSRC= \
	aes.c \
	auth.c \
	commands.c \
	fs.c \
	fstream.c \
	hal.c \
	log.c \
	main.c \
	newdes-sk.c \
	skipjack.c \
	sw.c \
	t0.c \
	tools.c \
	transaction.c

SSRC= \
	eepromi2c.S \
	io.S \
	tea-$(ARCH).S

OBJ=$(CSRC:.c=.o) $(SSRC:.S=.o)

SLOCFILES = auth.c auth.h commands.c commands.h config.h eepromi2c.S sw.c \
	sw.h fs.c fs.h fstream.c fstream.h hal.c hal.h io.S main.c main.h t0.c \
	t0.h tea-$(ARCH).S tea.h tools.c tools.h transaction.c transaction.h \
	types.h newdes-sk.c newdes-sk.h skipjack.c skipjack.h aes.c aes.h

CALLTREEFILES = auth.c commands.c sw.c fs.c fstream.c hal.c main.c t0.c \
	tea.c tools.c transaction.c newdes-sk.c skipjack.c aes.c

all: atmos eedata

atmos: $(OBJ)
	$(CC) $(CFLAGS) -Wl,-Map,atmos.map -o atmos $(OBJ)
	$(SIZE) atmos
	$(OBJCOPY) -O binary atmos atmos.bin
	$(OBJCOPY) -O ihex atmos atmos.hex

eedata:
	$(CC) $(ASFLAGS) -c -o eedata -DDAY=0x`date +%d` -DMONTH=0x`date +%m` -DYEAR=0x`date +%y` eedata.S
	$(OBJCOPY) -O binary eedata eedata.bin
	$(OBJCOPY) -O ihex eedata eedata.hex

sloc:
	@echo
	@echo Lines of code
	@sloccount $(SLOCFILES) | grep -A 1000 "SLOC-by-Language" | grep -v "^$$"

calltree:
	@echo
	@echo Calltree
	@/opt/schily/bin/calltree -m -I. -I/opt/avrgcc/avr/include/ -D__AVR_AT90S8515__ $(CALLTREEFILES)

calldepth:
	@echo
	@echo Calldepth
	@/opt/schily/bin/calltree -m -I. -I/opt/avrgcc/avr/include/ -D__AVR_AT90S8515__ $(CALLTREEFILES) | sed -e "s/[^ ].*$$//" -e "s/    /#/g" -e "s/#/1/" -e "s/#/2/" -e "s/#/3/" -e "s/#/4/" -e "s/#/5/" -e "s/#/6/" -e "s/#/7/" -e "s/#/8/" -e "s/#/9/" -e "s/#/0/" | sort | tail -1

uncalled:
	@echo
	@echo Uncalled
	@/opt/schily/bin/calltree -u -I. -I/opt/avrgcc/avr/include/ -D__AVR_AT90S8515__ $(CALLTREEFILES)

statistics: sloc calldepth uncalled

clean: clean-atmos clean-eedata
	rm -rf core
	make -f Makefile.emu clean
	make -f Makefile.ctapi clean

clean-atmos:
	rm -rf $(OBJ) atmos atmos.bin atmos.hex atmos.map

clean-eedata:
	rm -rf eedata eedata.bin eedata.hex eedata.lst

#
# Writing and verifying data
#
.PHONY: write write-eeprom write-flash verify verify-eeprom verify-flash

write: write-eeprom write-flash

verify: verify-eeprom verify-flash

write-eeprom:
	avrdude -p $(ARCH) -c $(PROG) -P $(PORT) -U eeprom:w:eedata.hex:i

verify-eeprom:
	avrdude -p $(ARCH) -c $(PROG) -P $(PORT) -U eeprom:v:eedata.hex:i

write-flash:
	avrdude -p $(ARCH) -c $(PROG) -D -P $(PORT) -U flash:w:sosse.hex:i

verify-flash:
	avrdude -p $(ARCH) -c $(PROG) -P $(PORT) -U flash:v:sosse.hex:i

erase:
	avrdude -p $(ARCH) -c $(PROG) -P $(PORT) -e

