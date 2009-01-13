
#
# ATMOS Makefile
# C 2008 Davor Ocelic, docelic@spinlocksolutions.com
#

# Your programmer device (for uisp -dprog=)
BOARD=stk500
PORT=/dev/ttyS0

# Your smartcard chip (both for chip-specific
# compilation and for uisp -dpart=)
#ARCH=at90s2323
#ARCH=at90s8515
#ARCH=at90s8535
ARCH=atmega161

# The usual compile options
CC=avr-gcc -mmcu=$(ARCH)
AS=avr-as
OBJCOPY=avr-objcopy
SIZE=avr-size

CFLAGS=-Wall -I. -Os -mcall-prologues
ASFLAGS=-Wall -I.

CSRC= \
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
	types.h newdes-sk.c newdes-sk.h skipjack.c skipjack.h

CALLTREEFILES = auth.c commands.c sw.c fs.c fstream.c hal.c main.c t0.c \
	tea.c tools.c transaction.c newdes-sk.c skipjack.c

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
	uisp -dprog=$(BOARD) -dpart=$(ARCH) -dserial=$(PORT) \
		--erase --segment=eeprom
	sleep 2
	uisp -dprog=$(BOARD) -dpart=$(ARCH) -dserial=$(PORT) \
		--upload --segment=eeprom if=eedata.hex
verify-eeprom:
	uisp -dprog=$(BOARD) -dpart=$(ARCH) -dserial=$(PORT) \
		--verify --segment=eeprom if=eedata.hex
write-flash:
	uisp -dprog=$(BOARD) -dpart=$(ARCH) -dserial=$(PORT) \
		--erase --segment=flash
	sleep 2
	uisp -dprog=$(BOARD) -dpart=$(ARCH) -dserial=$(PORT) \
		--upload --segment=flash if=atmos.hex
verify-flash:
	uisp -dprog=$(BOARD) -dpart=$(ARCH) -dserial=$(PORT) \
		--verify --segment=flash if=atmos.hex

