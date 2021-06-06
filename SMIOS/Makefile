CC=gcc
CFLAGS=-m32 -ffreestanding -c
LFLAGS=-m elf_i386 -T
AS=nasm
ASFLAGS=-f elf32
kernel.bin: main.o boot.o gdt.o idt.o isrs.o irq.o kb.o linker.ld
	ld $(LFLAGS) linker.ld -o SMIOS/boot/kernel.bin objects/boot.o  objects/main.o objects/gdt.o objects/idt.o objects/isrs.o objects/irq.o objects/kb.o
main.o :
	$(CC) $(CFLAGS)  Kernel/main.c -I include/ -o objects/main.o 
gdt.o :
	$(CC) $(CFLAGS)  Kernel/gdt.c -I include/ -o objects/gdt.o 
kb.o :
	$(CC) $(CFLAGS)  Kernel/kb.c -I include/ -o objects/kb.o 
idt.o :
	$(CC) $(CFLAGS)  Kernel/idt.c -I include/ -o objects/idt.o 
isrs.o :
	$(CC) $(CFLAGS)  Kernel/isrs.c -I include/ -o objects/isrs.o 
irq.o :
	$(CC) $(CFLAGS)  Kernel/irq.c -I include/ -o objects/irq.o 	
boot.o :
	$(AS) $(ASFLAGS) Boot/boot.s -o objects/boot.o

