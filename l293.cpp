// Control an L293 with an MCP23S17 SPI 16-bit IO expander
#include "l293.h"

//---------- constructor ----------------------------------------------------

    // Pins are numbered GPIO_A0 to GPIO_B7
L293::L293(MCP23S17* p_io, uint8_t strobe_pin, uint8_t left_pin, uint8_t right_pin, uint16_t timeout_ms) :
    m_strobe(0), m_left(0), m_right(0), m_strobe_pin(0), m_left_pin(0), m_right_pin(0), m_timeout_ms(timeout_ms), m_p_io(p_io)
{
    if (strobe_pin < 16)
    {
        m_strobe_pin = strobe_pin;
        m_strobe = 1 << strobe_pin;
    }
    if (left_pin < 16)
    {
        m_left_pin = left_pin;
        m_left = 1 << left_pin;
    }
    if (right_pin < 16)
    {
        m_right_pin = right_pin;
        m_right = 1 << right_pin;
    }
}

//---------- public ----------------------------------------------------

void L293::setup(void)
{

    this->m_p_io->pinMode(m_strobe_pin, OUTPUT);
    this->m_p_io->pinMode(m_left_pin, OUTPUT);
    this->m_p_io->pinMode(m_right_pin, OUTPUT);
}


void L293::strobeLeft()
{
    uint16_t output = this->m_p_io->port();
    output |= this->m_left;
    output &= ~this->m_right;
    output |= this->m_strobe;
    this->m_p_io->port(output);
    output &= ~this->m_strobe;
    delay(this->m_timeout_ms);
    this->m_p_io->port(output);
}

void L293::strobeRight()
{
    uint16_t output = this->m_p_io->port();
    output &= ~this->m_left;
    output |= this->m_right;
    output |= this->m_strobe;
    this->m_p_io->port(output);
    output &= ~this->m_strobe;
    delay(this->m_timeout_ms);
    this->m_p_io->port(output);
}



