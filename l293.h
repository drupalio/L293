
// Control an L293 with an MCP23S17 SPI 16-bit IO expander

#ifndef l293_h
#define l293_h

#include <Mcp23s17.h>

class L293
{
  public:
    // Pins are numbered GPIO_A0 to GPIO_B7
    L293(MCP23S17* p_io, uint8_t strobe_pin, uint8_t left_pin, uint8_t right_pin, uint16_t timeout_ms = 250);

    // Don't call this until SPI is initialised
    void setup();

    // GPIO 16-bit Combined Port (GPIO A0-A7 + GPIO B0-B7)
    void strobeLeft();
    void strobeRight();

  private:
    bool m_io_valid;
    uint8_t m_left_pin;
    uint8_t m_right_pin;
    uint8_t m_strobe_pin;
    uint16_t m_timeout_ms;
    MCP23S17* m_p_io;
};

#endif // Mcp23s17_h



