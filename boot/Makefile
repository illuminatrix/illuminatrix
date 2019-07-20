

all: file.img

boot.o:
	gcc -c  -g boot.S -o boot.o
file.img: boot.o
	ld --oformat binary -o file.img -T boot.ld boot.o
run: file.img
	qemu-system-i386 -hda file.img
clean:
	rm boot.o file.img
