#ifndef __PORT_H
#define __PORT_H

#include "types.h"

class Port {

protected:
    uint16_t port_number;
    Port(uint16_t port_number);
    ~Port();
};

class Port_8bit : public Port {

public:
    Port_8bit(uint16_t port_number);
    ~Port_8bit();

    virtual void write(uint8_t data);
    virtual uint8_t read();
};

class Port_8bit_slow : public Port_8bit {

public:
    Port_8bit_slow(uint16_t port_number);
    ~Port_8bit_slow();

    virtual void write(uint8_t data);
};

class Port_16bit : public Port {

public:
    Port_16bit(uint16_t port_number);
    ~Port_16bit();

    virtual void write(uint16_t data);
    virtual uint16_t read();
};

class Port_32bit : public Port {
    
public:
    Port_32bit(uint16_t port_number);
    ~Port_32bit();

    virtual void write(uint32_t data);
    virtual uint32_t read();
};


#endif // !__PORT_H
