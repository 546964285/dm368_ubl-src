/* --------------------------------------------------------------------------
  FILE        : dumpregs.c
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Todd Fischer
  DESC        : Helper routine to make it easy to dump registers to track
                various settings when optimizing hardware register
                configuration
 ----------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// Project specific debug functionality
#include "debug.h"

#define PLL1_BASE 0x01C40800
#define PLL2_BASE 0x01C40C00

struct reg_list {
	char *reg_name;
	Uint32 address;
};

const struct reg_list interesting_registers[] = {
	{ "DDR config   ", 0x20000008 },
	{ "DDR refresh  ", 0x2000000C },
	{ "DDR timing   ", 0x20000010 },
	{ "DDR timing2  ", 0x20000014 },
	{ "DDR phy contl", 0x200000E4 },
	{ "PLL1 CTL     ", PLL1_BASE + 0x100 },
	{ "PLL1 MUL     ", PLL1_BASE + 0x110 },
	{ "PLL1 DIV     ", PLL1_BASE + 0x114 },
	{ "PLL1 SCLK1   ", PLL1_BASE + 0x118 },
	{ "PLL1 SCLK2   ", PLL1_BASE + 0x11C },
	{ "PLL1 SCLK3   ", PLL1_BASE + 0x120 },
	{ "PLL2 CTL     ", PLL2_BASE + 0x100 },
	{ "PLL2 MUL     ", PLL2_BASE + 0x110 },
	{ "PLL2 DIV     ", PLL2_BASE + 0x114 },
	{ "PLL2 SCLK1   ", PLL2_BASE + 0x118 },
	{ "PLL2 SCLK2   ", PLL2_BASE + 0x11C },
	{ "PLL2 SCLK3   ", PLL2_BASE + 0x120 },
	/* Address value of zero marks end of array */
	{ "", 0 }
};


static inline void dump_reg(char *reg_name, Uint32 address)
{
	Uint32 *addr = (Uint32	*) address;
	DEBUG_printString(reg_name);
	DEBUG_printString("[0x");
	DEBUG_printHexInt(address);
	DEBUG_printString("]: ");
	DEBUG_printHexInt(*addr);
	DEBUG_printString("\r\n");
}

/**************************************************************************
 * Public Functions
 **************************************************************************/

void dump_registers(void)
{
	int i;

	for (i = 0; interesting_registers[i].address; i++) {
		dump_reg(interesting_registers[i].reg_name,
			 interesting_registers[i].address);
	}
}
