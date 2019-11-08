
all: kernel.bin

kernel_head.o:
	as -32 kernel.S -o kernel_head.o
kernel.o: kernel_head.o
	gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -fno-pie -O0 -Wall -Wextra -m32
kernel.bin: kernel.o
	gcc -T kernel.ld -o kernel.bin -ffreestanding -fno-pie -O0 -nostdlib kernel_head.o kernel.o -lgcc -m32
debug: kernel.bin
	objdump -lSdx kernel.bin > kernel.lst
run: kernel.bin
	qemu-system-i386 -kernel kernel.bin
clean:
	rm *.o *.bin *.lst

