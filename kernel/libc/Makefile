CFLAGS := -g -std=gnu11 -nostdlib -ffreestanding -fno-pie -O0 -Wextra -m32 -fno-stack-protector
FREEOBJS:=\
stdio/printf.o \
stdio/vsprintf.o \
stdio/putchar.o \
string/memcmp.o \
string/memcpy.o \
string/memmove.o \
string/memset.o \
string/strlen.o \

OBJS:=\
$(FREEOBJS) \


.PHONY: all clean

all: $(OBJS)

%.o: %.c
	$(CC) -Iinclude -I../include -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(BINARIES) $(OBJS) *.o */*.o */*/*.o
