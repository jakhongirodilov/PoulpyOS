#
# MAKEFILE FOR POULPY-OS
#

# Set source dirs
ASM_SOURCES = $(wildcard boot/*.asm)
C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c bin/*.c util/*.c)

HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h bin/*.h)
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

#Set compiler
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb
CFLAGS = -Wall -g -std=c99 -ffreestanding -Iinclude -Iutil


#Set names
IMG=poulpyOS.img
ISO=poulpyOS.iso

all: poulpyOS

#Build rules 
poulpyOS: $(IMG)

$(IMG): bootMain.bin kernel.bin
	dd if=boot/bootMain.bin of=$(IMG) conv=notrunc bs=512 seek=0 count=1
	dd if=kernel.bin of=$(IMG) conv=notrunc bs=512 seek=1

iso: $(IMG)
	mkisofs -pad -b $(IMG) -R -o $(ISO) $(IMG)

bootMain.bin: boot/bootMain.bin
	cp boot/bootMain.bin bootMain.bin


kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ 

run: $(IMG)
	qemu-system-i386 -fda $(IMG)

img:	
	make $(IMG)

#Debug build rules
debug: $(BIN) kernel.elf
	qemu-system-i386 -s -fda $(BIN) &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.o *.bin *.img *.iso 
	rm -rf kernel/*.o bin/*.o cpu/*.o boot/*.bin drivers/*.o boot/*.o libc/*.o boot/*.bin
