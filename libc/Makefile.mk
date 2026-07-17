LIBC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

LIBC_OBJS += $(LIBC_DIR)$(ARCH)/syscall.o

LIBC_OBJS += $(LIBC_DIR)stdio/printf.o
LIBC_OBJS += $(LIBC_DIR)stdio/vsprintf.o
LIBC_OBJS += $(LIBC_DIR)stdio/putchar.o
LIBC_OBJS += $(LIBC_DIR)string/memcpy.o
LIBC_OBJS += $(LIBC_DIR)string/memset.o

ifneq (,$(wildcard $(LIBC_DIR)$(ARCH)/string/memcmp.c))
LIBC_OBJS += $(LIBC_DIR)$(ARCH)/string/memcmp.o
else
LIBC_OBJS += $(LIBC_DIR)string/memcmp.o
endif

ifneq (,$(wildcard $(LIBC_DIR)$(ARCH)/string/memmove.c))
LIBC_OBJS += $(LIBC_DIR)$(ARCH)/string/memmove.o
else
LIBC_OBJS += $(LIBC_DIR)string/memmove.o
endif

ifneq (,$(wildcard $(LIBC_DIR)$(ARCH)/string/strlen.c))
LIBC_OBJS += $(LIBC_DIR)$(ARCH)/string/strlen.o
else
LIBC_OBJS += $(LIBC_DIR)string/strlen.o
endif

INCLUDE_DIRS += -I$(LIBC_DIR)

OBJS += $(LIBC_OBJS)
