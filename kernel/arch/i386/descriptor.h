#ifndef _KERNEL_DESCRIPTOR_H
#define _KERNEL_DESCRIPTOR_H

#include <stdint.h>

#define NON_PRIVILEGED 0x03

// Segments
#define KERNEL_CS   0x08
#define KERNEL_DS   0x10
#define USER_CS     0x18
#define USER_DS     0x20
#define KERNEL_TSS  0x28

/*
 * Address of predefined pages
 *
 *  0000 - 0FFF : Reserved for NULL pointer detection
 *  1000 - 1FFF : Boot information
 *  2000 - 2FFF : Boot stack (idle stack)
 *  3000 - 3FFF : Kernel page directory table
 *  4000 - 4FFF : Temporary boot page table (0-4M)
 *  4000 - 4FFF : Interrupt stack
 */
#define BOOT_INFO	0x1000
#define BOOT_STACK	0x2000
#define KERNEL_PGD	0x3000
#define BOOT_PTE0	0x4000
#define INT_STACK	0x4000

#define RESERVED_PAGES  0x5000
#define PAGE_SIZE 4096

#define BOOT_STACK_TOP		(KERNEL_BASE + BOOT_STACK + 0x1000)
#define INT_STACK_TOP		(KERNEL_BASE + INT_STACK + INT_STACK_SIZE)
#define INT_STACK_BOTTOM	(KERNEL_BASE + INT_STACK)

struct seg_desc {
    uint16_t limit_lo;    /* segment limit (lsb) */
    uint32_t base_lo:24;     /* segment base address (lsb) */
    uint8_t  type;     /* type */
    uint8_t limit_hi:4;     /* segment limit (msb) */
    uint8_t size:4;     /* size */
    uint8_t base_hi;      /* segment base address (msb) */
} __attribute__ ((packed));
typedef struct seg_desc seg_desc_t;

/*
 * Segment size
 */
#define SIZE_32			0x4	/* 32-bit segment */
#define SIZE_16			0x0	/* 16-bit segment */
#define SIZE_4K			0x8	/* 4K limit field */

/*
 * Segment type
 */
#define ST_ACC			0x01	/* accessed */
#define ST_LDT			0x02	/* LDT */
#define ST_CALL_GATE_16		0x04	/* 16-bit call gate */
#define ST_TASK_GATE		0x05	/* task gate */
#define ST_TSS			0x09	/* task segment */
#define ST_CALL_GATE		0x0c	/* call gate */
#define ST_INTR_GATE		0x0e	/* interrupt gate */
#define ST_TRAP_GATE		0x0f	/* trap gate */

#define ST_TSS_BUSY		0x02	/* task busy */

#define ST_DATA			0x10	/* data */
#define ST_DATA_W		0x12	/* data, writable */
#define ST_DATA_E		0x14	/* data, expand-down */
#define ST_DATA_EW		0x16	/* data, expand-down, writable */

#define ST_CODE			0x18	/* code */
#define ST_CODE_R		0x1a	/* code, readable */
#define ST_CODE_C		0x1c	/* code, conforming */
#define ST_CODE_CR		0x1e	/* code, conforming, readable */

#define ST_KERN			0x00	/* kernel access only */
#define ST_USER			0x60	/* user access */

#define ST_PRESENT		0x80	/* segment present */

/*
 * Task State Segment (TSS)
 */

#define IO_BITMAP_SIZE		(65536/8 + 1)
#define INVALID_IO_BITMAP	0x8000

struct tss {
	uint32_t back_link;
	uint32_t esp0, ss0;
	uint32_t esp1, ss1;
	uint32_t esp2, ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax, ecx, edx, ebx;
	uint32_t esp, ebp, esi, edi;
	uint32_t es, cs, ss, ds, fs, gs;
	uint32_t ldt;
	uint16_t dbg_trace;
	uint16_t io_bitmap_offset;
} __attribute__ ((packed));
typedef struct tss tss_t;
#endif
