#############################################################
# Makefile for TI UBL project.                              #
#   Generates the binary UBL file can be used as the        #
#   secondary bootloader for the DM35x in NOR, NAND, and   #
#   UART boot modes.                                        #
#############################################################
# Author:   Daniel Allred
#

#Include the device specific make
include ../device.mak

PROGRAM:=ubl

CROSSCOMPILE?=arm-none-linux-gnueabi-
CC=$(CROSSCOMPILE)gcc
OBJCOPY=$(CROSSCOMPILE)objcopy
OBJDUMP=$(CROSSCOMPILE)objdump
LDFLAGS=-Wl,-T$(LINKERSCRIPT) -nostdlib -Wl,-Map,$@.map
OBJCOPYFLAGS = --gap-fill 0xFF -S
SOURCES=$(PROGRAM).c boot.c selfcopy.c uartboot.c device.c debug.c uart.c util.c 
ASSEMBLY=../../../../Common/arch/arm926ejs/_udivsi3.S ../../../../Common/arch/arm926ejs/_divsi3.S
ENTRYPOINT=boot

CFLAGS:=-DPLL_SETTING_$(PLL_SETTING) -c -Os -Wall -ffreestanding -I../../../Common/include -I../../../../Common/include -I../../../../Common/arch/arm926ejs/include -I../../../../Common/$(PROGRAM)/include -I../../../../Common/drivers/include -I../../../../Common/gnu/include 
ifeq ($(TYPE),nand)
	CFLAGS+= -DUBL_NAND
  SOURCES+= nand.c nandboot.c device_nand.c
endif
ifeq ($(TYPE),nor)
  CFLAGS+= -DUBL_NOR
  SOURCES+= nor.c norboot.c 
endif
ifeq ($(TYPE),sdmmc)
	CFLAGS+= -DUBL_SDMMC
  SOURCES+= sdmmc.c sdmmcboot.c
endif

OBJECTS1:=$(patsubst %.c,%_$(DEVSTRING)_$(PLL_SETTING)_$(TYPE).o,$(SOURCES))
OBJECTS=$(OBJECTS1) $(ASSEMBLY)

ifneq ($(TEST_MEMORY),)
  CFLAGS+= -DSDRAM_BASE=$(SDRAM_BASE) -DSDRAM_SIZE=$(SDRAM_SIZE) -DTEST_MEMORY=$(TEST_MEMORY)
  OBJECTS+=memtest.o
endif

ifneq ($(PRINT_CONFIGURATION),)
  OBJECTS+= dumpregs.o
  CFLAGS+= -DPRINT_CONFIGURATION=$(PRINT_CONFIGURATION)
endif

EXECUTABLE:=$(PROGRAM)_$(DEVSTRING)_$(PLL_SETTING)_$(TYPE)
BINARY:=../$(EXECUTABLE).bin
LINKERSCRIPT=../$(PROGRAM).lds

# Target definitions
all: $(BINARY) $(OBJECTS)

.PHONY : clean objclean
clean:
		-rm -f -v $(OBJECTS1) $(BINARY) $(EXECUTABLE)
		
objclean:
		-rm -f -v $(OBJECTS1)
		
$(BINARY): $(EXECUTABLE)
		$(OBJCOPY) $(OBJCOPYFLAGS) -O binary $< $@
		@echo -n "The entry point of the binary is 0x"
		@$(OBJDUMP) -t $< | grep -E '[0-9a-f]{8}*[0-9a-f]{8} $(ENTRYPOINT)' | sed  's/^\([0-9a-f]\{4\}\)\([0-9a-f]\{4\}\).*/\2/'

$(EXECUTABLE): $(OBJECTS) $(LINKERSCRIPT)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@
		
%_$(DEVSTRING)_$(PLL_SETTING)_$(TYPE).o : %.c
		$(CC) $(CFLAGS) $< -o $@      
        
# Search paths for code and header files
vpath %.h :../../../Common/include:../../../../Common/include:../../../../Common/arch/arm926ejs/include:../../../../Common/$(PROGRAM)/include:../../../../Common/gnu/include:../../../../Common/drivers/include
vpath %.c ../../../Common/src:../../../../Common/src:../../../../Common/arch/arm926ejs/src:../../../../Common/$(PROGRAM)/src:../../../../Common/gnu/src:../../../../Common/drivers/src
vpath %.S ../../../../Common/arch/arm926ejs/
