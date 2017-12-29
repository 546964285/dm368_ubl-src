UBL need to be modified to fit your board, this doc focus on how to compile ubl.

1. source toolchain is a must
$ source set_env.sh


2. build all targets once
$ make -C ti-flash-utils/DM36x/GNU/ubl/ clean
$ make -C ti-flash-utils/DM36x/GNU/ubl/

3. build specified target for saving time
$ make -C ti-flash-utils/DM36x/GNU/ubl/build/ TYPE=sdmmc clean
$ make -C ti-flash-utils/DM36x/GNU/ubl/build/ TYPE=nand clean
$ make -C ti-flash-utils/DM36x/GNU/ubl/build/ TYPE=nor clean

$ make -C ti-flash-utils/DM36x/GNU/ubl/build/ TYPE=sdmmc SDRAM_BASE=0x80000000 SDRAM_SIZE=0x08000000 PLL_SETTING=ARM297_DDR270_OSC24
$ make -C ti-flash-utils/DM36x/GNU/ubl/build/ TYPE=nand SDRAM_BASE=0x80000000 SDRAM_SIZE=0x08000000 PLL_SETTING=ARM297_DDR270_OSC24
$ make -C ti-flash-utils/DM36x/GNU/ubl/build/ TYPE=nor SDRAM_BASE=0x80000000 SDRAM_SIZE=0x08000000 PLL_SETTING=ARM297_DDR270_OSC24

available PLL_SETTINGs are here, you can add more settings based on your code in ti-flash-utils/DM36x/Common/src/device.c
ARM297_DDR270_OSC24
ARM270_DDR216_OSC24
ARM297_DDR277_OSC27
ARM216_DDR173_OSC19P2
ARM216_DDR173_OSC24
ARM432_DDR340_OSC24
ARM297_DDR243_OSC24
ARM445_DDR351_OSC24


=======================================================================================================
history

2017-12-21
dsc: goto ti-flash-utils/DM36x/GNU/ubl/ and make, then generates all images for all available PLL settings
mod: ti-flash-utils/DM36x/GNU/ubl/build/makefile
mod: ti-flash-utils/DM36x/GNU/ubl/makefile
add: ti-flash-utils/DM36x/GNU/ubl/device.mak
-----------------------------------------------------
2017-12-08
dsc: avoid udivsi3 err after clean
mod: ti-flash-utils/DM36x/GNU/ubl/build/makefile



