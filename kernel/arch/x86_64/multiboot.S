 .code32

.set MAGIC,	0xe85250d6
.set MULTIBOOT_ARCH, 0
.set HEADER_LENGTH, (header_end - header_start)
.set CHECKSUM,	- (MAGIC + MULTIBOOT_ARCH + HEADER_LENGTH)
.set MULTIBOOT_HEADER_TAG_END, 0

.section .multiboot
header_start:
.align 4
.long MAGIC
.long MULTIBOOT_ARCH
.long HEADER_LENGTH
.long CHECKSUM
# Tags variable size
# required end tag
.short MULTIBOOT_HEADER_TAG_END
.short 0
.long 8
header_end:
