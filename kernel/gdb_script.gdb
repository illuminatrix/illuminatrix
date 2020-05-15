file kernel.bin
target remote localhost:1234
layout regs
break _start
define hook-quit
    set confirm off
end
