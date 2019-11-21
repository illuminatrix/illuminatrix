
all: kernel.bin

isrs.o:
	as -32 isrs.S -o isrs.o
mm.o:
	gcc -g -c mm.c -o mm.o -std=gnu99 -ffreestanding -fno-pie -O0 -Wextra -m32
interrupts.o: isrs.o
	gcc -g -c interrupts.c -o interrupts.o -std=gnu99 -ffreestanding -fno-pie -O0 -Wextra -m32
kernel_head.o:
	as -32 kernel.S -o kernel_head.o
kernel.o: kernel_head.o interrupts.o mm.o
	gcc -g -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -fno-pie -O0 -Wextra -m32
kernel.bin: kernel.o
	gcc -T kernel.ld -o kernel.bin -ffreestanding -fno-pie -O0 -nostdlib kernel_head.o kernel.o isrs.o interrupts.o mm.o -lgcc -m32
debug: kernel.bin
	objdump -lSdx kernel.bin > kernel.lst
run: kernel.bin
	qemu-system-i386 -kernel kernel.bin
clean:
	rm *.o *.bin *.lst

