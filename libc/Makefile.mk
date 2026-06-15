CURRENT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

OBJS += $(CURRENT_DIR)stdio/printf.o
OBJS += $(CURRENT_DIR)stdio/vsprintf.o
OBJS += $(CURRENT_DIR)stdio/putchar.o
OBJS += $(CURRENT_DIR)string/memcmp.o
OBJS += $(CURRENT_DIR)string/memcpy.o
OBJS += $(CURRENT_DIR)string/memmove.o
OBJS += $(CURRENT_DIR)string/memset.o
OBJS += $(CURRENT_DIR)string/strlen.o

INCLUDE_DIRS += -I$(CURRENT_DIR)
