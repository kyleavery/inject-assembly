CC_X64  := x86_64-w64-mingw32-gcc

CFLAGS  := $(CFLAGS) -Os -fno-asynchronous-unwind-tables -nostdlib 
CFLAGS  := $(CFLAGS) -fno-ident -fpack-struct=8 -falign-functions=1
CFLAGS 	:= $(CFLAGS) -s -ffunction-sections -falign-jumps=1
CFLAGS  := $(CFLAGS) -falign-labels=1 -fPIC -w
LFLAGS  := $(LFLAGS) -Wl,-s,--no-seh,--enable-stdcall-fixup,-Tsrc/LinkOrder.ld

all:
	@ nasm -f win64 src/asm/start.asm -o start.x64.o
	@ $(CC_X64) src/*.c start.x64.o -o injectassembly.x64.exe $(CFLAGS) -fno-exceptions $(LFLAGS)
	@ python3 scripts/extract.py -f injectassembly.x64.exe -o injectassembly.x64.bin
	@ nasm -f win64 src/bof/IAStart.asm -o IAStart.x64.o
	@ $(CC_X64) src/bof/IABOF.c -c -o IABOF.x64.o -Os -s -Qn
	@ x86_64-w64-mingw32-ld -r IABOF.x64.o IAStart.x64.o -o injectassembly.x64.o --enable-stdcall-fixup
	@ rm start.x64.o IABOF.x64.o IAStart.x64.o injectassembly.x64.bin injectassembly.x64.exe
