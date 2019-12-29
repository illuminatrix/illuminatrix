#
#
CC := /usr/bin/gcc
AS := /usr/bin/as
LD := /usr/bin/ld
OBJDUMP := /usr/bin/objdump
CFLAGS := -g -std=gnu99 -nostdlib -ffreestanding -fno-pie -O0 -Wextra -m32
ASFLAGS := -32
OBJS := kernel_head.o isrs.o interrupts.o kernel.o mm.o


%.o: %.S
	@echo "AS $^    ->     $@"
	@$(AS) $(ASFLAGS) -c -o $@ $^

%.o: %.c
	@echo "CC $^    ->    $@"
	@$(CC) $(CFLAGS) -c -o $@ $^

kernel.bin: $(OBJS)
	@echo "LD $^    ->    $@"
	@$(LD) -T kernel.ld -melf_i386 -o $@ $^

debug: kernel.bin
	$(OBJDUMP) -lSdx kernel.bin > kernel.lst

run: kernel.bin
	qemu-system-i386 -kernel kernel.bin

.PHONY: clean
clean:
	rm -f *.o *.bin *.lst
