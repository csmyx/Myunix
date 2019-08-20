#include "gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable()
: nullSegmentSelector(0, 0, 0),
  unusedSegmentSelector(0, 0, 0),
  codeSegmentSelector(0, 64*1024*1024, 0x9A),
  dataSegmentSelector(0, 64*1024*1024, 0x92) {

    uint32_t i[2];
    i[0] = (uint32_t)this;
    i[1] = sizeof(GlobalDescriptorTable) << 16; // Hibytes

    asm volatile("lgdt (%0)": :"p" (((uint8_t*)i)+2)); // tell how to use GDT

}

GlobalDescriptorTable::~GlobalDescriptorTable() {

}

uint16_t GlobalDescriptorTable::dataSegmentSelectorOffset() {
    return (uint8_t*)&dataSegmentSelector - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::codeSegmentSelectorOffset() {
    return (uint8_t*)&codeSegmentSelector - (uint8_t*)this;
}

GlobalDescriptorTable::SegementDescriptor::SegementDescriptor(uint32_t base, uint32_t limit, uint8_t flags) {
    
    uint8_t* target = (uint8_t*)this;

    if (limit <= 65536) {
        target[6] = 0x40;
    } else {
        if ((limit & 0XFFF) != 0xFFF) {
            limit = (limit >> 12) - 1;
        } else {
            limit = limit >> 12;
        }

        target[6] = 0xC0;
    }

    target[0] = limit & 0xFF; // limit_lo
    target[1] = (limit >> 8) & 0xFF; // limit_hi
    target[6] = target[6] | ((limit >> 16) & 0xF); // limit_vhi_half_byte

    target[2] = base & 0xFF; // base_vlo
    target[3] = (base >>  8) & 0xFF; // base_lo
    target[4] = (base >> 16) & 0xFF; // base_hi
    target[7] = (base >> 24) & 0xFF; // base_vhi

    target[5] = flags;
}

uint32_t GlobalDescriptorTable::SegementDescriptor::getBase() {
    
    uint8_t* target = (uint8_t*)this;
    uint32_t base = target[7];

    base = (base << 8) & target[4];
    base = (base << 8) & target[3];
    base = (base << 8) & target[2];

    return base;
}

uint32_t GlobalDescriptorTable::SegementDescriptor::getLimit() {
    
    uint8_t* target = (uint8_t*)this;
    uint32_t limit = target[6] & 0xF;
    
    limit = (limit << 8) & target[1];
    limit = (limit << 8) & target[0];

    if ((target[6] & 0xC0) == 0xC0) {
        limit = (limit << 12) | 0xFFF;
    }

    return limit;
}

