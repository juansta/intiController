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
 *
 * intiLED is a hardware and softwasre platform used to control high
 * power LED strings.
 *
 */

#include <global.h>
#include <rotary.h>
#include <lcd.h>
#include <delays.h>
#include <avr/power.h>
#include <avr/interrupt.h>

volatile unsigned int button;
volatile unsigned int left;
volatile unsigned int right;
volatile uint8_t portbhistory = 0xFF;     // default is high because the pull-up
bool spin;

ISR(PCINT0_vect)
{
    if (!spin)
    {
        uint8_t changedbits = PINB ^ portbhistory;
        portbhistory = PINB;

        if(changedbits & (1 << PB5))
        {
            button = button + 1;
        }

        if(changedbits & (1 << PB6))
        {
            left = left + 1;
        }

        if(changedbits & (1 << PB7))
        {
            right = right + 1;
        }
    }
}

int main(void)
{
    Lcd lcd;
    float i = 0;
    left = right = button = 0;

    clock_prescale_set(clock_div_1);

    DDRB = 0x00;
    PORTB |= 0xF0;

    PCICR  |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT2);
    PCMSK0 |= (1 << PCINT3);
    PCMSK0 |= (1 << PCINT4);
    PCMSK0 |= (1 << PCINT5);
    PCMSK0 |= (1 << PCINT6);
    PCMSK0 |= (1 << PCINT7);

    sei();

    while (1)
    {
         lcd.home();
         lcd.write("Timer - %.2f", i);
         lcd.setCursor(1,0);
         lcd.write("PC-%d L-%d R-%d", button, left, right);
         _delay_ms(10);

         i = i + 0.01f;
    }

    cli();

    return 0;
}
