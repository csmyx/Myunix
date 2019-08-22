#include "types.h"
#include "gdt.h"

/* Need to write printf by hand because have not lib and os now */
void printf(const int8_t* str) {
    static uint16_t* video_memory = (uint16_t*)0xb8000; // Point to the VGA Buffer Address
    static uint8_t row = 0, col = 0; // current print posion
    const static uint8_t row_nums = 25, col_nums = 80; // screen size

    for (int32_t i = 0; str[i] != '\0'; ++i) {
        switch (str[i])
        {
        case '\n': // New line
            ++row;
            col = 0;
            break;
        
        default:
            video_memory[row*col_nums + col] = (video_memory[row*col_nums + col] & 0xff00) | str[i]; // Preserve hibyte(attribute) and change lobyte(char)
            video_memory[row*col_nums + col] = (video_memory[row*col_nums + col] & 0x00ff) | 0x1500; // Preserve lobyte(char) and change hibyte(attribute)
            ++col;
            break;
        }

        if (col >= col_nums) {
            col = 0;
            ++row;
        }

        if (row >= row_nums) {
            break;
        }
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

extern "C" void kernelMain(void* multiboot_structure, uint32_t magic_number) {

    printf("Hello world!\n");
    printf("This is Myunix v1.1!\n");
    printf("<~._.~>");

    GlobalDescriptorTable gdt;

    while(1);
}
