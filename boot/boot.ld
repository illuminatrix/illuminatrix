SECTIONS
{
	. = 0x7c00;
	.text :
	{
		__start = .;
		*(.text)
		. = 0x1FE;
		SHORT(0xAA55)
		*(.nsector)
		. = ALIGN(512);
		__end = .;
		__end_align_4k = ALIGN(4k);
	}
}
