CURRENT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

OBJS += $(CURRENT_DIR)multiboot_start.o
OBJS += $(CURRENT_DIR)multiboot.o
