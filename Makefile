#
#
CC := gcc
AS := as
LD := ld
ARCH := i386
BOOT := multiboot
OBJDUMP := /usr/bin/objdump
CFLAGS := -g -std=gnu11 -nostdlib -ffreestanding -fno-pie -O0 -Wextra -m32 -fno-stack-protector
ASFLAGS := -32
QEMU_CMD := qemu-system-i386 -kernel kernel.bin -display curses -serial mon:stdio
INCLUDE_DIRS :=
OBJS := 

include arch/$(ARCH)/Makefile.mk
include kernel/Makefile.mk
include libc/Makefile.mk

%.o: %.S
	@echo "AS $^    ->     $@"
	@$(AS) $(ASFLAGS) $(INCLUDE_DIRS) -c -o $@ $^

%.o: %.c
	@echo "CC $^    ->    $@"
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c -o $@ $^

kernel.bin: $(OBJS)
	@echo "LD $^    ->    $@"
	$(LD) -T arch/$(ARCH)/kernel.ld -melf_i386 -o $@ $^

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
	rm -f *.o $(OBJS) *.bin *.lst
