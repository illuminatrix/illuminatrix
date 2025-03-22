#
#
CC := gcc
AS := as
LD := ld
OBJDUMP := /usr/bin/objdump
CFLAGS := -g -std=gnu11 -nostdlib -ffreestanding -fno-pie -O0 -Wextra -m32 -Ilibc/include
ASFLAGS := -32
OBJS := kernel_head.o isrs.o syscall.o interrupts.o kernel.o mm.o pic.o irq.o
QEMU_CMD := qemu-system-i386 -kernel kernel.bin -display curses -serial mon:stdio


%.o: %.S
	@echo "AS $^    ->     $@"
	@$(AS) $(ASFLAGS) -c -o $@ $^

%.o: %.c
	@echo "CC $^    ->    $@"
	@$(CC) $(CFLAGS) -c -o $@ $^

kernel.bin: $(OBJS)
	cd libc && make
	@echo "LD $^    ->    $@"
	$(LD) -T kernel.ld -melf_i386 -o $@ libc/stdio/*.o libc/string/*.o $^

debug: kernel.bin
	$(OBJDUMP) -lSdx kernel.bin > kernel.lst

run: kernel.bin
	$(QEMU_CMD)

run-debug: kernel.bin
	$(QEMU_CMD) -S -s

gdb:
	gdb -ix gdb_script.gdb

.PHONY: clean
clean:
	cd libc && make clean
	rm -f *.o *.bin *.lst
