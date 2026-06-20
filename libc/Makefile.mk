CURRENT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

OBJS += $(CURRENT_DIR)$(ARCH)/syscall.o

OBJS += $(CURRENT_DIR)stdio/printf.o
OBJS += $(CURRENT_DIR)stdio/vsprintf.o
OBJS += $(CURRENT_DIR)stdio/putchar.o
OBJS += $(CURRENT_DIR)string/memcpy.o
OBJS += $(CURRENT_DIR)string/memset.o

ifneq (,$(wildcard $(CURRENT_DIR)$(ARCH)/string/memcmp.c))
OBJS += $(CURRENT_DIR)$(ARCH)/string/memcmp.o
else
OBJS += $(CURRENT_DIR)string/memcmp.o
endif

ifneq (,$(wildcard $(CURRENT_DIR)$(ARCH)/string/memmove.c))
OBJS += $(CURRENT_DIR)$(ARCH)/string/memmove.o
else
OBJS += $(CURRENT_DIR)string/memmove.o
endif

ifneq (,$(wildcard $(CURRENT_DIR)$(ARCH)/string/strlen.c))
OBJS += $(CURRENT_DIR)$(ARCH)/string/strlen.o
else
OBJS += $(CURRENT_DIR)string/strlen.o
endif

INCLUDE_DIRS += -I$(CURRENT_DIR)
