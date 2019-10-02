all: file.img

boot: boot.S
	gcc -c  -g boot.S -o boot.o
	ld --oformat binary -o boot -T boot.ld boot.o

kernel: kernel.c
	gcc -c -ffreestanding -fno-PIE kernel.c -o kernel.o
	ld --oformat binary -o kernel -Ttext 0x10000 kernel.o

file.img: boot kernel
	cat boot kernel > file.img

run: file.img
	qemu-system-i386 -hda file.img

clean:
	rm boot boot.o kernel.o kernel file.img file.elf file.lst

debug: boot.o
	ld -o file.elf -T boot.ld boot.o; objdump -lS file.elf > file.lst

