.set MAGIC, 0x1badb002 # Bootloader to recognize the kernel
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, - (MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern kernelMain
.extern callConstructors
.global loader

loader:
    mov $kernel_stack, %esp # Set stack_point before the execution of kernelMain
    
    call callConstructors # Run init functions between start_ctors and end_ctors

    push %eax # Point to multiboot_structor which stored some informations of hardware
    push %ebx # MAGIC_NUMBER
    call kernelMain

_stop:
    cli
    hlt
    jmp _stop

.section .bss
.space 2*1024*1024; # 2MiB
kernel_stack:
