#include "utils.h"

#define TRAP(intno)                     \
    .globl trap##intno;                 \
    .align 4;                           \
    trap##intno:                        \
        SAVE_ALL                        \
        mov $intno, %eax;               \
        push %eax;                      \
        call general_interrupt_handler; \
        pop %eax;                       \
        RESTORE_ALL                     \
        iret;

.text
    .extern interrupt_handler;

# Processor exceptiions
TRAP(0) 
TRAP(1) 
TRAP(2) 
TRAP(3) 
TRAP(4) 
TRAP(5) 
TRAP(6) 
TRAP(7) 
TRAP(8) 
TRAP(9) 
TRAP(10)    
TRAP(11)    
TRAP(12)    
TRAP(13)    
TRAP(14)    
TRAP(15)    
TRAP(16)    
TRAP(17)    
TRAP(18)

# Bad traps
TRAP(19)
TRAP(20)
TRAP(21)
TRAP(22)
TRAP(23)
TRAP(24)
TRAP(25)
TRAP(26)
TRAP(27)
TRAP(28)
TRAP(29)
TRAP(30)
TRAP(31)

# IO Interrupts
TRAP(32)    
TRAP(33)    
TRAP(34)    
TRAP(35)    
TRAP(36)    
TRAP(37)    
TRAP(38)    
TRAP(39)    
TRAP(40)    
TRAP(41)    
TRAP(42)    
TRAP(43)    
TRAP(44)    
TRAP(45)    
TRAP(46)    
TRAP(47)    

# Bad traps 2
TRAP(48)
TRAP(49)

# System call
TRAP(50)
.end
