void main()
{
        char *terminal_buffer = (char*)0xb8000;
        *terminal_buffer = 'x';
        return;
}
