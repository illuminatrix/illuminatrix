CURRENT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

OBJS += $(CURRENT_DIR)isrs.o
OBJS += $(CURRENT_DIR)interrupts.o
OBJS += $(CURRENT_DIR)mm.o
OBJS += $(CURRENT_DIR)pio.o

INCLUDE_DIRS += -I$(CURRENT_DIR)

include $(CURRENT_DIR)boot/Makefile.$(BOOT).mk
