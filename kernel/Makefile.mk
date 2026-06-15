CURRENT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

OBJS += $(CURRENT_DIR)/syscall.o
OBJS += $(CURRENT_DIR)/kernel.o
OBJS += $(CURRENT_DIR)/pic.o
OBJS += $(CURRENT_DIR)/irq.o

INCLUDE_DIRS += -I$(CURRENT_DIR)
