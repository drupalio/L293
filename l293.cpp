// Control an L293 with an MCP23S17 SPI 16-bit IO expander
#include "l293.h"

//---------- constructor ----------------------------------------------------

    // Pins are numbered GPIO_A0 to GPIO_B7
L293::L293(MCP23S17* p_io, uint8_t strobe_pin, uint8_t left_pin, uint8_t right_pin, uint16_t timeout_ms) :
    m_strobe_pin(0xFF), m_left_pin(0xFF), m_right_pin(0xFF), m_io_valid(false), m_timeout_ms(timeout_ms), m_p_io(p_io)
{
    int count = 0;
    if (strobe_pin < 16)
    {
        m_strobe_pin = strobe_pin;
        count++;
    }
    if (left_pin < 16)
    {
        m_left_pin = left_pin;
        count++;
    }
    if (right_pin < 16)
    {
        m_right_pin = right_pin;
        count++;
    }
    if (count == 3)
    {
        m_io_valid = true;
    }    
}

//---------- public ----------------------------------------------------

void L293::setup(void)
{
    if (this->m_io_valid)
    {
        this->m_p_io->pinMode(m_strobe_pin, OUTPUT);
        this->m_p_io->pinMode(m_left_pin, OUTPUT);
        this->m_p_io->pinMode(m_right_pin, OUTPUT);
    }
}


void L293::strobeLeft()
{
    if (this->m_io_valid)
    {
        uint16_t output = this->m_p_io->port();
        output |= (1 << this->m_left_pin);
        output &= ~(1 << this->m_right_pin);
        output |= (1 << this->m_strobe_pin);
        this->m_p_io->port(output);
        output &= ~(1 << this->m_strobe_pin);
        delay(this->m_timeout_ms);
        this->m_p_io->port(output);
    }
}

void L293::strobeRight()
{
    if (this->m_io_valid)
    {
        uint16_t output = this->m_p_io->port();
        output &= ~(1 << this->m_left_pin);
        output |= (1 << this->m_right_pin);
        output |= (1 << this->m_strobe_pin);
        this->m_p_io->port(output);
        output &= ~(1 << this->m_strobe_pin);
        delay(this->m_timeout_ms);
        this->m_p_io->port(output);
    }
}



