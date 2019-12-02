/* This symbol is exported in kernel head and it is the starting point */
ENTRY(_start)

SECTIONS
{
	/*
	 * Set kernel to be loaded at the 1MB address.
	 * This is the conventional place to put a kernel, at least to start.
	 * Below one megabyte is all kinds of memory-mapped stuff. Remember the VGA.
	 * It wouldn't work if we mapped our kernel's code to that part of memory... garbage on the screen!
	 * https://www.ics.uci.edu/~aburtsev/143A/hw/hw3-boot-into-c/hw3-boot-into-c.html
	 * Fun experiment: try to put it in 0xb8000.
	*/
	. = 1M;

	/*
	 * Set multiboot section on rodata this is only ready only so should not be part of text that has
	 * execution permissions.
	 * FIXME: Try to write to this just to see if is really read only or needs more ld or grub magic.
	 * FIXME need to aling to 4K to allow to Identitiy mapping on paging.
	 */
	.rodata :
	{
		/* ensure that the multiboot section is at the beginning */
		KEEP(*(.multiboot))
		*(.rodata .rodata.*)
	}

	/* FIXME need to aling to 4K to allow to Identitiy mapping on paging */
	.text : {
		*(.text)
	}

	/* FIXME:
	 * When jump to  identity map we may face this issue:
	 * https://github.com/phil-opp/blog_os/issues/126#issuecomment-176907574
	*/

	/*
	 * FIXME: Add bss section and more
	*/

}
