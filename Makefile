CC=gcc
LD=ld
NASM=nasm
CFLAGS= -Wextra -Wall -nostdinc -fno-builtin \
	-fno-leading-underscore -Isrc/include
LDFLAGS= -nostdlib  \
	 -section-alignment 0x1000 \
	 -file-alignment 0x1 --image-base 0x100000 \
	 -e kernel_init

all:
	mkdir -p bin/
	$(CC) -m32 -c ${CFLAGS} src/kernel.c -o bin/kernel.o
	$(CC) -m32 -c ${CFLAGS} src/syscalls/screen.c -o bin/screen.o
	$(CC) -m32 -c ${CFLAGS} src/syscalls/memory.c -o bin/memory.o
	$(CC) -m32 -c ${CFLAGS} src/cli.c -o bin/cli.o
	$(CC) -m32 -c ${CFLAGS} src/syscalls/keyboard.c -o bin/keyboard.o
	$(CC) -m32 -c ${CFLAGS} src/syscalls/pci.c -o bin/pci.o
	$(CC) -m32 -c ${CFLAGS} src/syscalls/pic.c -o bin/pic.o
	$(CC) -m32 -c ${CFLAGS} src/init/net.c -o bin/net.o
	$(CC) -m32 -c ${CFLAGS} src/init/descriptor_tables.c -o bin/descriptor_tables.o
	$(CC) -m32 -c ${CFLAGS} src/drivers/net/i8254x.c -o bin/i8254x.o
	$(NASM) -f elf32 src/asm/gdt_flush.s -o bin/gdt_flush.o
	$(NASM) -f elf32 src/asm/idt_flush.s -o bin/idt_flush.o
	$(NASM) -f elf32 src/asm/interrupt.s -o bin/interrupt.o
	$(LD) bin/*.o -o kernel.bin -Map kernel.map -m i386pe --cref ${LDFLAGS}
	$(NASM) Stage1PXE.asm
	$(NASM) Stage1FDD.asm
	$(NASM) Stage2.asm
	python build.py

clean:
	rm -rf bin/

run:
	#qemu-system-i386 -net nic,model=e1000 -net dump,file=/tmp/vm0.pcap -net user os_fdd.img
	sudo qemu-system-i386 -net nic -net bridge,br=br0 -net nic,model=e1000 -net dump,file=/tmp/vm0.pcap -net user os_fdd.img
