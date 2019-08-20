#ifndef __GDT_H
#define __GDT_H

#include "types.h"

class GlobalDescriptorTable {

public:

    class SegementDescriptor {
    private:
        uint16_t limit_lo;
        uint16_t base_lo;
        uint8_t base_hi;
        uint8_t type;
        uint8_t flags_limit_hi;
        uint8_t base_vhi;
    public:
        SegementDescriptor(uint32_t base, uint32_t limit, uint8_t type);

        uint32_t getBase();
        uint32_t getLimit();

    } __attribute__((packed));

    SegementDescriptor nullSegmentSelector;
    SegementDescriptor unusedSegmentSelector;
    SegementDescriptor codeSegmentSelector;
    SegementDescriptor dataSegmentSelector;

    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    uint16_t codeSegmentSelectorOffset();
    uint16_t dataSegmentSelectorOffset();
};


#endif // !__GDT_H