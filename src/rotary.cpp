/*
 * This file is part of intiLED.
 *
 * intiLED is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * intiLED is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with intiLED.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <rotary.h>

volatile bool btn;
int button_count;

volatile bool up;
volatile bool spun;
int enc_count;

volatile uint8_t portbhistory = 0xFF;     // default is high because the pull-up

ISR(PCINT0_vect)
{
    uint8_t changedbits = PINB ^ portbhistory;
    bool a = PINB & (1 << PB6);
    bool b = PINB & (1 << PB7);

    if (changedbits & (1 << PB5))
        btn = !(PINB & (1 << PB5));
    else
    {
        a ? up = b : up = !b;

        spun = true;
    }

    portbhistory = PINB;
}

Rotary::Rotary()
{
    btn = spun = false;
    button_count = enc_count = 0;
    DDRB = 0x00;
    PORTB |= 0xF0;

    PCMSK0 |= (1 << PCINT5); // push button
    PCMSK0 |= (1 << PCINT6); // encoder A
    PCICR  |= (1 << PCIE0);
}

Rotary::button Rotary::check()
{
    button ret(NOTHING);

    if (btn)
    {
        ret = CLICK;
        btn = false;
    }
    else if (spun)
    {
        up ? ret = RIGHT : ret = LEFT;

        spun = false;
    }

    return ret;
}
