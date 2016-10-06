#include "asm_utils.h"

.text
    .extern general_interrupt_handler;
    .extern general_trap_handler;

ENTRY(common_interrupt)
    cld;
    SAVE_ALL
    pushl %esp;
    call general_interrupt_handler;
    addl $4, %esp;
interrupt_ret:
    cli;
    RESTORE_ALL;
    addl $8, %esp;
    iret;

#define INTR_ENTRY(irq) \
ENTRY(intr_##irq) \
    pushl $0; \
    pushl $(irq); \
    jmp common_interrupt;

INTR_ENTRY( 0)     /* PIT */
INTR_ENTRY( 1)     /* Keyboard/PS2 */
INTR_ENTRY( 2)     /* 8259A slave controller */
INTR_ENTRY( 3)     /* COM2 / COM4 */
INTR_ENTRY( 4)     /* COM1 / COM3 */
INTR_ENTRY( 5)     /* LPT2 */
INTR_ENTRY( 6)     /* Floppy controller */
INTR_ENTRY( 7)     /* LPT1 */
INTR_ENTRY( 8)     /* RTC */
INTR_ENTRY( 9)     /* unassigned */
INTR_ENTRY(10)     /* unassigned */
INTR_ENTRY(11)     /* unassigned */
INTR_ENTRY(12)     /* Mounse controller */
INTR_ENTRY(13)     /* Math coprocessor */
INTR_ENTRY(14)     /* Hard disk controller 1 */
INTR_ENTRY(15)     /* Hard disk controller 2 */

ENTRY(common_trap)
    SAVE_ALL
    pushl %esp;
    call general_trap_handler;
    addl $4, %esp;
trap_ret:
    RESTORE_ALL;
    addl $8, %esp;
    iret;

ENTRY(trap_default)
    pushl $0;
    pushl $(INVAL_INT);
    jmp common_trap;

#define TRAP_ENTRY(id) \
ENTRY(trap_##id) \
    pushl $0; \
    pushl $(id); \
    jmp common_trap;

#define TRAP_ERR_ENTRY(id) \
ENTRY(trap_##id) \
    pushl $0; \
    jmp common_trap;

TRAP_ENTRY    ( 0)      /* Divide error */
TRAP_ENTRY    ( 1)      /* Debug trap */
TRAP_ENTRY    ( 2)      /* NMI */
TRAP_ENTRY    ( 3)      /* Breakpoint */
TRAP_ENTRY    ( 4)      /* Overflow */
TRAP_ENTRY    ( 5)      /* Bounds check */
TRAP_ENTRY    ( 6)      /* Invalid opecode */
TRAP_ENTRY    ( 7)      /* Device not available */
TRAP_ERR_ENTRY( 8)      /* Double fault */
TRAP_ERR_ENTRY( 9)      /* Coprocessor overrun */
TRAP_ERR_ENTRY(10)      /* Invalid TSS */
TRAP_ERR_ENTRY(11)      /* Segment not present */
TRAP_ERR_ENTRY(12)      /* Stack bounds */
TRAP_ERR_ENTRY(13)      /* General Protection */
TRAP_ERR_ENTRY(14)      /* Page fault */
TRAP_ENTRY    (15)      /* (reserved) */
TRAP_ENTRY    (16)      /* Coprocessor error */
TRAP_ERR_ENTRY(17)      /* Alignment check */
TRAP_ERR_ENTRY(18)      /* Cache flush denied */

// System call
// TRAP(50)
.end
