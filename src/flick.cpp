/*
 * This file is part of Foobar.
 *
 * Foobar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include <flick.h>

Flick::Flick(int delay)
    : m_delay(delay)
{
    DDRB |= 0b0000001;
}

void Flick::go()
{
    PORTB = (PORTB ^ 0xFF);
    //_delay_ms(m_delay);
    _delay_ms(1000);
}