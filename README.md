Iluminatrix kernel
==================

# Getting started

```
make 
make run
```

## Machine introspection
- Qemu is started with vga diplay using curses.
- To manage the VM Qemu is also started with monitor using stdin use `ctr-a + c`
  - It will show a Qemu prompt
  - Useful commands
      ```
      # get memory info
      mem info
      # Print a memory address (e.g 00)
      x 00
      # Stop VM
      quit
      ```
## Debug 

You can debug qemu the kernel using qemu and gdb
```
# Start qemu with debug
make run-debug
# In other terminal debug with qemu
make 
```
