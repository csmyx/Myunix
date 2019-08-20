#include "types.h"
#include "gdt.h"

/* Need to write printf by hand because have not lib and os now */
void printf(char* str) {
    unsigned short* video_memory = (unsigned short*)0xb8000; // Point to the VGA Buffer Address

    for (int i = 0; str[i] != '\0'; ++i) {
        video_memory[i] = (video_memory[i] & 0xff00) | str[i]; // Preserve hibyte(attribute) and change lobyte(char)
	video_memory[i] = (video_memory[i] & 0x00ff) | 0x1500;
    }
    
}

typedef void (*constructor)();

extern "C" constructor start_ctors;

extern "C" constructor end_ctors;

extern "C" void callConstructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; ++i) {
        (*i)();
    }
}

extern "C" void kernelMain(void* multiboot_structure, unsigned int magic_number) {

    printf("Hello world! This is Myunix. :)");

    GlobalDescriptorTable gdt;

    while(1);
}
