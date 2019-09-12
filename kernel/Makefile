
all: kernel.bin

kernel_head.o:
	as -32 kernel.S -o kernel_head.o
kernel.o: kernel_head.o
	gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
kernel.bin: kernel.o
	gcc -T kernel.ld -o kernel.bin -ffreestanding -O2 -nostdlib kernel_head.o kernel.o -lgcc -m32

run: kernel.bin
	qemu-system-i386 -kernel kernel.bin
clean:
	rm kernel.o kernel.bin kernel_head.o

