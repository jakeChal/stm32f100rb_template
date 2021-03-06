###############################################################################
#
#
#
#
#
###############################################################################

OBJS  = main.o 
OBJS += stm32f10x_init.o 
OBJS += stm32f10x_misc.o 

###############################################################################

# root directory
export ROOT=..

# compiler toolchain
export CC=arm-none-eabi-gcc
export LD=arm-none-eabi-gcc
export AR=arm-none-eabi-ar
export AS=arm-none-eabi-as
export OBJCOPY=arm-none-eabi-objcopy
export GDB=arm-none-eabi-gdb

# default flags
export ASFLAGS=-g -mcpu=cortex-m3 -mthumb
export LDFLAGS=
export CFLAGS=-O1 -g -c -fno-common -mcpu=cortex-m3 -mthumb

# flash utils
STFLASH=st-flash
STUTIL=st-util
OPENOCD=openocd

# libtinyprintf
LDFLAGS += -L$(ROOT)/lib/tinyprintf
CFLAGS += -I$(ROOT)/lib/tinyprintf

# libstm32f10x
LDFLAGS += -L$(ROOT)/lib/stm32f10x
CFLAGS += -I$(ROOT)/lib/stm32f10x
CFLAGS += -I$(ROOT)/lib/stm32f10x/inc/core 
CFLAGS += -I$(ROOT)/lib/stm32f10x/inc/peripherals
CFLAGS += -DSTM32F10X_MD_VL=1 -DUSE_STDPERIPH_DRIVER=1

# liblcd
CFLAGS += -I$(ROOT)/lcd
LDFLAGS += -L$(ROOT)/lcd

# linker script and startup code
STARTUP = $(ROOT)/lib/stm32f10x/startup_stm32f10x_md_vl.s
LDFLAGS += -T$(ROOT)/lib/stm32f10x/stm32f100.ld

# additional compiler flags
CFLAGS += -std=c99 -pedantic -Wall -Wextra -Wshadow -Wcast-qual

.PHONY: flash gdb-server gdb-client clean

all: firmware.bin

firmware: $(OBJS)

firmware.elf: firmware libstm32f10x libtinyprintf liblcd
	$(LD) $(LDFLAGS) $(ASFLAGS) -o $@ $(OBJS) $(STARTUP) -llcd -lstm32f10x -ltinyprintf

firmware.bin: firmware.elf
	$(OBJCOPY) -O binary $< $@

# build libraries

libstm32f10x:
	$(MAKE) -C ../lib/stm32f10x libstm32f10x.a

libtinyprintf:
	$(MAKE) -C ../lib/tinyprintf libtinyprintf.a

liblcd:
	$(MAKE) -C ../lcd/ liblcd.a
# helper targets

# flash: firmware.bin
# 	$(STFLASH) write firmware.bin 0x8000000

flash: firmware.elf
	$(OPENOCD) -f $(ROOT)/openocd/stm32vldiscovery.cfg -c 'program firmware.elf verify reset exit'

gdb-server:
	$(STUTIL) --stlinkv1

gdb-client:
	$(GDB) --eval-command="target extended-remote :4242" firmware.elf

iterate:
	@echo "-------------------------------------------------------------------"
	make clean
	@echo "-------------------------------------------------------------------"
	make 
	@echo "-------------------------------------------------------------------"
	make flash
	@echo "-------------------------------------------------------------------"
	arm-none-eabi-size firmware.elf

clean:
	rm -f firmware.elf firmware.bin
	rm -f $(OBJS)

clean_all:
	$(MAKE) -C ../lib/stm32f10x clean
	$(MAKE) -C ../lib/tinyprintf clean
	rm -f firmware.elf firmware.bin
	rm -f $(OBJS)
