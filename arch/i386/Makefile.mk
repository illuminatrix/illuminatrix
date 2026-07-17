ARCH_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ARCH_OBJS += $(ARCH_DIR)isrs.o
ARCH_OBJS += $(ARCH_DIR)interrupts.o
ARCH_OBJS += $(ARCH_DIR)mm.o
ARCH_OBJS += $(ARCH_DIR)pio.o

INCLUDE_DIRS += -I$(ARCH_DIR)

include $(ARCH_DIR)boot/Makefile.$(BOOT).mk

OBJS += $(ARCH_OBJS)

kernel.bin: $(OBJS)
	@echo "LD $^    ->    $@"
	$(LD) -T $(ARCH_DIR)kernel.ld -melf_i386 -o $@ $^
