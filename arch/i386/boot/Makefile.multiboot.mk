CURRENT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

OBJS += $(CURRENT_DIR)start.o
OBJS += $(CURRENT_DIR)early_kernel.o
