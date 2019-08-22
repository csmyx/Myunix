#include "port.h"
#include "types.h"

/* Port.cpp */
Port::Port(uint16_t port_number) {
    this->port_number = port_number;
}

Port::~Port() {}

/* Port_8bit.cpp */
Port_8bit::Port_8bit(uint16_t port_number) 
: Port::Port(port_number) {

}

Port_8bit::~Port_8bit() {}

void Port_8bit::write(uint8_t data) {
    __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (port_number));
}

uint8_t Port_8bit::read() {
    uint8_t data;
    __asm__ volatile("inb %1, %0" : "=a" (data) : "Nd" (port_number));

    return data;
}

/* Port_8bit_slow.cpp */
Port_8bit_slow::Port_8bit_slow(uint16_t port_number) 
: Port_8bit::Port_8bit(port_number) {

}

Port_8bit_slow::~Port_8bit_slow() {}

void Port_8bit_slow::write(uint8_t data) {
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (data), "Nd" (port_number));
}

/* Port_16bit.cpp */
Port_16bit::Port_16bit(uint16_t port_number) 
: Port::Port(port_number) {

}

Port_16bit::~Port_16bit() {}

void Port_16bit::write(uint16_t data) {
    __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (port_number));
}

uint16_t Port_16bit::read() {
    uint16_t data;
    __asm__ volatile("inb %1, %0" : "=a" (data) : "Nd" (port_number));

    return data;
}

/* Port_32bit.cpp */
Port_32bit::Port_32bit(uint16_t port_number) 
: Port::Port(port_number) {

}

Port_32bit::~Port_32bit() {}

void Port_32bit::write(uint32_t data) {
    __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (port_number));
}

uint32_t Port_32bit::read() {
    uint32_t data;
    __asm__ volatile("inb %1, %0" : "=a" (data) : "Nd" (port_number));

    return data;
}