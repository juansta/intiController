#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

class Flick
{
public:
    Flick(int delay)
        :m_delay(delay)
    {
        DDRB |= 0b0000001;
    }

    void go()
    {
        PORTB = (PORTB ^ 0xFF);
        _delay_ms(m_delay);
    }

private:
    int m_delay;
};

int main(void) {
    Flick flick(100);

    while (1)
        flick.go();

    return 0;
}
