/* -------------------------------------------------------------------------
  FILE        : memtest.c
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Todd Fischer
  DESC        : Memory test that runs in UBL
 --------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// Project specific debug functionality
#include "debug.h"

#define TEST_VALUE   0x5a5a5a5aL

static inline void stop_test(void)
{
	DEBUG_printString("\r\nToo many DDR test failures, stopping\r\n");
	do {

	} while (1);
}

static inline void memory_test_failed(char *msg, Uint32 memory_address,
				      Uint32 expected_value, 
				      Uint32 actual_value)
{
	DEBUG_printString("\r\nERROR: ");
	DEBUG_printString(msg);
	DEBUG_printString(" -- address: 0x");
	DEBUG_printHexInt(memory_address);
	DEBUG_printString(", expected: 0x");
	DEBUG_printHexInt(expected_value);
	DEBUG_printString(", actual: 0x");
	DEBUG_printHexInt(actual_value);
}

static inline void write_test(Uint32 *memory_base, Uint32 memory_size)
{
	volatile Uint32 *ptr  = memory_base;
	Uint32 *pend = memory_base + ( memory_size / 4 );
	Uint32  value;
	Uint8 error_count = 0;

	DEBUG_printString("\r\nDDR write test started\r\n");
	for (; ptr < pend; ptr++) {
		/* Determine the test value and write it to memory */

		value = ((Uint32)ptr) ^ TEST_VALUE;
		*ptr = value;

		/* Read the test value and verify that it successful
		 * write to a memory location (but not necessary the
		 * correct memory location -- addressing aliasing
		 * failures will be caught in the re-read test.
		 */

		if (value != *ptr) {
			memory_test_failed("Write memory test failed",
					   (Uint32)ptr, value, *ptr);
			if (error_count++ >= 10) {
				stop_test();
			}
		}
	}
	if(!error_count)
		DEBUG_printString("DDR write test succeeded!!\r\n");
}


static inline void reread_test(Uint32 *memory_base, Uint32 memory_size)
{
	volatile Uint32 *ptr  = memory_base;
	Uint32 *pend = memory_base + ( memory_size / 4 );
	Uint32  value;
	Uint8 error_count = 0;

	DEBUG_printString("\r\nDDR read test started\r\n");
	for (; ptr < pend; ptr++) {
		/* Determine the test value */

		value = ((Uint32)ptr) ^ TEST_VALUE;

		/* Read the test value and verify that it contains
		 * the expected value.  This would not be the case if there
		 * were an address aliasing error that was not caught
		 * by the basic write test.
		 */

		if (value != *ptr) {
			memory_test_failed("Read back memory test failed",
					   (Uint32)ptr, value, *ptr);
			if (error_count++ >= 10) {
				stop_test();
			}
		}
	}
	if(!error_count)
		DEBUG_printString("DDR read test succeeded!!\r\n");
}

/**************************************************************************
 * Public Functions
 **************************************************************************/

void memory_test(Uint32 *memory_base, Uint32 memory_size)
{
	write_test(memory_base, memory_size);
	reread_test(memory_base, memory_size);
}
